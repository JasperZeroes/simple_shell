#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

void type_prompt();
void read_command (char cmd[], char *par[]);

int main(int argc __attribute__((unused)), char *argv[] __attribute__((unused)))
{
    char cmd[100], command[100], *parameters[20];  //env variables
    char *envp[] = { (char *) "PATH=/bin", 0};

    while (1)
    {
        type_prompt(); //displays prompt on screen
        read_command(command, parameters);

        if (fork() != 0)   //parent
        {
            wait(NULL); //wait for child process to finish
        }
        else
        {
            //inside child process
            strcpy (cmd, "/bin/");
            strcat (cmd, command);
            execve(cmd, parameters, envp);
        }

        if (strcmp (command, "exit") == 0)
            break;
    }

    return (0);
}

void type_prompt(void)
{
    static int first_time = 1;

    if (first_time)
    {
        const char *CLEAR_SCREEN_ANSI = "\e[1;H\e[2J";
        write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
        first_time = 0;
    }
    printf("~$ ");
}

void read_command (char cmd[], char *par[])
{
    char line[1024];
    int count = 0, i = 0, j = 0;
    char *array[100], *pch;

    //read one line
    for (;;)
    {
        int c = fgetc (stdin);
        line[count++] = (char) c;

        if (c == '\n')
            break;
    }

    if (count == 1)
        return;

    //parse the line into words
    pch = strtok(line, "\n");

    while (pch != NULL)
    {
        array[i++] = strdup(pch);
        pch = strtok(NULL, "\n");
    }

    //first word in the command
    strcpy (cmd, array[0]);
    //others are parameter
    for (int j =0; j < i; j++)
    {
        par[j] = array[j];
    }
    par[i] = NULL;
}
