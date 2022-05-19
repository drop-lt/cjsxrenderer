#include "HashTable.h"
#include <stdio.h>
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL
#define INITIAL_CAPACITY 16 

typedef struct {
    uint64_t key;
    void* value;
} Dict_entry_t;

struct HashTable {
    Dict_entry_t* entries;    // hash slots
    size_t capacity;      // size of _entries array
    size_t length;        // number of items in hash table
};

// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
static uint64_t hash_key(const char* key) { // i have no idea how this works but it does, im not into hashing
    uint64_t hash = FNV_OFFSET;
    for (const char* p = key; *p++; hash ^= *p) hash *= FNV_PRIME;
    return hash;
}

static const char* Dict_setEntry(Dict_entry_t* entries, size_t capacity, uint64_t key, void* value, size_t* length) {
    size_t index;
    for (index = key & (capacity - 1); entries[index].key; index = ++index >= capacity ? 0 : index)  // start from the end of the hash and go wrapping around until an empty spot
        if (key == entries[index].key) {                                                             // hash is the same as other hash
            entries[index].value = value;                                                            // set value
            return key;                                                                              // done
        }

    if (length) (*length)++;                                                                         // if isn't expanding the dict, increase length
    
    entries[index].key = key;     //new key
    entries[index].value = value; // new value
    return key;
}

static int Dict_expand(HashTable* table) {
    size_t new_capacity = table->capacity << 1; 

    Dict_entry_t* new_entries = calloc(new_capacity, sizeof(Dict_entry_t));
    if (!new_entries) return 1;

    for (size_t i = 0; i < table->capacity; ++i) {
        Dict_entry_t entry = table->entries[i];
        if (entry.key)  Dict_setEntry(new_entries, new_capacity, entry.key, entry.value, NULL);
    }

    free(table->entries);
    table->entries = new_entries;
    table->capacity = new_capacity;
    return 0;
}

const char* Dict_set(HashTable* table, const char* key, void* value) {
    return table->length >= table->capacity / 2 && Dict_expand(table) ? NULL : Dict_setEntry(table->entries, table->capacity, hash_key(key), value, &table->length);
}

void* Dict_get(HashTable* table, const char* key) {
    for (size_t index = hash_key(key) & (table->capacity - 1); table->entries[index].key; index = ++index >= table->capacity ? 0 : index)
        if (!strcmp(key, table->entries[index].key)) return table->entries[index].value; // Found key, return value.

    return NULL;
}

static void Dict_destroy(HashTable* table) {
    for (size_t i = 0; i < table->capacity; ++i) if (table->entries[i].key) free(table->entries[i].key);
    
    free(table->entries);
    free(table);
}

HashTable* Dict_create(void) {
    // Allocate space for hash table struct.
    HashTable* table = malloc(sizeof(HashTable));
    if (!table) return NULL;
    
    table->length = 0;
    table->capacity = INITIAL_CAPACITY;
    table->entries = calloc(INITIAL_CAPACITY, sizeof(Dict_entry_t));

    if (!table->entries) {
        free(table); 
        return NULL;
    }

    return table;
}