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

void open_test(char* arg) {
	int fd;
	printf("open_test: open() testing, trying to open %s:\n", arg);
	if ((fd = open(arg,  O_RDONLY, 0)) < 0) {
		perror("open_test: open() error: ");
		printf("open_test: can't open file %s \n\n", arg);
	} else	{
		printf("open_test: file %s is opened with descriptor = %d\n\n", arg, fd);
		close(fd);
		}

}

void creat_test(char* arg) {
	int fd;
	printf("creat_test: creat() testing, trying to creat %s:\n", arg);
	if ((fd = creat(arg,  0)) < 0) {
		perror("crear_test: creat() error: ");
		printf("creat_test: can't creat file %s \n\n", arg);
	} else
		printf("creat_test: file %s is created with descriptor = %d\n\n", arg, fd);
}

void fopen_test(char* arg) {
	FILE* fp;
	printf("fopen_test: fopen() testing, trying to open %s:\n", arg);
	if ((fp = fopen(arg, "r")) == NULL) {
		perror("fopen_test: fopen() error: ");
		printf("fopen_test: can't open file %s \n\n", arg);
	} else	{
		printf("fopen_test: file %s is opened\n\n", arg);
		fclose(fp);
		}
}


void stat_test(char* arg) {
	struct stat stbuf;
	printf("stat_test: stat() testing, trying to take stat info from %s:\n", arg);
	if ((stat(arg, &stbuf)) == -1) {
		perror("stat_test: stat() error: ");
		printf("stat_test: can't take stat info from file %s \n\n", arg);
	} else
		printf("stat_test: file %s is stated, it's inode:%ld \n\n", arg, stbuf.st_ino);
}


void unlink_test(char* arg) {
	int ret;
	printf("unlink_test: unlink() testing, trying to unlink file %s:\n", arg);
	if ((ret = unlink(arg)) < 0) {
		perror("unlink_test: unlink() error: ");
		printf("unlink_test: can't unlink file %s \n\n", arg);
	} else
		printf("unlink_test: file %s is unlinked \n\n", arg );
}

void remove_test(char* arg) {
	int ret;
	printf("remove_test: remove() testing, trying to remove file %s:\n", arg);
	if ((ret = remove(arg)) < 0) {
		perror("remove_test: remove() error: ");
		printf("remove_test: can't remove file %s \n\n", arg);
	} else
		printf("remove_test: file %s is removed \n\n", arg );
}

void read_open_dir_test(char* arg ) {
	DIR *dir;		/*analogue FILE*/
		
	if ((dir=opendir("./"))==0)
	    {
	        perror("Diropen error:\n");
	        exit(1);
	    };
	    
	/* Prosmotr failov vnutri direktorii, esli sozdan file - vyvod dannyh o nem na ekran*/
	
	/* Searching for created file by its name*/
	int exsts = 0;
	struct dirent *entry;
	
	    while( (entry = readdir(dir)) != NULL ) {
		if (!strcmp(entry->d_name, arg))
		{
		    printf("read_open_dir_test: File is found \n filename = %s, filename length = %ld\n\n",
			entry->d_name,strlen(entry->d_name));
		    exsts++;
		};
	};
	if (!exsts) printf("read_open_dir_test: File isn't found\n\n");
}


int main (int argc, char* argv[]) {
	char *filename;
	if (argv[1] != 0) 
		filename = argv[1]; 
	else
		filename = "ещеболеедлинноеоченьдлинноеимяоченьдлинноеимяоченьдлинноеимяоченьдлинноеимяоченьдлинноеимя\
оченьдлинноеимяоченьдлинноеимяоченьдлинноеимяоченьдлинноеимя";
		
	creat_test(filename);
	open_test(filename);
	stat_test(filename);
	read_open_dir_test(filename);
	unlink_test(filename);
	creat_test(filename);
	fopen_test(filename);
	remove_test(filename);
	
	return 0;
}
	