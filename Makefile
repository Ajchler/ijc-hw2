# Makefile
# Řešení IJC-DU2, druhy ukol
# Autor: Vojtěch Eichler (xeichl01)
# Fakulta informačních technologií VUT Brno
# Datum 13. 4. 2021

CFLAGS=-g -std=c99 -Wall -Wextra -pedantic
CC=gcc
LIB_OBJECT_FILES= htab_find.o htab_init.o htab_bucket_count.o\
		   		  htab_for_each.o htab_lookup_add.o htab_clear.o\
		   		  htab_free.o htab_move.o \
				  htab_size.o htab_erase.o htab_hash_function.o

all: tail wordcount wordcount-dynamic

tail:

# wordcount with static library
wordcount: io.c wordcount.c libhtab.a
	$(CC) $(CFLAGS) -static wordcount.c libhtab.a -o wordcount 

# wordcount with dynamic library
wordcount-dynamic: io.c wordcount.c libhtab.so
	$(CC) $(CFLAGS) wordcount.c -Wl,-rpath,'.' -L. -lhtab -o wordcount-dynamic

# static library
libhtab.a: $(LIB_OBJECT_FILES)
	ar rcs $@ htab_find.o htab_init.o htab_bucket_count.o htab_for_each.o htab_lookup_add.o htab_clear.o htab_free.o htab_move.o htab_size.o htab_erase.o htab_hash_function.o

# dynamic library
libhtab.so: $(LIB_OBJECT_FILES)
	$(CC) $(CFLAGS) -fPIC -shared -o $@ htab_find.o htab_init.o htab_bucket_count.o htab_for_each.o htab_lookup_add.o htab_clear.o htab_free.o htab_move.o htab_size.o htab_erase.o htab_hash_function.o

# compiling c files into object files
%.o: %.c htab.h htab_def.h
	$(CC) $(CFLAGS) -fPIC -c $<

clean:
	rm *.o
