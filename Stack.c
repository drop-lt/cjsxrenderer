#include "Stack.h"
#include <stdio.h>
struct Stack {
	void ** basePointer;
	size_t stack_size;
};

void* Stack_pop(Stack* stack) {	return stack->basePointer[--stack->stack_size - 1]; }

void* Stack_peek(const Stack* stack) { return stack->basePointer[stack->stack_size - 1]; }

void* Stack_destroy(Stack* stack) {
	free(stack->basePointer);
	free(stack);
	return NULL;
}

int Stack_push(Stack* stack, void* value) {
	void** bp = (bp = realloc(stack->basePointer, ++stack->stack_size * sizeof(void*))) ? (stack->basePointer = bp, stack->basePointer[stack->stack_size - 1] = value) : Stack_destroy(stack);
	return !!bp; 
}

Stack* Stack_create(void) {
	Stack* newStack = malloc(sizeof(Stack));
	if (!newStack) return NULL;
	if (newStack->basePointer = malloc(sizeof(void*))) {
		newStack->stack_size = 0;
		return newStack;
	}
	free(newStack);
	return NULL;
}