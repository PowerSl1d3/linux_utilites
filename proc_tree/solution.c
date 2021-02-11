#include <stdio.h>
#include <string.h>

void get_ppid_from_pid(char* pid) {
	char proc_dir[BUFSIZ] = {0};
	strcat(strcat(strcat(proc_dir, "/proc/"), pid),"/stat");
	FILE* file_stat = fopen(proc_dir, "r");

	char buf[BUFSIZ] = {0};

	int i = 0;
	while (i < 4) {
		fscanf(file_stat, " %s", buf);
		i++;
	}

	strcpy(pid, buf);
	fclose(file_stat);
}

int main(int argc, char* argv[]) {

	if (argc != 2) {
		printf("Error: you should pass argument!");
		return 1;
	}

	printf("%s\n", argv[1]);

	char current_pid[BUFSIZ];
	strcpy(current_pid, argv[1]);

	while (strcmp(current_pid, "1") != 0) {
		get_ppid_from_pid(current_pid);
		printf("%s\n", current_pid);
	}

	return 0;
}
