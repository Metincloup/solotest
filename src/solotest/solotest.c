#include "../../include/solotest.h"
#include "../../include/solotest_ext.h"

#include <stdint.h>


void solotest_init(struct solotest_board *restrict b) {
	b->peg_count = 32;
	b->board = 0x1fffeffff;
	b->pegs_can_move[0] = 0x10000000; // index 28
	b->pegs_can_move[1] = 0x4000; // index 14
	b->pegs_can_move[2] = 0x10; // index 4
	b->pegs_can_move[3] = 0x40000; // index 18
}

void solotest_copy(struct solotest_board *dst,
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

static inline void clear_peg(uint64_t *board, int index)
{
	if (index != -1)
		*board &= ~solotest_index_to_bitfield(index);
}

static inline void set_peg(uint64_t *board, int index)
{
	if (index != -1)
		*board |= solotest_index_to_bitfield(index);
}

static inline bool has_peg(uint64_t board, int index)
{
	if (index == -1)
		return 0;
	return (board | solotest_index_to_bitfield(index)) != 0;
}

void update_peg_can_move(struct solotest_board *b, int index)
{
	struct solotest_neighbor_indexes far_n = solotest_get_far_neighbors(index);
	struct solotest_neighbor_indexes n = solotest_get_neighbors(index);

	bool block = has_peg(b->board, index);

	// TODO: implement peg_can_move
	if (block) {
	} else {
	}
}

void solotest_move(struct solotest_board *b, int peg,
		   enum solotest_direction d) {
	struct solotest_neighbor_indexes far_n = solotest_get_far_neighbors(peg);
	struct solotest_neighbor_indexes n = solotest_get_neighbors(peg);

	int over = 0, to = 0;

	switch (d) {
	case SOLOTEST_DIRECTION_TOP:
		over = n.top;
		to = far_n.top;
		break;
	case SOLOTEST_DIRECTION_RIGHT:
		over = n.right;
		to = far_n.right;
		break;
	case SOLOTEST_DIRECTION_BOTTOM:
		over = n.bottom;
		to = far_n.bottom;
		break;
	case SOLOTEST_DIRECTION_LEFT:
		over = n.left;
		to = far_n.left;
		break;
	}

	clear_peg(&b->board, peg);
	clear_peg(&b->board, over);
	set_peg(&b->board, over);

	update_peg_can_move(b, peg);
	update_peg_can_move(b, over);
	update_peg_can_move(b, to);
}
