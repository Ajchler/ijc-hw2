// htab_init.c
// Řešení IJC-DU2, druhy ukol
// Autor: Vojtěch Eichler (xiechl01)
// Fakulta informačních technologií VUT Brno
// Datum: 4. 4. 2021
// Popis: Funkce na alokaci a inizializaci hash table

#include <htab.h>
#include <htab_def.h>

htab_t *htab_init(size_t number) {
	htab_t *table;
	// if allocation fails, return NULL, allocating space for hash table + 
	// n * pointer to hash table item/record
	if (!(table = malloc(sizeof(htab_t) + number * sizeof(htab_item_t*))))
		return NULL;

	// hash table initialization
	table->size = 0;
	table->arr_size = number;
	for (size_t i = 0; i < number; i++)
		table->items[i] = NULL;

	return table;
}
