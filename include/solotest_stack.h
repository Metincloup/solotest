/*!
 * Stack implementation for storing {@code struct solotest_board} values.
 * Optimized for bulk allocation in fixed-size chunks.
 *
 * Assumes no memory allocation failures will occur.
 */

#ifndef SOLOTEST_STACK_H
#define SOLOTEST_STACK_H

#include "vector.h"
#include "solotest.h"
#include <stddef.h>

#define SOLOTEST_STACK_ALLOCATION_CHUNK 16


/**
 * Internal fixed-size array of boards.
 */
struct solotest_stack_part {
	struct solotest_board *boards[SOLOTEST_STACK_ALLOCATION_CHUNK];
};

/**
 * Dynamic stack for storing Solo Test board states.
 */
struct solotest_stack {
	struct vec *stack_parts;
	size_t size;
	size_t cap;
};


/**
 * Initializes an empty stack.
 */
void solotest_stack_init(struct solotest_stack *);

/**
 * Pushes a board to the stack.
 */
void solotest_stack_push(struct solotest_stack *, struct solotest_board *);

void solotest_stack_destroy(struct solotest_stack *);

/**
 * Pops the most recent board from the stack.
 */
struct solotest_board *solotest_stack_pop(struct solotest_stack *);


#endif // SOLOTEST_STACK_H

