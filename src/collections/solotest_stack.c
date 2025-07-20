#include "../../include/solotest_stack.h"
#include "../../include/vector.h"
#include <stdio.h>
#include <stdlib.h>

#define VEC_UNWRAP(vec) \
	if (vec.v == VECE) { \
		perror("Unexpected error!\n"); \
		exit(1); \
	}


void solotest_stack_init(struct solotest_stack *stack)
{
	struct vec *vec = vec_init().d.vec;

	stack->stack_parts = vec;
	stack->size = 0;
	stack->cap = 0;
}

void solotest_stack_push(struct solotest_stack *stack, struct solotest_board *b)
{
	struct solotest_stack_part *part;

	if (stack->size == stack->cap) {
		part = (struct solotest_stack_part *)
			malloc(sizeof(struct solotest_stack_part));

		stack->cap += SOLOTEST_STACK_ALLOCATION_CHUNK;
		vec_append(stack->stack_parts, part);
	} else {
		part = (struct solotest_stack_part *)
			vec_get(stack->stack_parts, stack->size /
			SOLOTEST_STACK_ALLOCATION_CHUNK).d.element;
	}

	part->boards[stack->size % SOLOTEST_STACK_ALLOCATION_CHUNK] = b;

	stack->size++;
}

struct solotest_board *solotest_stack_pop(struct solotest_stack *stack)
{
	if (stack->size == 0)
		return NULL;

	struct solotest_stack_part *part;
	part = vec_get(stack->stack_parts,
		       (stack->size - 1) / SOLOTEST_STACK_ALLOCATION_CHUNK).d.element;

	stack->size--;

	return part->boards[stack->size % SOLOTEST_STACK_ALLOCATION_CHUNK];
}

void solotest_stack_destroy(struct solotest_stack *stack)
{
	while (stack->size)
		free(solotest_stack_pop(stack));

	while (stack->stack_parts->size)
		free(vec_pop(stack->stack_parts).d.element);

	vec_destroy(stack->stack_parts);
	free(stack);
}
