#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdbool.h>

bool get_ppid_from_pid_that_equal_input_pid(char* current_pid, char* cmp_pid) {
        char proc_dir[BUFSIZ] = {0};
	char* pid = (char*)malloc(BUFSIZ * sizeof(char));
	strcpy(pid, current_pid);
	
	while (!(strcmp(pid, cmp_pid) == 0 || strcmp(pid, "1") == 0 || strcmp(pid, "0") == 0)) {
		
		sprintf(proc_dir, "/proc/%s/stat", pid);
        	FILE* file_stat = fopen(proc_dir, "r");

        	int ppid;

		int c = fscanf(file_stat, "%*d %*s %*c %d", &ppid);
		c++;

		char buff[BUFSIZ];
		sprintf(buff, "%d", ppid);

        	strcpy(pid, buff);
        	fclose(file_stat);

	}

	if (strcmp(pid, cmp_pid) == 0) {
		free(pid);
		return true;
	}

	free(pid);
	return false;
}

int main(int argc, char* argv[]) {

	if (argc != 2) {
		printf("Error: you should pass argument!\n");
		return 1;
	}

	int counter = 0;

	DIR* proc = opendir("/proc/");

        struct dirent* proc_dir;

        while ((proc_dir = readdir(proc)) != NULL) {
                if (atoi(proc_dir->d_name)) {
			if (get_ppid_from_pid_that_equal_input_pid(proc_dir->d_name, argv[1])) {
				++counter;
			}
                }
        }

        printf("%d\n", counter);
        closedir(proc);

	return 0;
}
