#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include "hash_table.h"

#define SIZE 20000

//the djb2 hashing algorithm adjusted for our table size
unsigned long hash(char *str, int modulo)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) ^ c; // hash(i - 1) * 33 ^ str[i]

    return hash % modulo;
}

//allocate memory for a new entry and copy the given
//key and value in it
Entry *new_entry(char *key, char *value)
{
    Entry *entry = (Entry *)malloc(sizeof(Entry));
    entry->key = (char *)malloc(strlen(key));
    entry->value = (char *)malloc(strlen(value));

    strncpy(entry->key, key, strlen(key));
    strncpy(entry->value, value, strlen(value));

    return entry;
}

//free allocated memory for an entry on the heap
void free_entry(Entry *entry)
{
    free(entry->key);
    free(entry->value);
    free(entry);
}

//allocate memory for a new hash table, set its size to
//the given size, the number of entries to 0
//and initialize all items to NULL
Hash_Table *new_table(int size)
{
    Hash_Table *hash_table = (Hash_Table *)malloc(sizeof(Hash_Table));
    hash_table->size = size;
    hash_table->no_of_entries = 0;
    hash_table->entries = (Entry **)malloc(hash_table->size * sizeof(Entry *));

    for (int i = 0; i < hash_table->size; i++)
    {
        hash_table->entries[i] = NULL;
    }

    return hash_table;
}

//free allocated memory for a hash table on the heap
void free_table(Hash_Table *hash_table)
{
    for (int i = 0; i < hash_table->size; i++)
    {
        if (hash_table->entries[i] != NULL)
        {
            free_entry(hash_table->entries[i]);
        }
    }

    free(hash_table->entries);
    free(hash_table);
}

//create new entry with the given key and value, calculate its index
//and try to insert it in the hash table
void insert(Hash_Table *hash_table, char *key, char *value)
{
    Entry *entry = new_entry(key, value);

    int index = hash(key, hash_table->size);

    Entry *to_insert = hash_table->entries[index];

    if (to_insert == NULL)
    {
        //make sure that the hash table isn't full before inserting
        if (hash_table->no_of_entries == hash_table->size)
        {
            //expand(); //Not sure if we really need to implement this
            printf("Oh oh... cannot insert new value - hash table is full!\n");
            free_entry(entry);
            return;
        }

        hash_table->entries[index] = entry;
        hash_table->no_of_entries++;
    }
    //in case of a collision:
    else
    {
        //if the key is actually the same and the collision wasn't caused
        //by the hash function
        if (!strcmp(to_insert->key, key))
        {
            strncpy(hash_table->entries[index]->value, value, strlen(value));
            return;
        }
        //if there was an actual collision
        else
        {
            //collision(); //Later?
            return;
        }
    }
}

//search the hash table for the entry with the given key
//and return its value; if there's no such key, return NULL
char *search(Hash_Table *hash_table, char *key)
{
    int index = hash(key, hash_table->size);

    if (hash_table->entries[index] != NULL)
    {
        if (!strcmp(hash_table->entries[index]->key, key))
        {
            return hash_table->entries[index]->value;
        }
    }

    return NULL;
}

void print(Hash_Table *hash_table)
{
    for (int i = 0; i < hash_table->size; i++)
    {
        if (hash_table->entries[i])
        {
            printf("Index:%d, Key:%s, Value:%s\n", i, hash_table->entries[i]->key, hash_table->entries[i]->value);
        }
    }
}

int main()
{
    Hash_Table *hash_table = new_table(SIZE);
    insert(hash_table, "1", "Naman");
    insert(hash_table, "2", "Karim");
    insert(hash_table, "3", "Konstantinos");
    insert(hash_table, "4", "Panayiotis");
    print(hash_table);
    free_table(hash_table);
    return 0;
}