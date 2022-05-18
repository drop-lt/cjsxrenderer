#include "HashTable.h"

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL
#define INITIAL_CAPACITY 16 

struct HashTable {
    ht_entry* entries;    // hash slots
    size_t capacity;      // size of _entries array
    size_t length;        // number of items in hash table
};

// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
static uint64_t hash_key(const char* key) {
    uint64_t hash = FNV_OFFSET;
    for (const char* p = key; *p++; hash ^= *p) hash *= FNV_PRIME;
    return hash;
}

static const char* ht_set_entry(ht_entry* entries, size_t capacity, const char* key, void* value, size_t* length) {
    size_t index;
    for (index = hash_key(key) & (capacity - 1); entries[index].key; index = ++index >= capacity ? 0 : index) 
        if (!strcmp(key, entries[index].key)) {
            entries[index].value = value; 
            return entries[index].key;
        }

    if (length && (key = _strdup(key))) (*length)++;
    
    entries[index].key = key;
    entries[index].value = value;
    return key;
}

static int ht_expand(HashTable* table) {
    size_t new_capacity = table->capacity << 1; 

    ht_entry* new_entries = calloc(new_capacity, sizeof(ht_entry));
    if (!new_entries) return 1;

    for (size_t i = 0; i < table->capacity; ++i) {
        ht_entry entry = table->entries[i];
        if (entry.key)  ht_set_entry(new_entries, new_capacity, entry.key, entry.value, NULL);
    }

    free(table->entries);
    table->entries = new_entries;
    table->capacity = new_capacity;
    return 0;
}

const char* Dict_set(HashTable* table, const char* key, void* value) {
    return table->length >= table->capacity / 2 && ht_expand(table) ? NULL : ht_set_entry(table->entries, table->capacity, key, value, &table->length);
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
    table->entries = calloc(INITIAL_CAPACITY, sizeof(ht_entry));

    if (!table->entries) {
        free(table); 
        return NULL;
    }

    return table;
}