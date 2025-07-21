#include "../include/solotest_ext.h"
#include <stdio.h>


void print_neighbors()
{
	uint64_t board;
	struct solotest_neighbor_indexes neighbors;

	for (int i = 0; i < 33; i++) {
		board = 0;
		neighbors = solotest_get_far_neighbors(i);
		if (neighbors.top != -1)
			board |= solotest_index_to_bitfield(neighbors.top);
		if (neighbors.right != -1)
			board |= solotest_index_to_bitfield(neighbors.right);
		if (neighbors.bottom != -1)
			board |= solotest_index_to_bitfield(neighbors.bottom);
		if (neighbors.left != -1)
			board |= solotest_index_to_bitfield(neighbors.left);

		solotest_print_board(board);
		printf("\n------------------\n");
	}
}

int main()
{
	print_neighbors();
}
