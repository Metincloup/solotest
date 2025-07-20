#include "../../include/solotest.h"
#include "../../include/solotest_ext.h"

#include <stdint.h>


void solotest_init(struct solotest_board *restrict b) {
	b->peg_count = 0;
	b->board = 0x1fffeffff;
	b->pegs_can_move[0] = 0x10000000; // index 28
	b->pegs_can_move[1] = 0x4000; // index 14
	b->pegs_can_move[2] = 0x10; // index 4
	b->pegs_can_move[3] = 0x40000; // index 18
}

void solotest_clone(struct solotest_board *dst,
		    const struct solotest_board *src) {
	dst->peg_count = src->peg_count;
	dst->board = src->board;
	dst->pegs_can_move[0] = src->pegs_can_move[0];
	dst->pegs_can_move[1] = src->pegs_can_move[1];
	dst->pegs_can_move[2] = src->pegs_can_move[2];
	dst->pegs_can_move[3] = src->pegs_can_move[3];
}

// See https://graphics.stanford.edu/~seander/bithacks.html#ZerosOnRightBinSearch
// for counting trailing zeros bit magic.
inline int solotest_bitfield_to_index(uint64_t bitfield) {
	// Special case for odd v (assumed to happen half of the time)
	if (bitfield & 0x1)
		return 0;

	int c = 1;

	if ((bitfield & 0xffffffff) == 0) {
		bitfield >>= 32;
		c += 32;
	}
	if ((bitfield & 0xffff) == 0) {
		bitfield >>= 16;
		c += 16;
	}
	if ((bitfield & 0xff) == 0) {
		bitfield >>= 8;
		c += 8;
	}
	if ((bitfield & 0xf) == 0) {
		bitfield >>= 4;
		c += 4;
	}
	if ((bitfield & 0x3) == 0) {
		bitfield >>= 2;
		c += 2;
	}
	c -= bitfield & 0x1;

	return c;
}

inline uint64_t solotest_index_to_bitfield(int index) {
	return (uint64_t) 1 << index;
}


static inline uint64_t set_board_index(uint64_t board, int index)
{
	return index == -1 ? board : board | solotest_index_to_bitfield(index);
}

static inline uint64_t clear_board_index(uint64_t board, int index)
{
	return index == -1 ? board : board & ~solotest_index_to_bitfield(index);
}

static inline uint64_t get_board_index(uint64_t board, int index)
{
	return index == -1 ? 0 : board & solotest_index_to_bitfield(index);
}



static inline void place_peg(struct solotest_board *b, int index) {
	b->board = set_board_index(b->board, index);
}
static inline void block_move_to(struct solotest_board *b, int index) {
	struct solotest_neighbor_indexes farn = solotest_get_far_neighbors(index);
	b->pegs_can_move[0] = clear_board_index(b->pegs_can_move[0], farn.bottom);
	b->pegs_can_move[1] = clear_board_index(b->pegs_can_move[1], farn.left);
	b->pegs_can_move[2] = clear_board_index(b->pegs_can_move[2], farn.top);
	b->pegs_can_move[3] = clear_board_index(b->pegs_can_move[3], farn.right);
}

static inline void clear_peg(struct solotest_board *b, int index) {
	b->board = clear_board_index(b->board, index);
}

static inline void free_to_move(struct solotest_board *b, int index) {
	struct solotest_neighbor_indexes farn = solotest_get_far_neighbors(index);
	struct solotest_neighbor_indexes n = solotest_get_neighbors(index);

	if (get_board_index(b->board, n.bottom) &&
	    get_board_index(b->board, farn.bottom))
		b->pegs_can_move[0] =
			set_board_index(b->pegs_can_move[0], farn.bottom);

	if (get_board_index(b->board, n.left) &&
	    get_board_index(b->board, farn.left))
		b->pegs_can_move[1] =
			set_board_index(b->pegs_can_move[1], farn.left);

	if (get_board_index(b->board, n.top) &&
	    get_board_index(b->board, farn.top))
		b->pegs_can_move[2] =
			set_board_index(b->pegs_can_move[2], farn.top);

	if (get_board_index(b->board, n.right) &&
	    get_board_index(b->board, farn.right))
		b->pegs_can_move[3] =
			set_board_index(b->pegs_can_move[3], farn.right);
}


void solotest_move(struct solotest_board *b, int peg_index,
		   enum solotest_direction d) {
	struct solotest_neighbor_indexes farn =
		solotest_get_far_neighbors(peg_index);
	struct solotest_neighbor_indexes n =
		solotest_get_neighbors(peg_index);

	int clear = 0;
	int place = 0;

	switch (d) {
	case SOLOTEST_DIRECTION_TOP:
		clear = n.top;
		place = farn.top;
		break;
	case SOLOTEST_DIRECTION_RIGHT:
		clear = n.right;
		place = farn.right;
		break;
	case SOLOTEST_DIRECTION_BOTTOM:
		clear = n.bottom;
		place = farn.bottom;
		break;
	case SOLOTEST_DIRECTION_LEFT:
		clear = n.left;
		place = farn.left;
		break;
	}

	clear_peg(b, peg_index);
	clear_peg(b, clear);
	place_peg(b, place);

	free_to_move(b, peg_index);
	free_to_move(b, clear);
	block_move_to(b, place);
}
