#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

	pid_t pid =  fork();

	if (!pid) {
		chdir("/");
		printf("%d\n", setsid());
		fclose(stdout);
		fclose(stderr);
		fclose(stdin);
		pause();
	}

	return 0;

}
