CC=gcc

all:
	$(CC) -std=gnu99 -Wall -pedantic glibc_vlfn_test.c glibc_tests.h glibc_tests.c \
	filename_generator.h filename_generator.c  -o glibc_vlfn_test
clean:
	rm -rf *.o glibc_vlfn_test