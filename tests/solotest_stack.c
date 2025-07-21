#include "../include/solotest_stack.h"
#include <assert.h>
#include <stdlib.h>


int main()
{
	struct solotest_stack *stack;

	stack = malloc(sizeof(struct solotest_stack));
	solotest_stack_init(stack);

	struct solotest_board boards[128];

	for (int i = 0; i < 128; i++) {
		boards[i].board = i;
		solotest_stack_push(stack, &boards[i]);
	}

	for (int i = 0; i < 128; i++)
		assert(solotest_stack_pop(stack)->board == 127 - i);

	solotest_stack_destroy(stack);

	stack = malloc(sizeof(struct solotest_stack));
	solotest_stack_init(stack);

	for (int i = 0; i < 128; i++)
		solotest_stack_push(stack, malloc(sizeof(struct solotest_board *)));

	solotest_stack_destroy(stack);
}
