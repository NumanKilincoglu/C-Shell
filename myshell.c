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
                writef();
                break;
            case 7:
                runExecParam();
                break;
            case 8:
                helpScreen();
                break;
            default:
                handleErrors(choice);
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

void runExecParam()
{
    char *arg[4];
    arg[0] = token[2];
    arg[1] = token[5];
    arg[2] = token[3];
    arg[3] = NULL;
    int i;
    int pid = fork();

    if (pid == 0)
    {
        i = execv("execx", arg, NULL);
        perror("\nexecx calistirilamadi!\n");
    }
    else
    {
        wait(&i);
    }
}

void writef()
{
    if (pipe(pipefd) < 0)
    {
        perror("pipe");
        exit(1);
    }
    int ev = 0;
    int pid = fork();

    if (pid == 0)
    {
        char *arg[2];
        strcpy(arg[0], token[1]);
        arg[1] = NULL;
        ev = execv("writef", arg, NULL);
        perror("\nwritef calistirilamadi!\n");
    }
    else
    {
        char input[100] = {'\0'};
        printf("Input giriniz:\n");
        // fgets(input, 100, stdin);
        write(pipefd[1], input, strlen(input));
        wait(&ev);
    }
    close(pipefd);
}

void helpScreen()
{
    printf("\n--------------Shell Commands--------------\n");
    printf("\nExit shell: exit\n");
    printf("\nDisplay directory: ls\n");
    printf("\nClear terminal: clear\n");
    printf("\ncat: cat (parameter)\n");
    printf("\nwritef : writef -f filename\n");
    printf("\nexecx : execx -t 3 writef -f filename\n");
    printf("\nHelp screen: help\n");
    printf("\n******************************************\n");
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
    if (tokenCount == 1 && strcmp(token[0], "exit") == 0)
    {
        return 1;
    }
    else if (tokenCount == 1 && strcmp(token[0], "bash") == 0)
    {
        return 2;
    }
    else if (tokenCount == 1 && strcmp(token[0], "clear") == 0)
    {
        return 3;
    }
    else if (tokenCount == 1 && strcmp(token[0], "ls") == 0)
    {
        return 4;
    }
    else if (strcmp(token[0], "cat") == 0)
    {
        return 5;
    }
    else if (strcmp(token[0], "writef") == 0)
    {
        if (token[1] == NULL)
        {
            return -1;
        }
        return 6;
    }
    else if (tokenCount == 6)
    {
        if (strcmp(token[0], "execx") == 0 && strcmp(token[1], "-t") == 0 && strcmp(token[4], "-f") == 0)
        {
            if (token[2] != NULL && checkChar(token[2]) && token[3] != NULL && token[5] != NULL)
            {
                return 7;
            }
        }
        return -3;
    }

    else if (tokenCount == 1 && strcmp(token[0], "help") == 0)
    {
        return 8;
    }
    else
    {
        return -4;
    }
}

void handleErrors(int errorCode)
{

    if (errorCode == -1)
    {
        printf("\nLutfen writef komutunun parametrelerini kontrol edin!\nKomutlari gormek icin 'help' yazabilirsiniz\n");
    }
    if (errorCode == -2 || errorCode == -3)
    {
        printf("\nLutfen execx komutunun parametrelerini kontrol edin!\nKomutlari gormek icin 'help' yazabilirsiniz\n");
    }
    if (errorCode == -4)
    {
        printf("\nLutfen girdiginiz komutu kontrol edin!\nKomutlari gormek icin 'help' yazabilirsiniz\n");
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
