#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void handler(int signal) {

	exit(0);

}

int main(int argc, char* argv[]) {

	pid_t pid =  fork();

	if (!pid) {
		if (chdir("/")) {
			printf("ERROR!");
			exit(1);
		}
		printf("%d\n", setsid());
		signal(SIGURG, handler);
		fclose(stdout);
		fclose(stderr);
		fclose(stdin);
		pause();
	}

	return 0;

}
