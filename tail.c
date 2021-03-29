#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 512

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

	fclose(input);

	/*
	FILE *fp = fopen(argv[1], "rw");
	fp = stdin;
	while (fgets(string, 99, fp) != NULL)
			printf("%s", string);
	fclose(fp);
	*/
	return 0;
}
