#include "../../include/solotest_solver.h"
#include "../../include/solotest_stack.h"
#include "../../include/solotest_ext.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


void solotest_solver()
{
	struct solotest_stack *stack = malloc(sizeof(struct solotest_stack));
	struct solotest_board *board = malloc(sizeof(struct solotest_board));
	struct solotest_board *current = NULL;
	struct solotest_board *copy;

	solotest_init(board);

	int iterations = 0;
	int target_pins = 3;

	solotest_stack_init(stack);
	solotest_stack_push(stack, board);

	while (stack->size) {
		current = solotest_stack_pop(stack);
		iterations++;

		if (current->peg_count <= target_pins) {
			break;
		}

		// TODO: OPTIMIZE BIT SEARCH
		for (int i = 0; i < 4; i++) {
			int64_t can_move = current->pegs_can_move[i];
			if (!can_move)
				continue;

			for (int j = 0; j < 33; j++) {
				if (!(solotest_index_to_bitfield(j) & can_move))
					continue;

				copy = malloc(sizeof(struct solotest_board));
				solotest_copy(copy, current);
				solotest_move(copy, j, i);

				solotest_stack_push(stack, copy);
			}
		}

		if (current) {
			free(current);
			current = NULL;
		}
	}

	if (current)
		solotest_print_board(current->board);

	solotest_stack_destroy(stack);
}
