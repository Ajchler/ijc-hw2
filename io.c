// io.c
// Řešení IJC-DU2, druhy ukol
// Autor: Vojtěch Eichler (xiechl01)
// Fakulta informačních technologií VUT Brno
// Datum: 9. 4. 2021

#include <ctype.h>
#include <stdio.h>
 
int read_word(char *s, int max, FILE *f) {
	int count = 0;
	int character = 0;

	while ((character = fgetc(f)) != EOF) {
		// if we are at end of a word, return length
		if (isspace(character)) {
			return count;
		}
		// end of word wasnt reached yet
		else {
			// only save characters when count < max limit
			// -1 so that last character is always end of string
			if (count < (max - 1)) {
				s[count] = character;
				s[count + 1] = '\0';
			}
		}
		count++;
	}
	// end of file was reached
	return EOF;
}
