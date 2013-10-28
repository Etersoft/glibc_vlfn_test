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
//	printf("open_test: open() testing, trying to open %s:\n", arg);
	if ((fd = open(arg,  O_RDONLY, 0)) < 0) {
		perror("open_test: open() error");
	} else	{
		printf("open_test: working\n");
		close(fd);
		}

}

void creat_test(char* arg) {
	int fd;
	if ((fd = creat(arg,  0)) < 0) {
		perror("crear_test: creat() error");
	} else
		printf("creat_test: working\n");
}

void fopen_test(char* arg) {
	FILE* fp;
	if ((fp = fopen(arg, "r")) == NULL) {
		perror("fopen_test: fopen() error");
	} else	{
		printf("fopen_test: working\n");
		fclose(fp);
		}
}


void stat_test(char* arg) {
	struct stat stbuf;
	if ((stat(arg, &stbuf)) == -1) {
		perror("stat_test: stat() error");
	} else
		printf("stat_test: working \n");
}


void unlink_test(char* arg) {
	int ret;
	if ((ret = unlink(arg)) < 0) {
		perror("unlink_test: unlink() error");
	} else
		printf("unlink_test: working \n");
}

void remove_test(char* arg) {
	int ret;
	if ((ret = remove(arg)) < 0) {
		perror("remove_test: remove() error");
	} else
		printf("remove_test: working \n");
}

void access_test(char* arg) {
	int ret;
	if ((ret = access(arg, F_OK)) < 0) {
		perror("access_test: access() error");
	} else
		printf("access_test: working\n");
}

void chmod_test(char* arg) {
	int ret;
	if ((ret = chmod(arg, S_IRWXU)) < 0) {
		perror("chmod_test: chmod() error");
	} else
		printf("chmod_test: working\n");
}

void truncate_test(char* arg) {
	int ret;
	if ((ret = truncate(arg, 100000)) < 0) {
		perror("truncate_test: truncate() error");
	} else
		printf("truncate_test: working\n");
}




void read_open_dir_test(char* arg ) {
	DIR *dir;		/*analogue FILE*/
		
	if ((dir=opendir("./"))==0)
	    {
	        perror("Diropen error\n");
	        exit(1);
	    };
	    
	/* Prosmotr failov vnutri direktorii, esli sozdan file - vyvod dannyh o nem na ekran*/
	
	/* Searching for created file by its name*/
	int exsts = 0;
	struct dirent *entry;
	
	    while( (entry = readdir(dir)) != NULL ) {
		if (!strcmp(entry->d_name, arg))
		{
		    printf("read_open_dir_test: working\n");
		    exsts++;
		};
	};
	if (!exsts) printf("read_open_dir_test: File isn't found\n");
}

void link_test(char* arg1, char* arg2) {
	int ret;
	if ((ret = link(arg1, arg2)) < 0) {
		perror("link_test: link() error");
	} else
		printf("link_test: working\n");
}


void rename_test(char* arg1, char* arg2) {
	int ret;
	if ((ret = rename(arg1, arg2)) < 0) {
		perror("rename_test: rename() error");
	} else
		printf("rename_test: working\n");
}


void symlink_test(char* arg1, char* arg2) {
	int ret;
	if ((ret = symlink(arg1, arg2)) < 0) {
		perror("symlink_test: symlink() error");
	} else
		printf("symlink_test: working\n");
}


void mkdir_test(char* arg) {
	int ret;
	if ((ret = mkdir(arg, S_IRUSR)) < 0) {
		perror("mkdir_test: mkdir() error");
	} else
		printf("mkdir_test: working\n");
}

void rmdir_test(char* arg) {
	int ret;
	if ((ret = rmdir(arg)) < 0) {
		perror("rmdir_test: rmdir() error");
	} else
		printf("rmdir_test: working\n");
}






int main (int argc, char* argv[]) {
	char *filename;
	if (argv[1] != 0) 
		filename = argv[1]; 
	else
		filename = "ещеболеедлинноеоченьдлинноеимяоченьдлинноеимяоченьдлинноеимяоченьдлинноеимяоченьдлинноеимя\
оченьдлинноеимяоченьдлинноеимяоченьдлинноеимяоченьдлинноеимя";
		
	creat_test(filename);
	access_test(filename);
	chmod_test(filename);
	open_test(filename);
	stat_test(filename);
	read_open_dir_test(filename);

	unlink_test(filename);
	creat_test(filename);
	symlink_test(filename, "simply_symlink");
	unlink("simply_symlink");
	rename(filename, "newname");
	rename("newname", filename);
	chmod_test(filename);
	fopen_test(filename);
	truncate_test(filename);
	link_test(filename, "simply_link");
	unlink("simply_link");
	remove_test(filename);
	mkdir_test(filename);
	rmdir_test(filename);
	
	return 0;
}
	