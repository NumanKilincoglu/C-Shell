#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFF_LEN 64
#define MAX_TOKEN 32
#define MAX_INPUT 64
#define HISTORY 64

char commandInput[BUFF_LEN];
char *token[MAX_TOKEN];
int tokenCount = 0;

int main()
{
    while (1)
    {
        settings(commandInput, token);
        printf("\nmyshell >>");
        if (readCommandLine(commandInput, MAX_INPUT))
        {
            int cmdLen = commandLength(commandInput);
            printf("%d --\n", cmdLen);
            commandToToken(cmdLen);

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
    printf("cikti\n");

    return 0;
}

int readCommandLine(char *input, int maxLength)
{
    if (!fgets(input, maxLength, stdin))
        return 0;
    int cmdLength = commandLength(input);
    if (cmdLength == 0)
        return 0;
    if (cmdLength == 1 && (input[0] == '\n' || input[0] == '\r' || input[0] == '\t'))
        return 0;
    if (input[cmdLength - 1] == '\n')
    {
        input[cmdLength - 1] = '\0';
    }
    return 1;
}

int commandLength(char *input)
{
    return strlen(input);
}

int commandToToken(int lineLength)
{
    printf("*****>*****\n");
    int index = 0;
    token[index] = strtok(commandInput, " ");
    tokenCount++;
    int se = 0;
    while (commandInput[index] != '\0' && index <= lineLength)
    {   //printf("%s -: ", token[index]);
        token[++index] = strtok('\0', " ");
        printf("%d ", se++);
        tokenCount++;
    }
    printf("%d ", se);
    //printf(" %d ", tokenCount);

    for (int i = 0; i < tokenCount - 1; i++)
    {
        printf("%s ", token[i]);
    }

    printf("\n*****>*****\n");
}

void settings()
{
    tokenCount = 0;
    memset(commandInput, '\0', MAX_INPUT);
    memset(token, '\0', sizeof(token));
}

void print(char *input, int lineLength)
{
    int index = 0;

    while (input[index] != '0' && index <= lineLength)
    {
        printf("%c", input[index++]);
    }
    printf("\n%d --> ", lineLength);
}
