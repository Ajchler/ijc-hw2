// htab_def.h
// Řešení IJC-DU2, druhy ukol
// Autor: Vojtěch Eichler (xiechl01)
// Fakulta informačních technologií VUT Brno
// Datum: 3. 4. 2021

#include "htab.h"

#ifndef HTAB_DEF
#define HTAB_DEF

struct htab {
	// number of records inside hash table
	size_t size;
	// size of hashtable
	size_t arr_size;
	// flexible array member
	struct htab_item *items[];
};

typedef struct htab_item {
	struct htab_pair pair;
	struct htab_item *next;
} htab_item_t;

#endif
