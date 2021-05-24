#include "memory.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define MEMORY_SIZE 65536

static int8_t *memory = NULL;

void initialize(void)
{
    if (memory != NULL) {
        memory = calloc(MEMORY_SIZE, sizeof(int8_t));
        assert(memory != NULL);
    } else {
        printf("Memory is already initialized");
    }
}