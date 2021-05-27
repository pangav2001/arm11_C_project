#include <stdio.h>
#include <stdlib.h>
#include "parse_file.h"
#include "memory.h"

int32_t read_in_binary(char* fileName)
{
    FILE *inFile;
    int32_t fileSize;
    int8_t *buffer;

    inFile = fopen(fileName, "rb");

    if (inFile == NULL)
    {
        fputs("File error!", stderr);
        exit(1);
    }

    // get file size
    fseek(inFile, 0, SEEK_END);
    fileSize = ftell(inFile);
    rewind(inFile);

    if(fileSize > MEMORY_SIZE)
    {
        fputs("Larger file than expected!", stderr);
    }

    buffer = calloc(fileSize, sizeof(int8_t));
    if (buffer == NULL)
    {
        fputs("Memory error!", stderr);
        exit(2);
    }

    fread(buffer, 1, fileSize, inFile);

    for(int i = 0; i < fileSize; i++)
    {
        store_memory(i, buffer[i]);
    }
    
    fclose(inFile);

    return fileSize;
}