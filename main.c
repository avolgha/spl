#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "expression.h"
#include "stack.h"

// TODO: implement floating point numbers.

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("usage: %s <src>\n", argv[0]);
    return 1;
  }

  stack_t stack = {.items = {}, .length = 0};
  size_t i;
  size_t parse_result = parse_expression(&stack, argv[1], &i);
  if (parse_result < 0) {
    stack_dump(&stack);
    return -parse_result;
  }

  if (parse_result != 0 || stack.length > 1) {
    printf("error: all items on the stack need to be used.\n");
    stack_dump(&stack);
    return 1;
  }

  if (stack.length == 0) {
    printf("error: no items were added to the stack.\n");
    return 1;
  }

  printf("result: %d\n", stack.items[0]);
  return 0;
}
