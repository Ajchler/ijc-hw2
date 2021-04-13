// htab_bucket_count.c
// Řešení IJC-DU2, druhy ukol
// Autor: Vojtěch Eichler (xiechl01)
// Fakulta informačních technologií VUT Brno
// Datum: 4. 4. 2021
// Popis: Funkce vracející počet aktuálně uložených záznamů v hash table

#include "htab.h"
#include "htab_def.h"

// takes hash table as parameter, can be const since it's not being edited
size_t htab_bucket_count(const htab_t *t) {
	return t->arr_size;
}
