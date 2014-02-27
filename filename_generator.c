#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include "filename_generator.h"

void generate_rus_filename(int n, char * rus_name) {
        if (rus_name) {
		char * alphabet = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
		srand( time(NULL));
		int j = 0;
		int i = 0;
		for(i = 0; i < 2*n; i++) {
			j = 2 * (rand() % 33);
			rus_name[i] = alphabet[j];
			j++;
			i++;
			rus_name[i] = alphabet[j];
                }
                rus_name[++i] = '\0';
		printf("Generated name : %s\n", rus_name);
	} else {
                printf("Can't generate russian name");
                exit(1);
        }
}

void generate_eng_filename(int n, char * eng_name) {
	if (eng_name) {
		char alphabet[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m'\
			,'n','o','p','q','r','s','t','u','v','w','x','y','z'};
		srand( time(NULL));
		int i = 0;
		for(i = 0; i < n; i++) {
			eng_name[i] = alphabet[(rand() % 26)];
		}
		eng_name[++i] = '\0';
		printf("Generated name : %s\n", eng_name);
	} else {
		printf("Can't generate english name");
		exit(1);
	}

}