#include "main.h"

/**
 * read_command- reads cmd entered by user,
 * and parses the cmd into words
 * @cmd: arrays that stores the user's command
 * @par: point to the addr of parsed word
 *
 * Return: None
 */

void read_command(char cmd[], char *par[])
{
	char line[1024];
	int count = 0, i = 0, j;
	char *array[100], *pch;

	/* reads one line */
	for (;;)
	{
		int c = fgetc(stdin);

		line[count++] = (char) c;

		if (c == '\n')
			break;
	}

	if (count == 1)
		return;

	/* parse the line into words */
	pch = strtok(line, "\n");

	while (pch != NULL)
	{
		array[i++] = strdup(pch);
		pch = strtok(NULL, "\n");
	}

	/* first word in the command */
	strcpy(cmd, array[0]);
	/* others are parameter */
	for (j = 0; j < i; j++)
	{
		par[j] = array[j];
	}
	par[i] = NULL;
}
