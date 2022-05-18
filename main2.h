#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define EXEC 1
#define REDIR 2
#define PIPE 3
#define LIST 4
#define BACK 5

#define MAXARGS 10

struct cmd
{
	int type;
};

struct execcmd
{
	int type;
	char *argv[MAXARGS];
	char *eargv[MAXARGS];
};

struct redircmd
{
	int type;
	struct cmd *cmd;
	char *file;
	char *efile;
	int mode;
	int fd;
};

struct pipecmd
{
	int type;
	struct cmd *left;
	struct cmd *right;
};

struct backcmd
{
	int type;
	struct cmd *cmd;
};

struct listcmd
{
	int type;
	struct cmd *left;
	struct cmd *right;
};

struct cmd *execcmd(void);
struct cmd *redircmd(struct cmd *subcmd, char *file, char *efile, int mode, int fd);
struct cmd *pipecmd(struct cmd *left, struct cmd *right);
struct cmd *parsecmd(char *s);
struct cmd *parsepipe(char **ps, char *es);
struct cmd *parseline(char **ps, char *es);
struct cmd *parseblock(char **ps, char *es);
struct cmd *parseredirs(struct cmd *cmd, char **ps, char *es);
struct cmd *parseexec(char **ps, char *es);
struct cmd *nulterminate(struct cmd *cmd);

void panic(char *s);
int fork1(void);
void runcmd(struct cmd *cmd);
int gettoken(char **ps, char **es, char **q, char **eq);
int getcmd(char *buf, int nbuf);
int peek(char **ps, char *es, char *toks);
