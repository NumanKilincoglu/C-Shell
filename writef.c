#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{

    char string[15];

    read(3, string, 15);
    printf("alt program: %s", string);

    printf("\n%d--%d-- %s\n", getpid(), getppid(), argv[0]);
    printf("%d", writeFile(argv[0], string));
    printf("cikti");
    return 0;
}

int writeFile(char *fileName, char *string)
{
    FILE *file = NULL;
    printf("dosyaya gir\n");
    file = fopen(fileName, "a");

    if (file)
    {
        time_t curTime;
        time(&curTime);
        char pid[15] = {0};
        char ppid[25] = {0};
        sprintf(pid, "\nPID:%d ", getpid());
        sprintf(ppid, "PPID:%d ", getppid());
        fputs(string, file);
        fputs(pid, file);
        fputs(ppid, file);

        fputs(ctime(&curTime), file);
        fputs("\n", file);
        fclose(file);
    }
}
