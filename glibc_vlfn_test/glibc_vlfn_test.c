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

int open_test(char* arg) {
	int fd;
	errno = 0;
	if ((fd = open(arg,  O_RDONLY, 0)) > 0) {
	         close(fd);
		 return true;
		 } else return false;
}


int creat_test(char* arg) {
#line 26
	errno = 0;
	if ((creat(arg,  0)) < 0) return false;
	else return true;
}

int fopen_test(char* arg) {
        FILE* fp;
        errno = 0;
        if ((fp = fopen(arg, "r")) != NULL) {
		fclose(fp);
		return true;
	} else return false;
}

int stat_test(char* arg) {
	struct stat stbuf;
	errno = 0;
	if ((stat(arg, &stbuf)) == -1)
		return false; 
	else return true;
}


int lstat_test(char* arg) {
	        struct stat stbuf;
		errno = 0;
		if ((lstat(arg, &stbuf)) == -1) 
			return false; 
		else
			return true;
}

int unlink_test(char* arg) {
	errno = 0;
	if ((unlink(arg)) < 0)
		return false;
	else
		return true;
}

int remove_test(char* arg) {
	errno = 0;
        if ((remove(arg)) < 0)
		return false;
	else
		return true;
}

int access_test(char* arg) {
	errno = 0;
	if ((access(arg, F_OK)) < 0)
                return false;
	else
		return true;
}

int chmod_test(char* arg){
	errno = 0;
	if ((chmod(arg, S_IRWXU)) < 0)
		return false;
	else
		return true;
}

int truncate_test(char* arg) {
        errno = 0;
	if ((truncate(arg, 100000)) < 0)
		return false;
	else
		return true;
}

int link_test(char* arg1, char* arg2) {
        errno = 0;
        if ((link(arg1, arg2)) < 0)
		return false;
	else
		return true;
}


int rename_test(char* arg1, char* arg2) {
	errno = 0;
        if ((rename(arg1, arg2)) < 0) 
		return false;
	else
		return true;
}

int symlink_test(char* arg1, char* arg2) {
        errno = 0;
	if ((symlink(arg1, arg2)) < 0)
		return false;
	else
		return true;
}

int mkdir_test(char* arg) {
	errno = 0;
	if ((mkdir(arg, S_IRUSR)) < 0) 
		return false;
	else
		return true;
}

int rmdir_test(char* arg) {
	errno = 0;
	if ((rmdir(arg)) < 0)
		return false;
	else
		return true;
}

int read_open_dir_test(char* arg) {
        DIR *dir;               /*analogue FILE*/
        errno = 0;
        if ((dir=opendir("./"))==0)
            return false;

        /* Prosmotr failov vnutri direktorii, esli sozdan file - vyvod dannyh o nem na ekran*/
 
	/* Searching for created file by its name*/
	int exsts = 0;
	struct dirent *entry;

	while( (entry = readdir(dir)) != NULL ) {
	       if (!strcmp(entry->d_name, arg)) {
                   exsts++;
               };
        };
        if (!exsts)
		return false;
	else
       		return true;
}

int main (int argc, char* argv[]) {
	char *filename;
	int failed = 0;
	int passed = 0;
	if (argv[1] != 0)
		filename = argv[1];
	else
	        filename = "оченьдлинноеимяоченьдлинноеимяоченьдлинноеимяоченьдлинноеимякомунужнытакиеименаочень\
длинноеимяоченьдлинноеимяоченьдлинноеимяоченьдлинноеимяидлиннаяконцовкас тремя пробелами .И заглавной буквой.\
Сделаем имя очень длинным. Вряд ли кому-то в голову придет называть файл таким длинным именем. Даже чуть длиннее,\
проверим символы: АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ и нижние буквы абвгдеёжзийклмнопрстуфхцчшщъыьэюя. Возможно, \
я ошибся с порядком, поэтому проверю знаки: !№;%:?*()_-+=. Я точно не знаю, сколько они занимают байт, думаю, что\
немного. И...конец!!!!";

	int nameLength = strlen(filename);
#define failing() (({++failed; perror("Error"); printf("line:%d; file: %s\n", __LINE__, __FILE__); }))
#define passing() (++passed)
# if (nameLength <= 1023)
	#define ok(x) ((x) ? (passing()) : (failing()))
# else
	#define ok(x) ((x) ? (failing() : (passing())))
# endif
	
	printf("Testing glibc functions with %d-byte filename\n", strlen(filename));
	ok(creat_test(filename));
	printf("FAILED: %d, PASSED: %d\n", failed, passed);

}
