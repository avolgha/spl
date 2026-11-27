#include "expression.h"

#include <ctype.h>
#include <errno.h>
#include <string.h>

int binary_operation(stack_t *stack,
                     stack_item_t (*func)(stack_item_t, stack_item_t)) {
  if (stack->length < 2) {
    printf("error: not enough arguments on the stack.\n");
    return 1;
  }
  stack_item_t *two = stack_pop(stack);
  stack_item_t *one = stack_pop(stack);
  stack_push(stack, func(*one, *two));
  return 0;
}

stack_item_t op_add(stack_item_t a, stack_item_t b) { return a + b; }
stack_item_t op_sub(stack_item_t a, stack_item_t b) { return a - b; }
stack_item_t op_mul(stack_item_t a, stack_item_t b) { return a * b; }
stack_item_t op_div(stack_item_t a, stack_item_t b) { return a / b; }
stack_item_t op_mod(stack_item_t a, stack_item_t b) { return fmod(a, b); }

int parse_expression(stack_t *dest, char src[], size_t *i) {
  size_t srclen = strlen(src);
  if (i == NULL || *i < 0 || *i >= srclen) {
    return -1;
  }

  while (1) {
    if (src[*i] == ')' || src[*i] == '\0' || *i >= srclen) {
      break;
    } else if (isdigit(src[*i]) ||
               (src[*i] == '-' && *i + 1 < srclen && isdigit(src[*i + 1]))) {
      char buf[64];
      size_t buf_i = 0;
      if (src[*i] == '-') {
        buf[0] = '-';
        buf_i++;
        (*i)++;
      }

      // TODO: let the user input decimal values with points.

      while (isdigit(src[*i]) && *i < srclen) {
        buf[buf_i] = src[*i];
        buf_i++;
        (*i)++;
      }

      buf[buf_i] = '\0';

      char *e;
      errno = 0;
      stack_item_t num = strtold(buf, &e);
      if (*e != '\0' || errno != 0) {
        printf("error: could not parse input as long double. (input=\"%s\")",
               buf);
        return -1;
      }

      memset(buf, 0, sizeof(buf));
      stack_push(dest, num);
      continue;
    }

    switch (src[*i]) {
    case ' ':
      break;
    case '(':
      if (++*i >= srclen) {
        printf("error: found open parenthesis but nothing following it.\n");
        return -1;
      }

      stack_t expr_stack = {.items = {0}, .length = 0};
      int result = parse_expression(&expr_stack, src, i);
      if (result != 0)
        return result;
      if (expr_stack.length != 1) {
        printf("error: all items on the stack need to be used. "
               "(expression.c:83)\n");
        stack_dump(&expr_stack);
        return -1;
      }
      stack_append(dest, &expr_stack);
      break;
    case '+':
      if (binary_operation(dest, op_add) != 0)
        return 1;
      break;
    case '-':
      if (binary_operation(dest, op_sub) != 0)
        return 1;
      break;
    case '*':
      if (binary_operation(dest, op_mul) != 0)
        return 1;
      break;
    case '/':
      if (binary_operation(dest, op_div) != 0)
        return 1;
      break;
    case '%':
      if (binary_operation(dest, op_mod) != 0)
        return 1;
      break;
    default:
      printf("error: unknown operator '%c' (pos: %zu, code: %d).\n", src[*i],
             *i, src[*i]);
      return -1;
    }

    (*i)++;
  }

  return 0;
}
