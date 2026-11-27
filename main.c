#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "expression.h"
#include "stack.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("usage: %s <src>\n", argv[0]);
    return 1;
  }

  stack_t stack = {.items = {0}, .length = 0};
  size_t i = 0;
  int parse_result = parse_expression(&stack, argv[1], &i);
  if (parse_result < 0) {
    stack_dump(&stack);
    return -parse_result;
  }

  if (parse_result != 0 || stack.length > 1) {
    printf("error: all items on the stack need to be used. (%s:%d :: "
           "parse_result=%d :: stack.length=%zu)\n",
           __FILE__, __LINE__, parse_result, stack.length);
    stack_dump(&stack);
    return 1;
  }

  if (stack.length == 0) {
    printf("error: no items were added to the stack.\n");
    return 1;
  }

  printf("result: %Lf\n", stack.items[0]);
  return 0;
}
