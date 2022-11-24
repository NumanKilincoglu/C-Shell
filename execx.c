#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define BUFFER_LENGTH 100
#define PID_LENGTH 25

int main(int argc, char *argv[])
{
    printf("%d", getpid());
    for (int i = 0; i < argc; i++)
    {
        printf("%s %s girdik", argv[0], argv[1]);
    }
    
    return 0;
}