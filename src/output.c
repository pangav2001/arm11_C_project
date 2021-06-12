#include "output.h"

void write_to_binary(char* fileName, uint32_t *data, int size)
{
    FILE *outFile;
    uint32_t *buffer;

    outFile = fopen(fileName, "wb");

    if (outFile == NULL)
    {
        fputs("File error!", stderr);
        exit(1);
    }

    buffer = calloc(1, sizeof(uint32_t));
    if (buffer == NULL)
    {
        fputs("Memory error!", stderr);
        exit(2);
    }

    for(int i = 0; i < size; i++)
    {
        *buffer = data[i];
        fwrite(buffer, sizeof(buffer), 1, outFile);
    }

    free(buffer);
    
    fclose(outFile);
}