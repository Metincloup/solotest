#include "../../include/solotest.h"
#include "../../include/solotest_ext.h"
#include "../../include/solotest_play.h"

#include <stdint.h>
#include <stdio.h>


void solotest_play() {
	struct solotest_board board;
	int peg, direction;
	int peg_count = 32;
	uint64_t bitfield_index;

	solotest_init(&board);

	printf("Enter -1 to exit\n");
	while (true) {
		printf("\n");
		solotest_print_board(board.board);

		int no_move = 1;
		for (int i = 0; i < 4; i++)
			if (board.pegs_can_move[i]) {
				no_move = 0;
				break;
			}

		if (no_move) {
			printf("\nGame over! %d pegs remaining.\n", peg_count);
			break;
		}

		printf("\nBoard Indexes:\n");
		solotest_print_indices();

		printf("\nMove peg .. to .. (0: top, 1: right, "
		       "2: bottom, 3: left)\n");

		if (!scanf("%d", &peg))
			goto exit_error;

		if (peg == -1)
			break;

		if (!scanf("%d", &direction))
			goto exit_error;

		bitfield_index = solotest_index_to_bitfield(peg);
		if (direction < 0 || direction > 3 ||
		    !(board.pegs_can_move[direction] & bitfield_index)) {
			printf("Invalid move!\n");
			continue;
		}

		peg_count--;
		solotest_move(&board, peg, direction);
	}

	return;

exit_error:
	perror("Unexpected error");
}
