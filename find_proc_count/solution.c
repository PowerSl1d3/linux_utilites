#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int counter = 0;

int main(int argc, char* argv[]) {

	if (argc != 2) {
		printf("ERROR: you should pass argument!\n");
		return EXIT_FAILURE;
	}

	DIR* proc = opendir("/proc/");

	struct dirent* proc_dir;
	char proc_name[BUFSIZ], current_dir[BUFSIZ];
	
	while ((proc_dir = readdir(proc)) != NULL) {
		if (atoi(proc_dir->d_name)) {
			sprintf(current_dir, "/proc/%s/status", proc_dir->d_name);
			FILE* current_proc_stat = fopen(current_dir, "r");
			if (fscanf(current_proc_stat, " %s", proc_name)) {
				if (fscanf(current_proc_stat, " %s", proc_name)) {
					if (strcmp(argv[1], proc_name) == 0) {
						++counter;
					}
				}
			}
			fclose(current_proc_stat);
		}
	}

	printf("%d\n", counter);
	closedir(proc);
	return 0;

}
