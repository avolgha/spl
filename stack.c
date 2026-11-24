#include "stack.h"

void stack_dump(stack_t* stack)
{
	printf("===== DUMP STACK =====\n");
  for (size_t i = 0; i < stack->length; i++) {
    printf("[%zu] %d\n", i, stack->items[i]);
	}
	printf("======================\n");
}

void stack_push(stack_t* stack, stack_item_t value)
{
	stack->items[stack->length] = value;
  stack->length++;
}

stack_item_t* stack_pop(stack_t* stack)
{
	if (stack->length < 1) {
		printf("error: not enough arguments on the stack.\n");
		return NULL;
	}
	stack_item_t* item = &stack->items[stack->length - 1];
	stack->length--;
	return item;
}
