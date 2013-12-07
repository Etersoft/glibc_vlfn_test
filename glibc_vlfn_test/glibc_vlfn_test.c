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
#include <stdbool.h>

extern int lstat(const char *file_name, struct stat *buf);
extern int truncate(const char *path, off_t length);
extern int symlink(const char *topath, const char *frompath);

int failed = 0;
int passed = 0;

void open_test(char* arg, bool legal) {
	int fd;
	errno = 0; int koef = -1; if (legal == true) koef = 1; int retval = 1;
	if ((fd = open(arg,  O_RDONLY, 0)) < 0) {
		retval = -1*koef;
	} else	{
		retval = 1*koef;
		close(fd);
		}
	if (retval < 0) { perror("open_test()"); failed = failed+1; } else { printf("."); passed = passed+1; }

}

void creat_test(char* arg, bool legal) {
	errno = 0; int koef = -1; if (legal == true) koef = 1; int retval = 1;
	if ((creat(arg,  0)) < 0) {
		retval = -1*koef;
	} else {
		retval = 1*koef;
		}
       if (retval < 0) { perror("creat_test()"); failed = failed+1; } else { printf("."); passed = passed+1; }
}

void fopen_test(char* arg, bool legal) {
	FILE* fp;
	errno = 0; int koef = -1; if (legal == true) koef = 1; int retval = 1;
	if ((fp = fopen(arg, "r")) == NULL) {
		retval = -1*koef;
	} else	{
		retval = 1*koef;
		fclose(fp);
		}
       if (retval < 0) { perror("fopen_test()"); failed = failed+1; } else { printf("."); passed = passed+1; }
}


void stat_test(char* arg, bool legal) {
	struct stat stbuf;
	errno = 0; int koef = -1; if (legal == true) koef = 1; int retval = 1;
	if ((stat(arg, &stbuf)) == -1) {
		retval = -1*koef;
	} else	{
		retval = 1*koef;
		}
       if (retval < 0) { perror("stat_test()"); failed = failed+1; } else { printf("."); passed = passed+1; }
}

void lstat_test(char* arg, bool legal) {
	struct stat stbuf;
	errno = 0; int koef = -1; if (legal == true) koef = 1; int retval = 1;
	if ((lstat(arg, &stbuf)) == -1) {
		retval = -1*koef;
	} else	{
		retval = 1*koef;
		}
       if (retval < 0) { perror("lstat_test()"); failed = failed+1; } else { printf("."); passed = passed+1; }
}


void unlink_test(char* arg, bool legal) {
	errno = 0; int koef = -1; if (legal == true) koef = 1; int retval = 1;
	if ((unlink(arg)) < 0) {
		retval = -1*koef;
	} else	{
		retval = 1*koef;
		}
       if (retval < 0) { perror("unlink_test()"); failed = failed+1; } else { printf("."); passed = passed+1; }
}

void remove_test(char* arg, bool legal) {
	errno = 0; int koef = -1; if (legal == true) koef = 1; int retval = 1;
	if ((remove(arg)) < 0) {
		retval = -1*koef;
	} else	{
		retval = 1*koef;
		}
       if (retval < 0) { perror("remove_test()"); failed = failed+1; } else { printf("."); passed = passed+1; }
}

void access_test(char* arg, bool legal) {
	errno = 0; int koef = -1; if (legal == true) koef = 1; int retval = 1;
	if ((access(arg, F_OK)) < 0) {
		retval = -1*koef;
	} else	{
		retval = 1*koef;
		}
       if (retval < 0) { perror("access_test()"); failed = failed+1; } else { printf("."); passed = passed+1; }
}

void chmod_test(char* arg, bool legal) {
	errno = 0; int koef = -1; if (legal == true) koef = 1; int retval = 1;
	if ((chmod(arg, S_IRWXU)) < 0) {
		retval = -1*koef;
	} else	{
		retval = 1*koef;
		}
       if (retval < 0) { perror("chmod_test()"); failed = failed+1; } else { printf("."); passed = passed+1; }
}

void truncate_test(char* arg, bool legal) {
	errno = 0; int koef = -1; if (legal == true) koef = 1; int retval = 1;
	if ((truncate(arg, 100000)) < 0) {
		retval = -1*koef;
	} else	{
		retval = 1*koef;
		}
       if (retval < 0) { perror("truncate_test()"); failed = failed+1; } else { printf("."); passed = passed+1; }
}




