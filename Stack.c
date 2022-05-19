#include "Stack.h"
#include <stdio.h>
struct Stack {
	void ** base_pointer; // pointer pointer so indexing it retunrs a void*
	size_t stack_size; 
};

/**
 * 
 * The actual diference between pop and peek is that peek doesnt decrease the stack_size pointer, so peeking twice will always give the same result
 * 
 */
void* Stack_pop(Stack* stack) {	return stack->base_pointer[--stack->stack_size - 1]; }

void* Stack_peek(const Stack* stack) { return stack->base_pointer[stack->stack_size - 1]; }


void* Stack_destroy(Stack* stack) {
	free(stack->base_pointer);     
	free(stack);
	return NULL;
}

/**
 * 
 * bp is a placeholder so that if realloc fails, the stack can be safely destructed instead of stack->base_pointer going null and leaking memory
 * if realloc succeds, bp's last item is set to the given value, then the stack's base pointer is assigned with bp
 * 
 */

int Stack_push(Stack* stack, void* value) {
	void** bp = (bp = realloc(stack->base_pointer, ++stack->stack_size * sizeof(void*))) ? (bp[stack->stack_size - 1] = value, stack->base_pointer = bp) : Stack_destroy(stack);
	return !bp; 
}

Stack* Stack_create(void) {
	Stack* newStack = malloc(sizeof(Stack));
	if (!newStack) return NULL;
	if (newStack->base_pointer = malloc(sizeof(void*))) {
		newStack->stack_size = 0;
		return newStack;
	}
	free(newStack);
	return NULL;
}