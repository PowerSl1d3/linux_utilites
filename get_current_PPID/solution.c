#include <stdio.h>

#define BUFSIZE 512

int main(int argc, char* argv[]) {

	FILE* file_stat = fopen("/proc/self/stat", "r");

	char buf[BUFSIZE];

	int i = 0;
	while (i < 6) {
		fscanf(file_stat, " %s", buf);
		i++;
	}

	printf("%s\n", buf);
	fclose(file_stat);

	return 0;

}
