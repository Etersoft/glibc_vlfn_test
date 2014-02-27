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
#include "filename_generator.h"
#include "glibc_tests.h"


int main (int argc, char* argv[]) {
	int failed = 0;
	int passed = 0;
	int testing_length = 1024;
	int opt;
	size_t englen = 0;
	size_t ruslen = 0;
	char * rusname = NULL;
	char * engname = NULL;
	if (argc == 1) {
		printf("Type \"test -h\" for help\n");
                exit(1);
	}
	while((opt = getopt(argc, argv, "he:r:l:")) != -1) {
		switch (opt) {
			case 'h':
				printf("Usage:\n -e <num> - tests for english filename "
				"with <num> length. Don't use it with -r; \n "
				"-r <num> - tests for russian filname "
				"with <num> length. Don't use it with -e; \n "
				"-l <num> - length of testing bound; \n"
				"-h - print this help\n");
				exit(1);
			case 'e':
				englen = atoi(optarg);
				if (englen <= 0 || englen >= 4096) {
					printf("Wrong english filename length\n");
					exit(1);
				} else {				
					engname = calloc(englen, sizeof(char)+1);
					generate_eng_filename(englen, engname);
					break;
				}
			case 'r':
				ruslen = atoi(optarg);
                                
				if (ruslen <= 0 || ruslen >= 4096) {
					printf("Wrong russian filename length\n");
					exit(1);
				} else {
					rusname = calloc(ruslen, 2*sizeof(char)+1);
					generate_rus_filename(ruslen, rusname);
					break;
				}
			case 'l':
				testing_length = atoi(optarg);
				if (testing_length <= 0 || testing_length >= 4095) {
					printf("Wrong testing length %d. Must be"
					"between 0 and 4094", testing_length );
					exit(1);
				}
				break;
			default:
				printf("Type \"test -h\" for help\n");
				exit(1);
		}
	}



	/*Request for parameter - length of the filename, from which searching of the largest available filename starts*/
	char* filename = NULL;
	errno = 0;	

	if (ruslen) {
		filename = rusname;
	} else if (englen) {
		filename = engname;
		}
/*	filename[0] = "оченьдлинноеимяоченьдлинноеимяоченьдлинноеимяоченьдлинноеимякомунужнытакиеименаочень\
длинноеимяоченьдлинноеимяоченьдлинноеимяоченьдлинноеимяидлиннаяконцовкас тремя пробелами .И заглавной буквой.\
Сделаем имя очень длинным. Вряд ли кому-то в голову придет называть файл таким длинным именем. Даже чуть длиннее,\
проверим символы: АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ и нижние буквы абвгдеёжзийклмнопрстуфхцчшщъыьэюя. Возможно, \
я ошибся с порядком, поэтому проверю знаки: !№;%:?*()_-+=. Я точно не знаю, сколько они занимают байт, думаю, что\
немного. И...конец!!!";

	filename[1] = "оченьдлинноеимяоченьдлинноеимяоченьдлинноеимяоченьдлинноеимякомунужнытакиеименаочень\
длинноеимяоченьдлинноеимяоченьдлинноеимяоченьдлинноеимяидлиннаяконцовкас тремя пробелами .И заглавной буквой.\
Сделаем имя очень длинным. Вряд ли кому-то в голову придет называть файл таким длинным именем. Даже чуть длиннее,\
проверим символы: АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ и нижние буквы абвгдеёжзийклмнопрстуфхцчшщъыьэюя. Возможно, \
я ошибся с порядком, поэтому проверю знаки: !№;%:?*()_-+=. Я точно не знаю, сколько они занимают байт, думаю, что\
немного. И...конец!!!!";
*/	
	
#define failing printf("Error in line:%d; file: %s: %s\n", __LINE__, __FILE__, strerror(errno)), failed++
#define passing ++passed

#define ok(x) ((x) == (strlen(filename) < testing_length)) ? (passing) : (failing)

//	#define ok(x) ((x) ? (failing()) : (passing())) 

		printf("Testing glibc functions with %zd-byte filename\n", strlen(filename));
		ok(creat_test(filename));
		ok(access_test(filename));
		ok(chmod_test(filename));
		ok(open_test(filename));
		ok(stat_test(filename)); 
		ok(lstat_test(filename)); 
		ok(read_open_dir_test(filename)); 
		ok(unlink_test(filename));
		ok(creat_test(filename));
		ok(rename_test(filename, "newname"));
		ok(rename_test("newname", filename));
		ok(chmod_test(filename));
		ok(fopen_test(filename));
		ok(truncate_test(filename));
		ok(link_test(filename, "simply_link"));
		ok(unlink_test("simply_link"));
		ok(remove_test(filename));
		ok(symlink_test( "simply_symlink", filename));
		ok(unlink_test(filename));
		ok(mkdir_test(filename));
		ok(read_open_dir_test(filename));
		ok(rmdir_test(filename));
		printf("FAILED: %d, PASSED: %d\n\n", failed, passed);
		failed = 0;
		passed = 0;

}
