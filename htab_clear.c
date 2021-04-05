// htab_clear.c
// Řešení IJC-DU2, druhy ukol
// Autor: Vojtěch Eichler (xiechl01)
// Fakulta informačních technologií VUT Brno
// Datum: 4. 4. 2021
// Popis: Funkce na vymazání všech záznamů z hash table

#include <stdlib.h>
#include "htab.h"
#include "htab_def.h"

void htab_clear(htab_t *t) {
	htab_item_t *item;
	htab_item_t *tmp;
	for (size_t i = 0; i < t->arr_size; i++) {
		item = t->items[i];
		while (item != NULL) {
			tmp = item->next;
			free((char *)item->pair.key);
			free(item);
			item = tmp;
		}
		t->items[i] = NULL;
	}
	t->size = 0;
}
