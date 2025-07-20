#include "../../include/solotest.h"
#include "../../include/solotest_ext.h"

#include <stdint.h>
#include <stdio.h>
#include <pthread.h>

static pthread_once_t neighbors_initialized = PTHREAD_ONCE_INIT;
static struct solotest_neighbor_indexes NEIGHBOR_INDEXES[33];
static struct solotest_neighbor_indexes NEIGHBOR_FAR_INDEXES[33];

void initialize_neighbor_indices()
{
	for (int i = 0; i < 33; i++)
		NEIGHBOR_FAR_INDEXES[i] = NEIGHBOR_INDEXES[i] = \
			(struct solotest_neighbor_indexes) {
				.top = -1,
				.right = -1,
				.bottom = -1,
				.left = -1
			};
}

struct solotest_neighbor_indexes solotest_get_neighbors(int peg_index) {
	pthread_once(&neighbors_initialized, initialize_neighbor_indices);
	return NEIGHBOR_INDEXES[peg_index];
}

struct solotest_neighbor_indexes solotest_get_far_neighbors(int peg_index) {
	pthread_once(&neighbors_initialized, initialize_neighbor_indices);
	return NEIGHBOR_FAR_INDEXES[peg_index];
}


void solotest_print_indices() {
	int i, j, index = 0;
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 7; j++) {
			if ((i >= 2 && i <= 4) || (j >= 2 && j <= 4)) {
				printf("%2d ", index++);
			} else {
				printf("   ");
			}
		}
		printf("\n");
	}
}

void solotest_print_board(uint64_t board) {
	int i, j;
	uint64_t index = 0;

	for (i = 0; i < 7; i++) {
		for (j = 0; j < 7; j++) {
			if ((i >= 2 && i <= 4) || (j >= 2 && j <= 4)) {
				printf("%c ",
				       (solotest_index_to_bitfield(index) & board) ?
				       '#' : '.');
				index++;
			} else {
				printf("  ");
			}
		}
		printf("\n");
	}
}
