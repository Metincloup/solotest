/*!
 * Core Solo Test board types and functions. This header defines the essential
 * structs, enums, and operations required to represent and manipulate
 * the board.
 *
 * Error checking, debugging utilities, and validity tests live in
 * {@code solotest_ext.h}.
 *
 * Assumes clean input and responsible usage by the solver implementation.
 * When used properly, these declarations are sufficient for a fully functional
 * and optimized Solo Test implementation.
 */

#ifndef SOLOTEST_H
#define SOLOTEST_H

#include <stdint.h>
#include <stdbool.h>


/**
 * Represents the state of a Solo Test board.
 */
struct solotest_board {
    /**
     * Bit-packed board representation.
     */
    uint64_t board;

    /**
     * Bitfield of pegs that can currently make a valid move.
     *
     * Top, right, bottom, left respectively.
     */
    uint64_t pegs_can_move[4];

    /**
     * Total number of pegs currently on the board.
     */
    uint8_t peg_count;
};

enum solotest_direction {
	SOLOTEST_DIRECTION_TOP,
	SOLOTEST_DIRECTION_RIGHT,
	SOLOTEST_DIRECTION_BOTTOM,
	SOLOTEST_DIRECTION_LEFT,
};


/**
 * Initializes the board to the starting state.
 */
void solotest_init(struct solotest_board *);

/**
 * Applies a move to the given board by moving a peg in the specified
 * direction.
 *
 * No error checking is performed; the caller is responsible for ensuring the
 * move is valid.
 */
void solotest_move(struct solotest_board *, int peg_index,
		   enum solotest_direction);

/**
 * Copies one board state into another.
 */
void solotest_copy(struct solotest_board *dst, const struct solotest_board *src);

/**
 * Returns the index corresponding to a bitfield with a single peg.
 */
int solotest_bitfield_to_index(uint64_t bitfield);

/**
 * Returns the bitfield representation of a peg at the given index.
 */
uint64_t solotest_index_to_bitfield(int index);

#endif // SOLOTEST_H
