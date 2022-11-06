#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.c"

#define BUFF_LEN 64
#define MAX_TOKEN 32
#define MAX_INPUT 64
#define HISTORY 64

char commandInput[BUFF_LEN];
char *token[MAX_TOKEN];

int main()
{
    while (1)
    {
        clearArrays(commandInput, token, MAX_INPUT);
        printf("myshell >>");
        if (readCommandLine(commandInput, MAX_INPUT))
        {
            int cmdLen = commandLength(commandInput);
            commandToToken(commandInput, token, MAX_INPUT);

            print(commandInput, cmdLen);
            printf("\n%d-- \n", strlen(commandInput));

            if (strcmp(commandInput, "exit") == 0)
            {
                break;
            }
        }
        else
        {
            printf("\nLutfen gecerli bir komut giriniz!\n");
            continue;
        }
    }

    return 0;
}