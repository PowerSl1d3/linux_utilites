#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "lib.h"

int main(int argc, char* argv[]) {

	if (argc != 2) {
		printf("Please, put 2 arguments!\n");
		return EXIT_FAILURE;
	}

	int c = 0;

	printf("%d\n", stringstat(argv[1], 2, &c));
	printf("%d\n", c);

	return EXIT_SUCCESS;

}
