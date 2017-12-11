#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>


int endCol;
int endRow;
int rows;
int cols;
int x_dimension;
int y_dimension;

bool solve(int row, int col, char maze[y_dimension][x_dimension + 1]) {
	/* Returns false if it goes outside the bounds or starts on something other than a space.
	 * This is NOT the checker for an unsolveable maze. Rather, this checks for an invalid start point.
	 */
	if (row < 0 || col < 0 || row >= rows || col >= cols || maze[row][col] != ' ') {
		return false;
	}

	maze[row][col] = '*';

	/* This part takes care of making the output pretty for the user.
	 * Waits 5 * 1000 nano seconds (5 ms), then prints the current maze.
	 * The outputs are a little fucked, which is why the 2 last printfs.
	 * But it is portable to different maze sizes, so nbd.
	 */
	usleep(5 * 1000);
	for (int i = 0; i < y_dimension - 1; i++) {
		printf("Line #: %3d: %s", i, maze[i]);
	}
	printf("Line #: %3d: %s", y_dimension - 1, maze[y_dimension - 1]);
	printf("Line #: %3d: %s", y_dimension, maze[y_dimension]);
	printf("\n");
	
	/* Returns true when the maze is solved. Pretty self explanitory. */
	if (row == endRow && col == endCol) {
		return true;
	}

	/* This is the recursion bit. Config can be changed, but it first checks right, then down, then left, then up. 
	 * This will return true if the maze solved bit above ^^ returns true.
	 */
	if (solve(row, col + 1, maze) || solve(row + 1, col, maze) || solve(row, col - 1, maze) || solve(row - 1, col, maze)) {
		return true;
	}
	
	/*maze[row][col] = ' '; */
	maze[row][col] = '0';
	return false;
}

/* Gets the X and Y width/length of the maze from the file.
 * Reads the maze line by line, sets result[]'s values accordingly.
 */

int get_line_length(char* filename, int (*result)[2]) {
	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	stream = fopen(filename, "r");
	if (stream == NULL) {
		exit(EXIT_FAILURE);
	}
	int i = 0;
	int line_length = 0;
	while ((read = getline(&line, &len, stream)) != -1) {
		if (i == 0) {
			line_length = (int) read;
		}
		i++;
	}
	i--;
	(*result)[0] = line_length;
	(*result)[1] = i;
	free(line);
	fclose(stream);
}

int main(int argc, char* argv[]) {
	if (argc == 1) {
		fprintf(stderr, "Must supply maze file as an argument!");
	}
	
	/* Grab the maze file */
	FILE *fp;
	fp = fopen(argv[1], "r");
	
	if (fp == NULL) {
		fprintf(stderr, "No such file found!\n");
	}

	/* Initialize the maze char[][] array */
	/* Get the length of one maze line */
	int result[2] = {0};
	get_line_length(argv[1], &result);
	/* x_dimension = line length */
	x_dimension = result[0];
	/* y_dimension = # of lines */
	y_dimension = result[1];
	char maze[y_dimension][x_dimension + 1];
	char tmaze[x_dimension + 1];
	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	stream = fopen(argv[1], "r");
	int i = 0;
	while ((read = getline(&line, &len, stream)) != -1) {
		strncpy(tmaze, line, x_dimension + 1);
		strcpy(maze[i], tmaze);
		/* PRINTS A LINE OF THE MAZE EACH TIME IT IS READ. LEAVING UNPRINTED NOW.
		printf("%s", tmaze); */
		i++;
	}
	free(line);
	fclose(stream);

	/* Now it's time to solve the damn thing lmao */
	endCol = x_dimension - 3;
	endRow = y_dimension - 1;
	cols = x_dimension;
	rows = y_dimension;
    bool t = solve(1, 1, maze);	
	if (t) {
		printf("Maze Solved!\n");
	} else {
		printf("Maze has NO solution!\n");
	}
}
