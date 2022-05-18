#ifndef STACK_H
#define STACK_H
#include <stdint.h>
#include <stdlib.h>

typedef struct Stack Stack;

Stack* Stack_create(void);
int Stack_push(Stack*, void* value);
void* Stack_pop(Stack*);
void* Stack_peek(const Stack*);
void* Stack_destroy(Stack*);

#endif // !STACK_H