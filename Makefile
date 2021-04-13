# Makefile
# Řešení IJC-DU2, druhy ukol
# Autor: Vojtěch Eichler (xeichl01)
# Fakulta informačních technologií VUT Brno
# Datum 13. 4. 2021

CFLAGS= -g -std=c99 -Wall -Wextra -pedantic
CC=gcc
LIB_SOURCE_FILES= htab_find.c htab_init.c htab_bucket_count.c\
		   		  htab_for_each.c htab_lookup_add.c htab_clear.c\
		   		  htab_free.c htab_move.c htab_def.h htab.h \
				  htab_size.c htab_erase.c htab_hash_function.c

all: tail wordcount wordcount-dynamic

tail:

wordcount: io.c wordcount.c libhtab.a
	$(CC) $(CFLAGS) wordcount.c libhtab.a -o wordcount 

wordcount-dynamic: io.c wordcount.c libhtab.so
	$(CC) $(CFLAGS) wordcount.c -Wl,-rpath,'.' -L. -lhtab -o wordcount-dynamic

libhtab.a: libhtab
	ar rcs $@ htab_find.o htab_init.o htab_bucket_count.o htab_for_each.o htab_lookup_add.o htab_clear.o htab_free.o htab_move.o htab_size.o htab_erase.o htab_hash_function.o

libhtab.so: libhtab
	$(CC) $(CFLAGS) -fPIC -shared -o $@ htab_find.o htab_init.o htab_bucket_count.o htab_for_each.o htab_lookup_add.o htab_clear.o htab_free.o htab_move.o htab_size.o htab_erase.o htab_hash_function.o

# making .o files needed for building libraries
libhtab: $(LIB_SOURCE_FILES)
	$(CC) $(CFLAGS) -fPIC -c htab_find.c -o htab_find.o
	$(CC) $(CFLAGS) -fPIC -c htab_init.c -o htab_init.o
	$(CC) $(CFLAGS) -fPIC -c htab_bucket_count.c -o htab_bucket_count.o
	$(CC) $(CFLAGS) -fPIC -c htab_for_each.c -o htab_for_each.o
	$(CC) $(CFLAGS) -fPIC -c htab_lookup_add.c -o htab_lookup_add.o
	$(CC) $(CFLAGS) -fPIC -c htab_clear.c -o htab_clear.o
	$(CC) $(CFLAGS) -fPIC -c htab_free.c -o htab_free.o
	$(CC) $(CFLAGS) -fPIC -c htab_move.c -o htab_move.o
	$(CC) $(CFLAGS) -fPIC -c htab_size.c -o htab_size.o
	$(CC) $(CFLAGS) -fPIC -c htab_erase.c -o htab_erase.o
	$(CC) $(CFLAGS) -fPIC -c htab_hash_function.c -o htab_hash_function.o

clean:
	rm *.o
