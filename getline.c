#include <stdio.h>

int main(void)
{
	/**
	  * main- prints '$' and wait for the user to enter a command.
	  * then, print same input to standard output.
	  *
	  * Return: Always 0
	  */

	int c;

	printf("$ ");
	while ((c = getchar()) != EOF)
	{
		putchar(c);
	}

	return (0);
}
