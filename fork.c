#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int n;
    int id = fork();

    if (id == 0)
    {
        printf("Child Process running\n");
        for (n = 6; n <11; n++)
        {
            printf("%d\n", n);
        }
    printf("\n");
    }
        //printf("Child process of id %d is running\n", id);
    else
    {
        printf("Parent Process running\n");
        for (n = 1; n < 6; n++)
        {
            printf("%d\n", n); 
        }
    }

    return 0;
}
