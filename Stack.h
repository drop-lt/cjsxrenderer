#ifndef STACK_H
#define STACK_H
#include <stdint.h>
#include <stdlib.h>

typedef struct Stack Stack;

/**
 * @brief create a new Stack
 * 
 * @return a heap-allocated Stack object 
 */
Stack* Stack_create(void);

/**
 * @brief push a new item into the specified stack
 * 
 * @param stack: the stack object
 * @param value: the value to push
 * 
 * @return 0 on success and 1 on fail
 */
int Stack_push(Stack* stack, void* value);

/**
 * @brief pop the last item from the stack
 * 
 * @param stack: the stack object
 * 
 * @return the last item of the stack
 */
void* Stack_pop(Stack* stack);

/**
 * @brief peek the last item in the stack
 * 
 * @param a stack object, can be constant because peeking doesnt change the object
 * 
 * @return the last item on the stack
 */
void* Stack_peek(const Stack* stack);

/**
 * @brief delete a stack object
 * 
 * @param stack: the stack to be deleted
 * 
 * @return NULL, always
 */
void* Stack_destroy(Stack* stack);

#endif // !STACK_H


