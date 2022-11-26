#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>
#include <sys/wait.h>

#define BUFFER_LENGTH 100
#define PID_LENGTH 25
int pipeArray[3][2];

int main(int argc, char *argv[])
{
    int processNum = atoi(argv[0]);

    printf("%s %s\n", argv[0], argv[1]);

    doExec(argv, processNum);
    return 0;
}

void doExec(char *args[], int processNum)
{
    int ev;
    int pids[processNum];
    char *arg[2];
    arg[0] = args[1];
    arg[1] = NULL;
    for (int i = 0; i < processNum; i++)
    {
        if (pipe(pipeArray[i]) < 0)
        {
            return -1;
        }
    }
    for (int i = 0; i < processNum; i++)
    {
        pids[i] = fork();
        if (pids[i] == 0) // child process
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
            write(pipeArray[i][1], input, strlen(input));
            wait(&ev);
            close(pipeArray[i][1]);
        }
    }
}
