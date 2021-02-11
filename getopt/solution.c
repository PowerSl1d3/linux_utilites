#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

	extern int opterr;

	opterr = 0;

	int opchar = 0;
	int correct = 1;
	int number;

	struct option opts[] = {
		{"query", required_argument, 0, 'q'},
		{"longinformationrequest", no_argument, 0, 'i'},
		{"version", no_argument, 0, 'v'},
		{0,0,0,0}
	};

	while ( -1 != (opchar = getopt_long(argc, argv, "q:iv", opts, NULL)) ) {
		switch(opchar) {
			case 'q':
				number = atoi(optarg);
				if (!number) {
					correct = 0;
				}
				break;
			case 'i':
				break;
			case 'v':
				break;
			default:
				correct = 0;
				break;
		}
	}

	if (correct) {
		printf("+\n");
	} else  {
		printf("-\n");
	}

	return 0;

}
