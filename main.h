#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

void prompt(void);
void read_command(char cmd[], char *par[]);

#endif /* MAIN_H */
