#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// not the best implementation of a hash table but it does the job well

typedef struct {
    const char* key;
    void* value;
} ht_entry;

typedef struct HashTable HashTable;



void Dict_destroy(HashTable* table);
void* Dict_get(HashTable* table, const char* key);
const char* Dict_set(HashTable* table, const char* key, void* value);
HashTable* Dict_create(void);

#endif