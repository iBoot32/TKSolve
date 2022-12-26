#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include "miniunit.h"
#include "cube_solver.h"
#include <assert.h>
#include <string.h>

static int _solve_every_2x2_from_file_and_report_speed()
{
	//
	// This test will solve every cornerstring given in "solutions.txt".
	// Just make sure each cornerstring is given on a new, blank line.
	//

	mu_start();

	char **lines = NULL;
	int num_lines = 0;


	FILE *file = fopen("solutions.txt", "r");
	mu_check(file != NULL);

	char line[1000];
	while (fgets(line, 1000, file) != NULL) {
		// Check if line has any spaces
		if (strchr(line, ' ') == NULL) {
			// Check if line is not blank
			if (strlen(line) > 3) {
				// Add line to array
				lines = realloc(lines, (num_lines + 1) * sizeof(char *));
				lines[num_lines] = strdup(line);
				num_lines++;
				printf("Reading line %i\r", num_lines);
			}
		}
	}

	int cube_idx = 0;
	printf("\n\nRead %i lines\n", num_lines);
	printf("Solving cube %i\r", cube_idx);


	struct timeval stop, start;
	gettimeofday(&start, NULL);

	for (size_t i = 0; i < num_lines; i++)
	{
		//printf("solving %li\r", i + 1);
		solve_cube(lines[i] , "WBWRWGWOBOGOGRBRYGYRYBYO");
	}

	gettimeofday(&stop, NULL);
	printf("took %lu us to solve %i cubes \n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec, num_lines); 
	
	mu_end();
}

/*static int _test_edge_LUT()
{
	//
	// This test will solve a given cube and report solve time in us.
	//

	struct timeval stop, start;
	gettimeofday(&start, NULL);

	mu_start();

	// D2 F2 U' R2 B2 D' B2 L2 U L2 U' F L2 D2 L' B R D B2 L2
	//solve_cube("GYOBRYRYGGWORWBBOWGWROBY", "BRBWRGOWWRYOWGRYBYYGOGBO");

	solve_cube("GRYBYOWGORWGBYRRBWWOBGOY", "RGOBWBWOOGYGRBWRGWRYYOYB");
	
	gettimeofday(&stop, NULL);
	printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec); 

	mu_end();
}*/

int main(int argc, char* argv[]) 
{
	mu_run(_solve_every_2x2_from_file_and_report_speed);
	//mu_run(_test_edge_LUT);
	
	return EXIT_SUCCESS;
}
