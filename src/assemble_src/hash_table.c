#include "headers/hash_table.h"
#include <assert.h>

//#define SIZE 20000

struct Entry
{
    char *key;
    uint32_t value;
};

struct Hash_Table
{
    Entry **entries;
    List_Node **buckets;
    int size;
    int no_of_entries;
};

struct List_Node
{
    Entry *entry;
    List_Node *next;
};

// the djb2 hashing algorithm adjusted for our table size
unsigned long hash(char *str, int modulo)
{
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) ^ c; // hash(i - 1) * 33 ^ str[i]

    return hash % modulo;
}

// allocate memory for a new entry and copy the given
// key and value in it
Entry *new_entry(char *key, uint32_t value)
{
    Entry *entry = (Entry *)malloc(sizeof(Entry));
    assert(entry != NULL);

    entry->key = (char *)malloc(strlen(key) + 1); //+1 for string terminator
    assert(entry->key != NULL);

    entry->value = value;

    strcpy(entry->key, key);

    return entry;
}

// free allocated memory for an entry on the heap
void free_entry(Entry *entry)
{
    free(entry->key);
    free(entry);
}

// allocate memory for a new hash table, set its size to
// the given size, the number of entries to 0
// and initialize all items to NULL
Hash_Table *new_table(int size)
{
    Hash_Table *hash_table = (Hash_Table *)malloc(sizeof(Hash_Table));
    assert(hash_table != NULL);

    hash_table->size = size;
    hash_table->no_of_entries = 0;
    hash_table->entries = (Entry **)malloc(hash_table->size * sizeof(Entry *));
    assert(hash_table->entries != NULL);

    for (int i = 0; i < hash_table->size; i++)
    {
        hash_table->entries[i] = NULL;
    }

    hash_table->buckets = create_buckets(hash_table);

    return hash_table;
}

// free allocated memory for a hash table on the heap
void free_table(Hash_Table *hash_table)
{
    for (int i = 0; i < hash_table->size; i++)
    {
        if (hash_table->entries[i] != NULL)
        {
            free_entry(hash_table->entries[i]);
        }
    }

    free_buckets(hash_table);
    free(hash_table->entries);
    free(hash_table);
}

// create new entry with the given key and value, calculate its index
// and try to insert it in the hash table
void table_insert(Hash_Table *hash_table, char *key, uint32_t value)
{
    Entry *entry = new_entry(key, value);

    int index = hash(key, hash_table->size);

    Entry *to_insert = hash_table->entries[index];

    if (to_insert == NULL)
    {
        // make sure that the hash table isn't full before inserting
        // although this might not be necessary due to bucketing
        if (hash_table->no_of_entries == hash_table->size)
        {
            // expand(); // Not sure if we really need to implement this
            printf("Oh oh... cannot insert new value - hash table is full!\n");
            free_entry(entry);
            return;
        }

        hash_table->entries[index] = entry;
        hash_table->no_of_entries++;
    }
    // in case of a collision:
    else
    {
        // if the key is actually the same and the collision wasn't caused
        // by the hash function
        if (!strcmp(to_insert->key, key))
        {
            hash_table->entries[index]->value = value;
            return;
        }
        // if there was an actual collision
        else
        {
            collision(hash_table, index, entry);
            return;
        }
    }
}

// search the hash table for the entry with the given key
// and return its value; if there's no such key, return -1
uint32_t table_search(Hash_Table *hash_table, char *key)
{
    int index = hash(key, hash_table->size);
    Entry *entry = hash_table->entries[index];
    List_Node *head = hash_table->buckets[index];

    while (entry != NULL)
    {
        if (!strcmp(entry->key, key))
        {
            return entry->value;
        }

        if (head == NULL)
        {
            return -1;
        }

        head = head->next;
        entry = head->entry;
    }

    return -1;
}

// print each entry of the hash table along with its index
void print_table(Hash_Table *hash_table)
{
    bool empty = true;

    for (int i = 0; i < hash_table->size; i++)
    {
        if (hash_table->entries[i] != NULL)
        {
            empty = false;
            printf("Index: %d, Key: %s, Value: %d", i, hash_table->entries[i]->key, hash_table->entries[i]->value);
            if (hash_table->buckets[i] != NULL)
            {
                printf(" ; Bucket: ");
                List_Node *head = hash_table->buckets[i];
                while (head != NULL)
                {
                    printf("Key: %s, Value: %d ; ", head->entry->key, head->entry->value);
                    head = head->next;
                }
            }
            printf("\n");
        }
    }

    if (empty)
    {
        printf("Sorry! Hash table is empty!\n");
    }
    else
    {
        printf("\n");
    }
}

