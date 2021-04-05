// htab_erase.c
// Řešení IJC-DU2, druhy ukol
// Autor: Vojtěch Eichler (xiechl01)
// Fakulta informačních technologií VUT Brno
// Datum: 5. 4. 2021

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "htab.h"
#include "htab_def.h"

bool htab_erase(htab_t *t, htab_key_t key) {
	htab_item_t *item;
	htab_item_t *tmp;
	// counting index by calling hash function
	size_t index = htab_hash_function(key);
	index = index % t->arr_size;
	
	// if first record is the one I am looking for, erase it
	item = t->items[index];
	if (item) {
		if (!(strcmp(key, item->pair.key))) {
			tmp = item->next;
			free((char *)item->pair.key);
			free(item);
			t->items[index] = tmp;
			return true;
		}
	} else
		return false;
	
	// cycling through the rest of records, erase if found
	while (item->next) {
		if (!(strcmp(key, item->next->pair.key))) {
			tmp = item->next;
			item->next = item->next->next;
			free((char *)tmp->pair.key);
			free(tmp);
			return true;
		}
		item = item->next;
	}
	// if record wasn't found
	return false;
}
