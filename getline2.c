#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
	/**
	  * main- prints '$' and wait for the user to enter a command.
	  * then, print same input to standard output.
	  *
	  * Return: Always 0
	  */
     
    int int_mode = isatty(STDIN_FILENO);

   // while (int_mode)
    //{
        if (int_mode == 1)
        {
            write(STDOUT_FILENO, "~$ ", 13);
        }

    //}
    return (0);
}
