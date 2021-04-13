// htab_free.c
// Řešení IJC-DU2, druhy ukol
// Autor: Vojtěch Eichler (xiechl01)
// Fakulta informačních technologií VUT Brno
// Datum: 5. 4. 2021
// Popis: Funkce na uvolnění paměti které zabírá hash table, volá funkci
// htab_clear na uvolnění záznamů

#include <stdlib.h>
#include "htab.h"
#include "htab_def.h"

void htab_free(htab_t *t) {
	// clearing records inside hash table
	htab_clear(t);
	// freeing allocated space
	free(t);
}
