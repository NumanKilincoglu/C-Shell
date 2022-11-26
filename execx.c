#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>

#define BUFFER_LENGTH 100
#define PID_LENGTH 25
int pipeArray[2];

int main(int argc, char *argv[])
{
    int processNum = atoi(argv[0]);
    doExec(argv, processNum);
    return 0;
}

void doExec(char *args[], int processNum)
{
    int ev;
    char *arg[2];
    arg[0] = args[1];
    arg[1] = NULL;

    if (pipe(pipeArray) < 0)
    {
        return -1;
    }

    for (int i = 0; i < processNum; i++)
    {
        int pid = fork();
        if (pid == 0) // child process
        {
            ev = execv("writef", arg, NULL);
            perror("Hata var");
            exit(0);
        }
        else
        {
            char input[100] = {'\0'};
            printf("Input giriniz:\n");
            // fgets(input, 100, stdin);
            write(pipeArray[1], input, strlen(input));
            wait(&ev);
        }
    }
}
