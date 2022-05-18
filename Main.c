#include "Stack.h"
#include <stdio.h>

int main() {

	Stack* stack = Stack_create();
	Stack_push(stack, (void *)0x5345);
	printf("value at strack currently is %p\n", Stack_peek(stack));
	Stack_destroy(stack);
	

	return 0;
}