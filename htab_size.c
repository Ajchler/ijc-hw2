// htab_size.c
// Řešení IJC-DU2, druhy ukol
// Autor: Vojtěch Eichler (xeichl01)
// Fakulta informačních technologií VUT Brno
// Datum: 4. 4. 2021
// Popis: Funkce která vrací velikost hash table

#include "htab.h"
#include "htab_def.h"

// takes hash table as parameter, const because we're not editing it
size_t htab_size(const htab_t *t) {
	return t->size;
}