// allocate memory on the heap for a new linked list node pointer
List_Node *new_node()
{
    List_Node *node = (List_Node *)malloc(sizeof(List_Node));
    assert(node != NULL);

    return node;
}

// insert new node at start of the list

List_Node *list_insert(List_Node *linked_list, Entry *entry)
{
    if (linked_list == NULL)
    {
        List_Node *head = new_node();

        head->entry = entry;
        head->next = NULL;
        linked_list = head;

        return linked_list;
    }
    else if (linked_list->next == NULL)
    {
        List_Node *node = new_node();

        node->entry = entry;
        node->next = NULL;
        linked_list->next = node;

        return linked_list;
    }
    else
    {
        List_Node *temp = linked_list;

        while (temp->next->next != NULL)
        {
            temp = temp->next;
        }

        List_Node *node = new_node();

        node->entry = entry;
        node->next = NULL;
        temp->next = node;

        return linked_list;
    }
}

// pop the head of the list and return its contents
Entry *list_pop(List_Node **linked_list)
{
    if (*linked_list == NULL || (*linked_list)->next == NULL)
    {
        return NULL;
    }

    List_Node *node = NULL;
    node = (*linked_list)->next;

    Entry *entry = NULL;
    entry = (*linked_list)->entry;

    free(*linked_list);

    *linked_list = node;

    return entry;
}

// free the allocated memory for a list
void free_list(List_Node *linked_list)
{
    List_Node *temp = linked_list;
    while (linked_list != NULL)
    {
        temp = linked_list;
        linked_list = linked_list->next;
        free(temp->entry->key);
        free(temp->next);
        free(temp);
    }
}

// allocate memory for the overflow buckets
List_Node **create_buckets(Hash_Table *hash_table)
{
    List_Node **buckets = (List_Node **)malloc(hash_table->size * sizeof(List_Node *));
    assert(buckets != NULL);

    for (int i = 0; i < hash_table->size; i++)
    {
        buckets[i] = NULL;
    }

    return buckets;
}

// free the memory allocated for the overflow buckets
void free_buckets(Hash_Table *hash_table)
{
    List_Node **buckets = hash_table->buckets;

    for (int i = 0; i < hash_table->size; i++)
    {
        free_list(buckets[i]);
    }

    free(buckets);
}

// add the entry that caused a collision to the appropriate bucket
void collision(Hash_Table *hash_table, int index, Entry *entry)
{
    List_Node *head = hash_table->buckets[index];

    if (head == NULL)
    {
        head = new_node();
        head->entry = entry;
        head->next = NULL;
        hash_table->buckets[index] = head;
        return;
    }
    else
    {
        hash_table->buckets[index] = list_insert(head, entry);
        return;
    }
}

// check if the key is present; then check if there is a bucket
// if not then just delete the entry, if there's a bucket then iterate
// through it until the key is found or the end of the bucket is reached
void table_remove(Hash_Table *hash_table, char *key)
{
    int index = hash(key, hash_table->size);
    Entry *entry = hash_table->entries[index];
    List_Node *head = hash_table->buckets[index];

    if (entry == NULL)
    {
        return;
    }
    else
    {
        if (head == NULL && !strcmp(entry->key, key))
        {
            hash_table->entries[index] = NULL;
            free_entry(entry);
            hash_table->no_of_entries--;
            return;
        }
        else if (head != NULL)
        {
            if (!strcmp(entry->key, key))
            {
                free_entry(entry);
                List_Node *node = head;
                head = head->next;
                node->next = NULL;
                hash_table->entries[index] = new_entry(node->entry->key, node->entry->value);
                free_list(node);
                hash_table->buckets[index] = head;
                return;
            }

            List_Node *curr = head;
            List_Node *prev = NULL;

            while (curr != NULL)
            {
                if (!strcmp(curr->entry->key, key))
                {
                    if (prev == NULL)
                    {
                        free_list(head);
                        hash_table->buckets[index] = NULL;
                        return;
                    }
                    else
                    {
                        prev->next = curr->next;
                        curr->next = NULL;
                        free_list(curr);
                        hash_table->buckets[index] = head;
                        return;
                    }
                }

                curr = curr->next;
                prev = curr;
            }
        }
    }
}
