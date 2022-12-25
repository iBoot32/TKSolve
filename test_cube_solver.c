#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include "miniunit.h"
#include "cube_solver.h"

static int _test_find_target_corner()
{
	mu_start();

	corners[0] = 'Y';
	corners[1] = 'G';
	corners[2] = 'R';
	mu_check(find_target_corner() == 15);

	corners[0] = 'O';
	corners[1] = 'W';
	corners[2] = 'B';
	mu_check(find_target_corner() == 1);

	corners[0] = 'B';
	corners[1] = 'Y';
	corners[2] = 'O';
	mu_check(find_target_corner() == 23);

	corners[0] = 'O';
	corners[1] = 'G';
	corners[2] = 'W';
	mu_check(find_target_corner() == 10);

	mu_end();
}

static int _test_edge_LUT()
{
	struct timeval stop, start;
	gettimeofday(&start, NULL);

	mu_start();

	// D2 F2 U' R2 B2 D' B2 L2 U L2 U' F L2 D2 L' B R D B2 L2
	solve_cube("GYOBRYRYGGWORWBBOWGWROBY", "BRBWRGOWWRYOWGRYBYYGOGBO");
	
	gettimeofday(&stop, NULL);
	printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 

	mu_end();
}

int main(int argc, char* argv[]) 
{
	mu_run(_test_find_target_corner);
	mu_run(_test_edge_LUT);
	
	return EXIT_SUCCESS;
}
