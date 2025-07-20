/*!
 * Utilities for validity checking and debugging.
 */

#ifndef SOLOTEST_EXT_H
#define SOLOTEST_EXT_H

#include "solotest.h"


/**
 * List of valid directions peg can move to.
 */
struct solotest_valid_directions {
	bool top;
	bool right;
	bool bottom;
	bool left;
};

enum solotest_neighbor {
	SOLOTEST_NEIGHBOR_EMPTY,
	SOLOTEST_NEIGHBOR_PEG,
	SOLOTEST_NEIGHBOR_OUT,
};

/**
 * Neighbor states for each cardinal direction.
 */
struct solotest_neighbors {
	enum solotest_neighbor top;
	enum solotest_neighbor right;
	enum solotest_neighbor bottom;
	enum solotest_neighbor left;
};


/**
 * Returns the neighbor states of the peg at the given index.
 */
struct solotest_neighbors solotest_get_neighbors(const struct solotest_board *,
						 int peg_index);

struct solotest_valid_directions solotest_get_valid_directions(const struct solotest_board *,
							       int peg_index);

#endif //SOLOTEST_EXT_H
