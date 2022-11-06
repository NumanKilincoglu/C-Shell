#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    printf("%s-->", tokens[index]);

    while (input[index] != NULL)
    {
        tokens[++index] = strtok(NULL, " \t\n");
    }

}

void clearArrays(char *commandInput, char **tokens, int MAX_INPUT)
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
