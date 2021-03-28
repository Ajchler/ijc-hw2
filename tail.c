#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 512

int main(int argc, char *argv[]) {
	char string[100];
	FILE *fp = fopen(argv[1], "rw");
	fp = stdin;
	while (fgets(string, 99, fp) != NULL)
			printf("%s", string);
	fclose(fp);
	return 0;
}
