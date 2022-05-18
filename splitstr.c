#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#

int main(int argc, char *argv[])
{
    /**
     * strtok takes two parameters; a string and a delimiter
     * char *strtok(char *str, const char *delim)
    */ 
   
    char str[] = "Let's break this string up";
    const char *delimiter = " ";
    char *piece = strtok(str, delimiter);

    while(piece != NULL)
    {
        printf("%s\n", piece);
        piece = strtok(NULL, delimiter);
    }
    return (0);
}
