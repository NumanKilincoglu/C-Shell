#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
        clearArrays(commandInput, token);
        printf("myshell >>");
        if (readCommandLine(commandInput, MAX_INPUT))
        {
            int cmdLen = commandLength(commandInput);
            commandToToken(commandInput, token, MAX_INPUT);
            print(commandInput, cmdLen);
            

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

int commandToToken(char *input, char *tokens[], int length)
{
    printf("*****>*****\n");
    int index = 0;
    tokens[index] = strtok(input, " \t\n");

    while (input[index] != NULL)
    {
        tokens[++index] = strtok(NULL, " \t\n");
    }
    printStr(**tokens, length);

}

void clearArrays(char *commandInput, char **tokens)
{
    memset(commandInput, '\0', MAX_INPUT);
    memset(tokens, '\0', sizeof(tokens));
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


void printStr(char **input, int lineLength)
{
    int index = 0;

    printf("%s ", input[index++]);
 
}
