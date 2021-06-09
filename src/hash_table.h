#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct
{
    char *key;
    uint32_t value;
} Entry;

typedef struct
{
    Entry **entries;
    int size;
    int no_of_entries;
} Hash_Table;

unsigned long hash(char *str, int modulo);

Entry *new_entry(char *key, uint32_t value);

void free_entry(Entry *entry);

Hash_Table *new_table(int size);

void free_table(Hash_Table *hash_table);

void insert(Hash_Table *hash_table, char *key, uint32_t value);

uint32_t search(Hash_Table *hash_table, char *key);

void print(Hash_Table *hash_table);

#endif