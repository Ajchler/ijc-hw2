// hash_function.c
// Řešení IJC-DU2, druhy ukol
// Autor: Vojtěch Eichler (xiechl01)
// Fakulta informačních technologií VUT Brno
// Datum: 4. 4. 2021
// Popis: Hashovací funkce, která se používá ve více modulech,
// 	proto má vlastní modul.

// stddef.h for size_t type
#include <stdint.h>
#include "htab.h"

#ifndef HASHTEST
size_t htab_hash_function(htab_key_t str) {
	uint32_t h=0;
	const unsigned char *p;
	for(p=(const unsigned char*)str; *p!='\0'; p++)
	h = 65599*h + *p;
	return h;
}
#else
size_t htab_hash_function(htab_key_t str) {
    uint32_t h = 5381;
    const unsigned char *p;
	for(p=(const unsigned char*)str; *p!='\0'; p++)
    	h = ((h << 5) + h) + *p;
    return h;
}
#endif
