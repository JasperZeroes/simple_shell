#include <stdio.h>
#include "main.h"

void prompt();
void read_command(char cmd[], char *par[]);

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
	char cmd[100], command[100], *parameters[20];  /*env variables */
	char *envp[] = { (char *) "PATH=/bin", 0};

	while (1)
	{
		/* type_prompt(); //displays prompt on screen */
		prompt(); /* displays prompt on screen */
		read_command(command, parameters);

		if (fork() != 0)   /* parent */
		{
			wait(NULL); /* wait for child process to complete */
		}
		else
		{
			/* inside child process */
			strcpy(cmd, "/bin/");
			strcat(cmd, command);
			execve(cmd, parameters, envp);
		}

		if (strcmp(command, "exit") == 0)
			break;
	}

	return (0);
}
