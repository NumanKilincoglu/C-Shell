#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define BUFFER_LENGTH 100
#define PID_LENGTH 25

int main(int argc, char *argv[])
{
    char string[BUFFER_LENGTH] = {'\0'};
    read(0, string, BUFFER_LENGTH);
    printf("------> %s\n", argv[0]);
    writeFile(argv[0], string);
    return 0;
}

int writeFile(char *fileName, char *string)
{
    FILE *file = NULL;
    file = fopen(fileName, "a");

    if (file)
    {
        char pid[PID_LENGTH] = {0};
        char ppid[PID_LENGTH] = {0};
        time_t curTime;
        time(&curTime);
        sprintf(pid, "PID:%d ", getpid());
        sprintf(ppid, "PPID:%d ", getppid());
        fputs(string, file);
        fputs(pid, file);
        fputs(ppid, file);
        fputs(ctime(&curTime), file);
        fputs("\n", file);
        fclose(file);
    }
}
