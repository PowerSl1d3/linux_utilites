#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	char arg_prog[BUFSIZ];

	sprintf(arg_prog, "./%s %s", argv[1], argv[2]);

	FILE* prog = popen(arg_prog, "r");

	size_t counter = 0;
	int current_symbol;

	while ((current_symbol = fgetc(prog)) != EOF) {
		if (current_symbol == '0') {
			++counter;
		}
	}

	printf("%ld\n", counter);

	fclose(prog);

	return 0;

}
