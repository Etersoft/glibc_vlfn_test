#ifndef FILENAME_GENERATOR_H
	#define FILENAME_GENERATOR_H
#endif

#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include <getopt.h>
#include <stdio.h>


void generate_rus_filename(int n, char * rus_name);

void generate_eng_filename(int n, char * eng_name);