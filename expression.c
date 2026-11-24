#include <ctype.h>
#include <string.h>
#include "expression.h"

int binary_operation(stack_t* stack, stack_item_t (*func)(stack_item_t, stack_item_t))
{
	if (stack->length < 2) {
		printf("error: not enough arguments on the stack.\n");
		return 1;
	}
	stack_item_t* two = stack_pop(stack);
	stack_item_t* one = stack_pop(stack);
	stack_push(stack, func(*one, *two));
	return 0;
}

stack_item_t op_add(stack_item_t a, stack_item_t b) { return a + b; }
stack_item_t op_sub(stack_item_t a, stack_item_t b) { return a - b; }
stack_item_t op_mul(stack_item_t a, stack_item_t b) { return a * b; }
stack_item_t op_mod(stack_item_t a, stack_item_t b) { return a % b; }

int parse_expression(stack_t* stack, char src[], size_t* i)
{
	size_t srclen = strlen(src);
	if (i == NULL || *i < 0 || *i >= srclen) return -1; 

	char buf[32]; // i dont suspect users to input a number of (hopefully) only size 10^32-1 ...
  while (1) {
		if (src[*i] == ')' || src[*i] == '\0' || *i >= srclen) {
			break;
		} else if (isdigit(src[*i]) || (src[*i] == '-' && *i+1 < srclen && isdigit(src[*i+1]))) {
			size_t buf_i = 0;
			if (src[*i] == '-') {
				buf[0] = '-';
				buf_i++;
				(*i)++;
			}

			while (isdigit(src[*i]) && *i < srclen) {
				buf[buf_i] = src[*i];
				buf_i++; (*i)++;
			}

			buf[buf_i] = '\0';

			int32_t num = strtol(buf, NULL, 10);
			memset(buf, 0, sizeof(buf));
			stack_push(stack, num);
			continue;
		}

		switch(src[*i]) {
			case ' ': break;
			case '(':
				if (++*i >= srclen) {
					printf("error: found open parenthesis but nothing following it.\n");
					return -1;
				}

				int result = parse_expression(stack, src, i);
				if (result != 0) return result;
				break;
			case '+': if (binary_operation(stack, op_add) != 0) return 1; break;
			case '*': if (binary_operation(stack, op_mul) != 0) return 1; break;
			case '%': if (binary_operation(stack, op_mod) != 0) return 1; break;	
			case '-':	if (binary_operation(stack, op_sub) != 0) return 1; break;
			default:
				printf("error: unknown operator '%c' (pos: %zu, code: %d).\n", src[*i], *i, src[*i]);
				return -1;
		}

		(*i)++;
  }

	return strlen(buf);
}
