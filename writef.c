#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    
    int rvalue = writeFile();

    return 0;
}

int writeFile(char *fileName)
{
    FILE *file = NULL;

    file = fopen(fileName, 'a');
    
    if(file == NULL){
        file = fopen(fileName, 'w');

    }

}
