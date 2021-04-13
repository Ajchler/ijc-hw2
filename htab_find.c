// htab_find.c
// Řešení IJC-DU2, druhy ukol
// Autor: Vojtěch Eichler (xiechl01)
// Fakulta informačních technologií VUT Brno
// Datum: 5. 4. 2021
// Popis: Funkce která vyhledá záznam a vrátí ukazatel na něj, pokud nenajde,
// 	vrací NULL

#include <string.h>
#include "htab.h"
#include "htab_def.h"

htab_pair_t *htab_find(htab_t *t, htab_key_t key) {
	htab_item_t *item;
	// finding index of key in hash table
	size_t index = htab_hash_function(key);
	index = index % t->arr_size;

	// cycling through all records at index in hash table
	item = t->items[index];
	while (item) {
		// if current item has the wanted key
		if (!(strcmp(key, item->pair.key)))
			return &(item->pair);
		item = item->next;
	}

	// hash table doesn't contain key
	return NULL;
}
