#include "../include/solotest_play.h"
#include "../include/solotest_solver.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main()
{
	int selection;
	errno = EINVAL;  // perror() function appends errno at the end. Previous one was returning "success"
	
	printf("=== SOLO TEST ===\n"
	       "Select game mode:\n"
	       "1 - Play!\n"
	       "2 - Solve the problem\n"
	       "Selection (1/2): ");

	if (!scanf("%d", &selection)) {
		perror("Unexpected error!");
		return 1;
	}

	if (selection == 1) {
		solotest_play();
	} if (selection == 2) {
		solotest_solver();
	} 
	
	printf("Unknown option!");
	// return 1 just like line 21
	return 1;
}
