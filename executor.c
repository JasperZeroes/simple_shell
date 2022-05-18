#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "shell.h"
#include "node.h"
#include "executor.h"


char *search_path(char *file)
{
	char *PATH = getenv("PATH");
	char *p    = PATH;
	char *p2;
	
	int  plen = p2-p;
	struct stat st;
	int  alen = strlen(file);
	
	while(p && *p)
	{
		p2 = p;

		while(*p2 && *p2 != ':')
		{
			p2++;
		}

		if(!plen)
		{
			plen = 1;
		}

		char path[plen+1+alen+1];
		
	strncpy(path, p, p2-p);
		path[p2-p] = '\0';
		
	if(p2[-1] != '/')
		{
			strcat(path, "/");
		}

		strcat(path, file);
		
		if(stat(path, &st) == 0)
		{
			if(!S_ISREG(st.st_mode))
			{
				errno = ENOENT;
				p = p2;
				if(*p2 == ':')
				{
					p++;
				}
				continue;
			}

			p = malloc(strlen(path)+1);
			if(!p)
			{
				return NULL;
			}
			
		strcpy(p, path);
			return p;
		}
		else    /* file not found */
		{
			p = p2;
			if(*p2 == ':')
			{
				p++;
			}
		}
	}

	errno = ENOENT;
	return NULL;
}


int do_exec_cmd(int argc __attribute__ ((unused)), char **argv __attribute__((unused)))
{
	char *path;
	if(strchr(argv[0], '/'))
	{
		execv(argv[0], argv);
	}
	else
	{
		path = search_path(argv[0]);
		if(!path)
		{
			return 0;
		}
		execv(path, argv);
		free(path);
	}
	return 0;
}


static inline void free_argv(int argc __attribute__ ((unused)), char **argv __attribute__((unused)))
{
	if(!argc)
	{
		return;
	}

	while(argc--)
	{
		free(argv[argc]);
	}
}


int do_simple_command(struct node_s *node)
{
	int argc = 0;
	long max_args = 255;
	char *argv[max_args+1];     /* keep 1 for the terminating NULL arg */
	char *str;
	struct node_s *child;
	child = node->first_child;
	pid_t child_pid = fork();

	if(!node)
	{
		return 0;
	}

	if(!child)
	{
		return 0;
	}
	
	while(child)
	{
		str = child->val.str;
		argv[argc] = malloc(strlen(str)+1);
		
	if(!argv[argc])
		{
			free_argv(argc, argv);
			return 0;
		}
		
	strcpy(argv[argc], str);
		if(++argc >= max_args)
		{
			break;
		}
		child = child->next_sibling;
	}
	argv[argc] = NULL;

	if(child_pid == 0)
	{
		do_exec_cmd(argc, argv);
		fprintf(stderr, "error: failed to execute command: %s\n", strerror(errno));
		if(errno == ENOEXEC)
		{
			exit(126);
		}
		else if(errno == ENOENT)
		{
			exit(127);
		}
		else
		{
			exit(EXIT_FAILURE);
		}
	}
	else if(child_pid < 0)
	{
		fprintf(stderr, "error: failed to fork command: %s\n", strerror(errno));
		return 0;
	}

	waitpid(child_pid, &stat, 0);
	free_argv(argc, argv);
	
	return 1;
}
