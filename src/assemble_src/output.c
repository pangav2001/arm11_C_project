#include "headers/output.h"

void write_to_binary(char *fileName, uint32_t *data, int size)
{
    FILE *outFile = fopen(fileName, "wb");

    if (outFile == NULL)
    {
        fputs("File error!", stderr);
        exit(1);
    }

    fwrite(data, sizeof(uint32_t), size, outFile);

    fclose(outFile);
}