#include "../include/solotest.h"

#include <assert.h>
#include <stdint.h>


void t_peg_index_bitfield_conversion()
{
	for (uint64_t i = 0; i < 63; i++) {
		uint64_t bitfield = (uint64_t) 1 << i;

		assert(bitfield == solotest_index_to_bitfield(i));
		assert(i == solotest_bitfield_to_index(bitfield));
	}
}


int main()
{
	t_peg_index_bitfield_conversion();
}
