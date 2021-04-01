#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 511 characters + end of string + newline
#define MAX_SIZE 513

char **alloc_buffer(long to_print) {
	char **buffer = malloc(to_print * sizeof(char *));
	if (!buffer) {
		fprintf(stderr, "ERROR: allocation failed");
		return NULL;
	}
	for (int i = 0; i < to_print; i++) {
		// if allocating a row failed print error and free what was already allocated
		if (!(buffer[i] = malloc(MAX_SIZE))) {
			fprintf(stderr, "ERROR: allocation failed");
			for (int j = i - 1; j >= 0; j--) {
				free(buffer[j]);
				free(buffer);
			}	
			return NULL;
		}
	}
	return buffer;
}

void free_buffer(char **buffer, long to_print) {
	for (int i = 0; i < to_print; i++)
		free(buffer[i]);
	free(buffer);

}

int read_lines(FILE *input, long to_print) {
	long i = 0;
	char **buffer = alloc_buffer(to_print);
	char line[MAX_SIZE] = "";
	if (!buffer)
		return -1;
	while (fgets(line, MAX_SIZE, input) != NULL) {
		strncpy(buffer[i], line, MAX_SIZE);
		// if a line was longer than maximum size, insert a newline
		while (!strchr(line, '\n')) {
			buffer[i][MAX_SIZE - 2] = '\n';
			fgets(line, MAX_SIZE, input);
		}
		i = (i + 1) % to_print;
	}

	for (int j = i; j != i - 1; j = (j + 1) % to_print) {
		printf("%s", buffer[j]);
	}
	printf("%s", buffer[i - 1]);
	free_buffer(buffer, to_print);
	return 0;
}

int main(int argc, char *argv[]) {
	long to_print = 10;
	FILE *input = stdin;
	char *filename = NULL;
	
	switch (argc) {
		// no arguments given, default number of rows to print (10) and reads from stdin
		case 1:
			break;
		// only one argument set, expecting a file
		case 2:
			filename = argv[1];
			break;
		// two or three arguments given, if two were given, expecting -n flag,
		// if three were given, expecting -n flag and file
		case 3:
		case 4:
			// first argument should be -n flag
			if (!strcmp(argv[1], "-n")) {
				// converting argument after -n to a number
				to_print = strtol(argv[2], NULL, 10);
				if (to_print == 0) {
					fprintf(stderr, "ERROR: -n flag was given invalid argument");
					return 1;
				}
			}
			else
				fprintf(stderr, "ERROR: invalid arguments");
			// 3 arguments given, last one is name of a file
			if (argc == 4)
				filename = argv[argc - 1];
			break;

		default:
			fprintf(stderr, "ERROR: invalid arguments");
	}

	if (filename)
		input = fopen(filename, "r");
	if (!input) {
		fprintf(stderr, "ERROR: failed opening the file\n");
		return 1;
	}

	if (read_lines(input, to_print) < 0)
		return 1;

	if (filename)
		fclose(input);
	return 0;
}
