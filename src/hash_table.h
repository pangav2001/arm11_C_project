#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct Entry Entry;

typedef struct Hash_Table Hash_Table;

typedef struct List_Node List_Node;

unsigned long hash(char *str, int modulo);

Entry *new_entry(char *key, uint32_t value);

void free_entry(Entry *entry);

Hash_Table *new_table(int size);

void free_table(Hash_Table *hash_table);

void table_insert(Hash_Table *hash_table, char *key, uint32_t value);

uint32_t table_search(Hash_Table *hash_table, char *key);

void print_table(Hash_Table *hash_table);

List_Node *new_node();

List_Node *list_insert(List_Node *linked_list, Entry *entry);

Entry *list_remove(List_Node **linked_list);

void free_list(List_Node *linked_list);

List_Node **create_buckets(Hash_Table *hash_table);

void free_buckets(Hash_Table *hash_table);

void collision(Hash_Table *hash_table, int index, Entry *entry);

void table_remove(Hash_Table *hash_table, char *key);

#endif