#include "Stack.h"
#include "HashTable.h"
#include <stdio.h>

int main() {
	
	HashTable *table = Dict_create();
	Dict_set(table, "key 1", (void*)0x5426);
	Dict_set(table, "key 2", (void*)0x6748);
	Dict_set(table, "key 3", (void*)0x5463);
	Dict_set(table, "key 4", (void*)0x3466);
	Dict_set(table, "key 6", (void*)0x5686);
	Dict_set(table, "key 7", (void*)0x7654);
	Dict_set(table, "key 8", (void*)0x2575);
	Dict_set(table, "key 9", (void*)0x2435);
	Dict_set(table, "key 10", (void*)0x3346);
	Dict_set(table, "key 11", (void*)0x2765);
	Dict_set(table, "key 12", (void*)0x2356);
	Dict_set(table, "key 13", (void*)0x3658);
	Dict_set(table, "key 14", (void*)0x5625);
	return 0;
}