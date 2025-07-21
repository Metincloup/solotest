#include "../../include/solotest.h"
#include "../../include/solotest_ext.h"

#include <stdint.h>
#include <stdio.h>
#include <pthread.h>


static pthread_once_t neighbors_initialized = PTHREAD_ONCE_INIT;
static struct solotest_neighbor_indexes NEIGHBOR_INDEXES[33];
static struct solotest_neighbor_indexes NEIGHBOR_FAR_INDEXES[33];
static int INDEX_MAP[7][7];


// Lazy initialization/cache for neighbors and index map.
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

	int index = 0;

	for (int j = 0; j < 7; j++) {
		for (int i = 0; i < 7; i++) {
			if ((i >= 2 && i <= 4) || (j >= 2 && j <= 4)) {
				INDEX_MAP[j][i] = index;
				index++;
			} else {
				INDEX_MAP[j][i] = -1;
			}
		}
	}

	for (int j = 0; j < 7; j++) {
		for (int i = 0; i < 7; i++) {
			index = INDEX_MAP[j][i];

			if (index == -1)
				continue;

			// top
			if (j > 0)
				NEIGHBOR_INDEXES[index].top = INDEX_MAP[j - 1][i];
			if (j > 1)
				NEIGHBOR_FAR_INDEXES[index].top = INDEX_MAP[j - 2][i];

			// right
			if (i < 6)
				NEIGHBOR_INDEXES[index].right = INDEX_MAP[j][i + 1];
			if (i < 5)
				NEIGHBOR_FAR_INDEXES[index].right = INDEX_MAP[j][i + 2];

			// bottom
			if (j < 6)
				NEIGHBOR_INDEXES[index].bottom = INDEX_MAP[j + 1][i];
			if (j < 5)
				NEIGHBOR_FAR_INDEXES[index].bottom = INDEX_MAP[j + 2][i];

			// left
			if (i > 0)
				NEIGHBOR_INDEXES[index].left = INDEX_MAP[j][i - 1];
			if (i > 1)
				NEIGHBOR_FAR_INDEXES[index].left = INDEX_MAP[j][i - 2];
		}
	}
}

inline struct solotest_neighbor_indexes solotest_get_neighbors(int peg_index) {
	pthread_once(&neighbors_initialized, initialize_neighbor_indices);
	return NEIGHBOR_INDEXES[peg_index];
}

inline struct solotest_neighbor_indexes solotest_get_far_neighbors(int peg_index) {
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
				printf("%s ",
				       (solotest_index_to_bitfield(index) & board) ?
				       "##" : "..");
				index++;
			} else {
				printf("   ");
			}
		}
		printf("\n");
	}
}
