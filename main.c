#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.c"

#define BUFF_LEN 64
#define MAX_TOKEN 32
#define MAX_INPUT 64
#define HISTORY 64

char commandInput[BUFF_LEN] = {'\0'};
char *token[MAX_TOKEN] = {'\0'};

int main()
{
    while (1)
    {
        printf("MyShell >>");
        if (readCommandLine(commandInput, MAX_INPUT))
        {
            int cmdLen = commandLength(commandInput);

            printt(commandInput, cmdLen);
            printf("%d-- ", strlen(commandInput));
        }
        else
        {
            printf("\nLutfen gecerli bir komut giriniz!\n");
        }
    }

    return 0;
}