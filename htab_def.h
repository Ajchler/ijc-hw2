// htab_def.h
// Řešení IJC-DU2, druhy ukol
// Autor: Vojtěch Eichler (xiechl01)
// Fakulta informačních technologií VUT Brno
// Datum: 3. 4. 2021

#include "htab.h"

#ifndef HTAB_DEF
#define HTAB_DEF

struct htab {
	size_t size;
	size_t arr_size;
	// flexible array member
	struct htab_item *items[];
};

struct htab_item {
	struct htab_pair pair;
	struct htab_item *next;
};

#endif
