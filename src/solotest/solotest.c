#include "../../include/solotest.h"

#include <stdint.h>


void solotest_init(struct solotest_board *restrict b) {
	b->peg_count = 0;
	b->board = 0x1fffeffff;
	b->pegs_can_move[0] = 0x10000000; // index 28
	b->pegs_can_move[1] = 0x4000; // index 14
	b->pegs_can_move[2] = 0x10; // index 4
	b->pegs_can_move[3] = 0x40000; // index 18
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
