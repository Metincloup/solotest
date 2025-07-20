/*!
 * Utilities for validity checking and debugging.
 */

#ifndef SOLOTEST_EXT_H
#define SOLOTEST_EXT_H

#include "solotest.h"


/**
 * A collection of 4 index.
 */
struct solotest_neighbor_indexes {
	int top;
	int right;
	int bottom;
	int left;
};


/**
 * Returns the neighbor indexes of the peg at the given index.
 */
struct solotest_neighbor_indexes solotest_get_neighbors(int peg_index);

/**
 * Returns the indexes of neighbors that are two tiles away (i.e., one peg
 * in between).
 */
struct solotest_neighbor_indexes solotest_get_far_neighbors(int peg_index);

/**
 * Prints board index layout for visualization.
 */
void solotest_print_indices();

/**
 * Prints current peg positions on the board.
 */
void solotest_print_board(uint64_t);

#endif //SOLOTEST_EXT_H
