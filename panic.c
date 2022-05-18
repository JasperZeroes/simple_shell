#include "main2.h"
#include <stdio.h>

void panic(char *s)
{
	fprintf(2, "%s\n", s);
	exit(1);
}