void read_open_dir_test(char* arg, bool legal) {
	DIR *dir;		/*analogue FILE*/
	errno = 0; int koef = -1; if (legal == true) koef = 1; int retval = 1;
	if ((dir=opendir("./"))==0)
	    {
	        retval = -1*koef;
	    };
	    
	/* Prosmotr failov vnutri direktorii, esli sozdan file - vyvod dannyh o nem na ekran*/
	
	/* Searching for created file by its name*/
	int exsts = 0;
	struct dirent *entry;
	
	    while( (entry = readdir(dir)) != NULL ) {
		if (!strcmp(entry->d_name, arg))
		{
		    exsts++;
		};
	};
	if (!exsts)	{ 
		retval = -1*koef;
		} else retval = 1*koef;
	 if (retval < 0) { printf("read_open_dir error"); failed = failed+1; } else { printf("."); passed = passed+1; }
}

void link_test(char* arg1, char* arg2, bool legal) {
	errno = 0; int koef = -1; if (legal == true) koef = 1; int retval = 1;
	if ((link(arg1, arg2)) < 0) {
		retval = -1*koef;
	} else	{
		retval = 1*koef;
		}
	if (retval < 0) { perror("link_test()"); failed = failed+1; } else { printf("."); passed = passed+1; }
}


void rename_test(char* arg1, char* arg2, bool legal) {
	errno = 0; int koef = -1; if (legal == true) koef = 1; int retval = 1;
	if ((rename(arg1, arg2)) < 0) {
		retval = -1*koef;
	} else	{
		retval = 1*koef;
		}
	if (retval < 0) { perror("rename_test()"); failed = failed+1; } else { printf("."); passed = passed+1; }
}


void symlink_test(char* arg1, char* arg2, bool legal) {
	errno = 0; int koef = -1; if (legal == true) koef = 1; int retval = 1;
	if ((symlink(arg1, arg2)) < 0) {
		retval = -1*koef;
	} else	{
		retval = 1*koef;
		}
	if (retval < 0) { perror("symlink_test()"); failed = failed+1; } else { printf("."); passed = passed+1; }
}


void mkdir_test(char* arg, bool legal) {
	errno = 0; int koef = -1; if (legal == true) koef = 1; int retval = 1;
	if ((mkdir(arg, S_IRUSR)) < 0) {
		retval = -1*koef;
	} else	{
		retval = 1*koef;
		}
	if (retval < 0) { perror("mkdir_test()"); failed = failed+1; } else { printf("."); passed = passed+1; }
}

void rmdir_test(char* arg, bool legal) {
	errno = 0; int koef = -1; if (legal == true) koef = 1; int retval = 1;
	if ((rmdir(arg)) < 0) {
		retval = -1*koef;
	} else	{
		retval = 1*koef;
		}
	if (retval < 0) { perror("rmdir_test()"); failed = failed+1; } else { printf("."); passed = passed+1; }
}






int main (int argc, char* argv[]) {
	char *filename;
	if (argv[1] != 0) 
		filename = argv[1]; 
	else
		filename = "оченьдлинноеимяоченьдлинноеимяоченьдлинноеимяоченьдлинноеимякомунужнытакиеименаочень\
длинноеимяоченьдлинноеимяоченьдлинноеимяоченьдлинноеимяидлиннаяконцовкас тремя пробелами .И заглавной буквой.\
Сделаем имя очень длинным. Вряд ли кому-то в голову придет называть файл таким длинным именем. Даже чуть длиннее,\
проверим символы: АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ и нижние буквы абвгдеёжзийклмнопрстуфхцчшщъыьэюя. Возможно, \
я ошибся с порядком, поэтому проверю знаки: !№;%:?*()_-+=. Я точно не знаю, сколько они занимают байт, думаю, что\
немного. И...конец!!!!";

	bool legal = true;
	if (strlen(filename) > 1023) legal = false;
	printf("Testing glibc functions with %d-byte filename", strlen(filename));
	creat_test(filename, legal);
	access_test(filename, legal);
	chmod_test(filename, legal);
	open_test(filename, legal);
	stat_test(filename, legal);
	lstat_test(filename, legal);
	read_open_dir_test(filename, legal);
	unlink_test(filename, legal);
	creat_test(filename, legal);
	symlink_test(filename, "simply_symlink", legal);
	unlink_test("simply_symlink", legal);
	rename_test(filename, "newname", legal);
	rename_test("newname", filename, legal);
	chmod_test(filename, legal);
	fopen_test(filename, legal);
	truncate_test(filename, legal);
	link_test(filename, "simply_link", legal);
	unlink_test("simply_link", legal);
	remove_test(filename, legal);
	mkdir_test(filename, legal);
	read_open_dir_test(filename, legal);
	rmdir_test(filename, legal);
	
	if (failed == 0) printf("OK\n");
	printf("\nPASSED: %d, FAILED: %d\n", passed, failed);
	
	return 0;
	
}
