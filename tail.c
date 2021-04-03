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

int last_lines(FILE *input, long to_print) {
	long i = 0;
	long break_point = 0;
	char **buffer = alloc_buffer(to_print);
	char line[MAX_SIZE] = "";
	if (!buffer)
		return -1;
	// reading from file
	while (fgets(line, MAX_SIZE, input) != NULL) {
		strncpy(buffer[i], line, MAX_SIZE);
		// if a line was longer than maximum size, insert a newline
		while (!strchr(line, '\n')) {
			buffer[i][MAX_SIZE - 2] = '\n';
			fgets(line, MAX_SIZE, input);
		}
		i = (i + 1) % to_print;
	}
	// finding index of last line
	break_point = i == 0 ? to_print - 1 : i - 1;
	for (int j = i; j != break_point; j = (j + 1) % to_print) {
		printf("%s", buffer[j]);
	}
	printf("%s", buffer[break_point]);
	free_buffer(buffer, to_print);
	return 0;
}

void write_lines(FILE *input, long line_number) {
	long read = 0;
	char line[MAX_SIZE] = "";
	while (fgets(line, MAX_SIZE, input) != NULL) {
		// if a line was longer than 511 characters insert newline and read
		// the rest of a line
		while (!strchr(line, '\n')) {
			line[MAX_SIZE - 2] = '\n';
			fgets(line, MAX_SIZE, input);
		}
		if (read >= line_number - 1)
			printf("%s", line);
		read++;
	}
}

int main(int argc, char *argv[]) {
	long count = 10;
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
				count = strtol(argv[2], NULL, 10);
				if (count == 0) {
					fprintf(stderr, "ERROR: -n flag was given invalid argument");
					return 1;
				}
			}
			else {
				fprintf(stderr, "ERROR: invalid arguments");
				return 1;
			}
			// 3 arguments given, last one is name of a file
			if (argc == 4)
				filename = argv[argc - 1];
			break;

		default:
			fprintf(stderr, "ERROR: invalid arguments");
			return 1;
	}

	if (filename)
		input = fopen(filename, "r");
	if (!input) {
		fprintf(stderr, "ERROR: failed opening the file\n");
		return 1;
	}
	
	// if -n flag was given and the number given contains plus, write lines from n to the end
	if (argc > 2)
		if (strchr(argv[2], '+')) {
			write_lines(input, count);
			if (filename) {
				fclose(input);
				return 0;
			}
		}

	// if number given by user contains '+' then print all lines from nth line
	if (last_lines(input, count) < 0) {
		if (filename)
			fclose(input);
		return 1;
	}

	if (filename)
		fclose(input);
	return 0;
}
