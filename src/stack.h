#pragma once
#include <stdlib.h>

#define STACK_SIZE 64

typedef long double stack_item_t;
typedef struct {
  size_t length;
  stack_item_t items[STACK_SIZE];
} stack_t;

void stack_dump(stack_t *stack);
void stack_push(stack_t *stack, stack_item_t value);
void stack_append(stack_t *dest, stack_t *src);
stack_item_t *stack_pop(stack_t *stack);
