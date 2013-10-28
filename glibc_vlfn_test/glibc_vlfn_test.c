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

int open_test(char* arg) {
	int fd;
	if ((fd = open(arg,  O_RDONLY, 0)) < 0) {
		perror("open_test: open() error");
		return -1;
	} else	{
		printf("open_test: working\n");
		close(fd);
		return 0;
		}

}

int creat_test(char* arg) {
	int fd;
	if ((fd = creat(arg,  0)) < 0) {
		perror("crear_test: creat() error");
		return -1;
	} else {
		printf("creat_test: working\n");
		return 0;
		}
}

int fopen_test(char* arg) {
	FILE* fp;
	if ((fp = fopen(arg, "r")) == NULL) {
		perror("fopen_test: fopen() error");
		return -1;
	} else	{
		printf("fopen_test: working\n");
		return 0;
		fclose(fp);
		}
}


int stat_test(char* arg) {
	struct stat stbuf;
	if ((stat(arg, &stbuf)) == -1) {
		perror("stat_test: stat() error");
		return -1;
	} else	{
		printf("stat_test: working \n");
		return 0;
		}
}


int unlink_test(char* arg) {
	int ret;
	if ((ret = unlink(arg)) < 0) {
		perror("unlink_test: unlink() error");
		return -1;
	} else	{
		printf("unlink_test: working \n");
		return 0;
		}
}

int remove_test(char* arg) {
	int ret;
	if ((ret = remove(arg)) < 0) {
		perror("remove_test: remove() error");
		return -1;
	} else	{
		printf("remove_test: working \n");
		return 0;
		}
}

int access_test(char* arg) {
	int ret;
	if ((ret = access(arg, F_OK)) < 0) {
		perror("access_test: access() error");
		return -1;
	} else	{
		printf("access_test: working\n");
		return 0;
		}
}

int chmod_test(char* arg) {
	int ret;
	if ((ret = chmod(arg, S_IRWXU)) < 0) {
		perror("chmod_test: chmod() error");
		return -1;
	} else	{
		printf("chmod_test: working\n");
		return 0;
		}
}

int truncate_test(char* arg) {
	int ret;
	if ((ret = truncate(arg, 100000)) < 0) {
		perror("truncate_test: truncate() error");
		return -1;
	} else	{
		printf("truncate_test: working\n");
		return 0;
		}
}




int read_open_dir_test(char* arg ) {
	DIR *dir;		/*analogue FILE*/
		
	if ((dir=opendir("./"))==0)
	    {
	        perror("Diropen error\n");
	        return -1;
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
	if (!exsts)	{  
		printf("read_open_dir_test: File isn't found\n"); 
		return -1;
		} else return 0;
}

int link_test(char* arg1, char* arg2) {
	int ret;
	if ((ret = link(arg1, arg2)) < 0) {
		perror("link_test: link() error");
		return -1;
	} else	{
		printf("link_test: working\n");
		return 0;
		}
}


int rename_test(char* arg1, char* arg2) {
	int ret;
	if ((ret = rename(arg1, arg2)) < 0) {
		perror("rename_test: rename() error");
		return -1;
	} else	{
		printf("rename_test: working\n");
		return 0;
		}
}


int symlink_test(char* arg1, char* arg2) {
	int ret;
	if ((ret = symlink(arg1, arg2)) < 0) {
		perror("symlink_test: symlink() error");
		return -1;
	} else	{
		printf("symlink_test: working\n");
		return 0;
		}
}


int mkdir_test(char* arg) {
	int ret;
	if ((ret = mkdir(arg, S_IRUSR)) < 0) {
		perror("mkdir_test: mkdir() error");
		return -1;
	} else	{
		printf("mkdir_test: working\n");
		return 0;
		}
}

int rmdir_test(char* arg) {
	int ret;
	if ((ret = rmdir(arg)) < 0) {
		perror("rmdir_test: rmdir() error");
		return -1;
	} else	{
		printf("rmdir_test: working\n");
		return 0;
		}
}






int main (int argc, char* argv[]) {
	char *filename;
	if (argv[1] != 0) 
		filename = argv[1]; 
	else
		filename = "ещеболеедлинноеоченьдлинноеимяоченьдлинноеимяоченьдлинноеимяоченьдлинноеимяоченьдлинноеимя\
оченьдлинноеимяоченьдлинноеимяоченьдлинноеимяоченьдлинноеимя";
	int err = 0;
	err += creat_test(filename);
	err += access_test(filename);
	err += chmod_test(filename);
	err += open_test(filename);
	err += stat_test(filename);
	err += read_open_dir_test(filename);

	err += unlink_test(filename);
	err += creat_test(filename);
	err += symlink_test(filename, "simply_symlink");
	err += unlink("simply_symlink");
	err += rename(filename, "newname");
	err += rename("newname", filename);
	err += chmod_test(filename);
	err += fopen_test(filename);
	err += truncate_test(filename);
	err += link_test(filename, "simply_link");
	err += unlink("simply_link");
	err += remove_test(filename);
	err += mkdir_test(filename);
	err += rmdir_test(filename);
	
	printf("Errors: %d\n", (-err));
	
	return 0;
}
