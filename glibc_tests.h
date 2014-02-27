#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define true 1
#define false 0

int open_test(char* arg);


int creat_test(char* arg);

int fopen_test(char* arg);

int stat_test(char* arg);


int lstat_test(char* arg);

int unlink_test(char* arg);

int remove_test(char* arg);

int access_test(char* arg);

int chmod_test(char* arg);

int truncate_test(char* arg);

int link_test(char* arg1, char* arg2);


int rename_test(char* arg1, char* arg2);

int symlink_test(char* arg1, char* arg2);

int mkdir_test(char* arg);

int rmdir_test(char* arg);

int read_open_dir_test(char* arg);