#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>
#include <sys/wait.h>

#define BUFF_LEN 64
#define MAX_TOKEN 32
#define MAX_INPUT 64
#define HISTORY 64

char commandInput[BUFF_LEN];
// char bufferArray[BUFF_LEN];
char *token[MAX_TOKEN];
int tokenCount = 0;

int pipefd[2];

int main()
{
    while (1)
    {
        settings(commandInput, token);
        printf("\nmyshell >>");
        if (readCommandLine(commandInput, MAX_INPUT))
        {
            if (pipe(pipefd) < 0)
            {
                perror("pipe");
                exit(1);
            }
            commandToToken();
            int choice = handleCommand();
            switch (choice)
            {
            case 1:
                exit(1);
                break;
            case 2:
                runBash();
                break;
            case 3:
                clearTerminal();
                break;
            case 4:
                list();
                break;
            case 5:
                cat();
                break;
            case 6:
                runExecx();
                break;
            case 7:
                runExecx();
                break;
            case 8:
                helpScreen();
                break;
            default:
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

void runBash()
{
    int i;
    int pid = fork();

    if (pid == 0)
    {
        i = execve("/bin/bash", NULL, NULL);
        perror("\nBash calistirilirken sorun olustu!\n");
    }
    else
    {
        wait(&i);
    }
}

void clearTerminal()
{
    system("clear");
}

void list()
{
    DIR *dir;
    struct dirent *directory;
    dir = opendir(".");
    if (dir)    
    {
        while ((directory = readdir(dir)) != NULL)
        {
            printf("%s\t", directory->d_name);
        }
        closedir(dir);
    }
    puts("\n");
}

void cat()
{
    printf("cat:");
    for (int i = 1; i < tokenCount; i++)
    {
        printf("%s ", token[i]);
    }
}

void runExecx()
{
}

void writef(){

}

void helpScreen()
{
    printf("\n-------Shell Commands-------\n");
    printf("\nExit shell: exit\n");
    printf("\nList directory: ls\n");
    printf("\nClear terminal: clear\n");
    printf("\ncat: cat\n");
    printf("\nexecx : execx -t 3 writef -f filename\n");
    printf("\nHelp screen: help\n");
    printf("\n****************************\n");
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

int commandToToken()
{
    int index = 0;
    char *bufferArray = strdup(commandInput);
    char *str = strtok(bufferArray, " ");

    while (str != NULL)
    {
        tokenCount++;
        token[index++] = str;
        str = strtok(NULL, " ");
    }
}

int handleCommand()
{
    if (strcmp(token[0], "exit") == 0)
    {
        return 1;
    }
    else if (strcmp(token[0], "bash") == 0)
    {
        return 2;
    }
    else if (strcmp(token[0], "clear") == 0)
    {
        return 3;
    }
    else if (strcmp(token[0], "ls") == 0)
    {
        return 4;
    }
    else if (strcmp(token[0], "cat") == 0)
    {
        return 5;
    }
    else if (strcmp(token[0], "execx") == 0 && strcmp(token[1], "-t") == 0 && strcmp(token[3], "writef") == 0 && strcmp(token[4], "-f") == 0)
    {
        if (checkChar(token[2]) && token[5] != NULL)
        {
            return 6;
        }
        return -3;
    }
    else if (strcmp(token[0], "execx") == 0 && strcmp(token[1], "-t") == 0 && strcmp(token[3], "writef") == 0)
    {
        if (checkChar(token[2]))
        {
            return 7;
        }
        return -1;
    }

    else if (strcmp(token[0], "help") == 0)
    {
        return 8;
    }
    else
    {
        return -2;
    }
}

int checkChar(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] > '9' || str[i] < '0')
            return 0;
    }
    return 1;
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

void printTokens()
{
    for (int i = 0; i < tokenCount; i++)
    {
        printf("\n%d: %s\n", i, token[i]);
    }
}
