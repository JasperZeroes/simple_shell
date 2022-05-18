#include "main.h"

/**
 * prompt- displays '$' as prompt and
 * collects/writes command of user to stdin
 *
 * Return: None
 */


void prompt(void)
{
	static int first_time = 1;

	printf("~$ ");
	if (first_time)
	{
		/*const char *CLEAR_SCREEN_ANSI = "\e[1;H\e[2J";*/
		const char *fp;
		write(STDOUT_FILENO, fp, 12);
		first_time = 0;
	}
}
