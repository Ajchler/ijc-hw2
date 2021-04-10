// htab_lookup_add.c
// Řešení IJC-DU2, druhy ukol
// Autor: Vojtěch Eichler (xiechl01)
// Fakulta informačních technologií VUT Brno
// Datum: 5. 4. 2021
// Popis: Funkce, která vyhledá záznam podle key, pokud najde, vrátí ukazatel na
// 	pair, pokud nenajde, vyvtvoří nový záznam a vrátí ukazatel na něj. Při
// 	selhání alokace, vrací NULL.

#include <stdlib.h>
#include <string.h>
#include "htab.h"
#include "htab_def.h"

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
	htab_item_t *item;
	size_t index = htab_hash_function(key);
	index = index % t->arr_size;

	item = t->items[index];
	// there are no records at index
	if (!item) {
		// alloc new item
		t->items[index] = malloc(sizeof(htab_item_t));
		if (!(t->items[index]))
			return NULL;
		t->items[index]->next = NULL;
		// alloc key inside pair, allocating length of key + \0
		t->items[index]->pair.key = malloc(strlen(key) + 1);
		// if allocation failed, free what was alloced and return
		if (!(t->items[index]->pair.key)) {
			free(t->items[index]);
			t->items[index] = NULL;
			return NULL;
		}
		// copy key given by user to hash table
		strcpy((char *)t->items[index]->pair.key, key);
		t->items[index]->pair.value = 0;
		t->size++;
		return &(t->items[index]->pair);
	}
	
	// there is atleast one record inside hash table at this index
	
	// if the first one is what we are looking for
	if (!strcmp(item->pair.key, key))
		return &(item->pair);
	
	// cycling through all values and looking for key
	while (item->next) {
		if (!(strcmp(item->next->pair.key, key))) {
			return &(item->next->pair);
		}
		item = item->next;
	}

	// key wasn't found, alloc new item
	item->next = malloc(sizeof(htab_item_t));
	if (!item->next)
		return NULL;
	item->next->next = NULL;
	item->next->pair.key = malloc(strlen(key) + 1);
	if (!(item->next->pair.key)) {
		free(item->next);
		item->next = NULL;
		return NULL;
	}
	strcpy((char *)item->next->pair.key, key);
	t->size++;	
	item->next->pair.value = 0;
	return &(item->next->pair);
}
