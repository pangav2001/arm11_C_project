#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct
{
    char *key;
    char *value;
} Entry;

typedef struct
{
    Entry **entries;
    int size;
    int no_of_entries;
} Hash_Table;

unsigned long hash(char *str, int modulo);

Entry *new_entry(char *key, char *value);

void free_entry(Entry *entry);

Hash_Table *new_table(int size);

void free_table(Hash_Table *hash_table);

void insert(Hash_Table *hash_table, char *key, char *value);

char *search(Hash_Table *hash_table, char *key);

void print(Hash_Table *hash_table);

#endif