#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/time.h>
#include "miniunit.h"
#include "cube_solver.h"
#include "calc.h"
#include <assert.h>
#include <string.h>

int _solve_every_2x2_from_file_and_report_speed()
{
	//
	// This test will solve every cornerstring given in "solutions.txt".
	// Just make sure each cornerstring is given on a new, blank line.
	//

	mu_start();

	char **lines = NULL;
	int num_lines = 0;


	FILE *file = fopen("states.txt", "r");
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

	printf("\n\nRead %i lines\n", num_lines);


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

int _test_calc()
{
	mu_start();

	char solved_corners[] = "WOBWRBWRGWOGYOGYRGYRBYOB"; 
	char moves[] = "ndnbhjcqdqlncnilrlql"; // F' U F' R' L' D R2 B' U B' D2 F' R2 F' L2 D2 B2 D2 B' D2
	int size = sizeof(moves) / sizeof(moves[0]);

	calc(solved_corners, moves, size - 1); // -1 due to \0
	
	mu_check(strcmp(solved_corners, "WRGBOWYGRBRYOGYBYOWBRWOG") == 0);

	mu_end();
}

int _hamilton_to_cubestate_txt()
{
	mu_start();

	char solved_corners[] = "WOBWRBWRGWOGYOGYRGYRBYOB"; 
	FILE *fp;
    int c;
	int count = 1;
	char move;

	static const char hamilton_to_calc[] =
	{
    	['R'] = 'a',
		['U'] = 'd',
		['F'] = 'm',
		['S'] = 'b',
		['V'] = 'e',
		['G'] = 'n'
	};

    // Open the files for reading
	FILE *txt = fopen("states.txt", "w");
    fp = fopen("Hamilton222.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read each character from the file until EOF is reached
    while ((c = fgetc(fp)) != EOF) {
        // Perform some action on the character
		if (c != '\n' && c != '\r')
		{
			move = hamilton_to_calc[c];
			calc(solved_corners, &move, 1);
			printf("state #%i = %s\r", count++, solved_corners);
			fprintf(txt, "%s\n", solved_corners);
		}
    }
	printf("\n");

    // Close the file
    fclose(fp);
	fclose(txt);

	mu_end();
}

int main(int argc, char* argv[]) 
{
	//mu_run(_solve_every_2x2_from_file_and_report_speed);
	//mu_run(_test_edge_LUT);
	//mu_run(_test_calc);
	mu_run(_hamilton_to_cubestate_txt);
	mu_run(_solve_every_2x2_from_file_and_report_speed);
	
	return EXIT_SUCCESS;
}
