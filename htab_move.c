// htab_move.c
// Řešení IJC-DU2, druhy ukol
// Autor: Vojtěch Eichler (xiechl01)
// Fakulta informačních technologií VUT Brno
// Datum: 6. 4. 2021

#include "htab.h"
#include "htab_def.h"

htab_t *htab_move(size_t n, htab_t *from) {
	htab_t *dest = htab_init(n);
	if (!dest)
		return NULL;

	for (size_t i = 0; i < from->arr_size; i++) {
		while (from->items[i]) {
			htab_lookup_add(dest, from->items[i]->pair.key);
			htab_erase(from, from->items[i]->pair.key);
		}
	}

	return dest;
}
