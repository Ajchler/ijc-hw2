// htab_for_each.c
// Řešení IJC-DU2, druhy ukol
// Autor: Vojtěch Eichler (xiechl01)
// Fakulta informačních technologií VUT Brno
// Datum: 6. 4. 2021

#include "htab.h"
#include "htab_def.h"

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
	htab_item_t *item;
	for (size_t i = 0; i < t->arr_size; i++) {
		item = t->items[i];
		while (item) {
			f(&(item->pair));
			item = item->next;
		}
	}
}
