#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int counter_SIGUSR1 = 0;
int counter_SIGUSR2 = 0;

void handler_SIGUSR1(int signal) {

	++counter_SIGUSR1;

}

void handler_SIGUSR2(int signal) {

	++counter_SIGUSR2;

}

void exiter(int signal) {

	printf("%d %d\n", counter_SIGUSR1, counter_SIGUSR2);
	exit(0);

}

int main(int argc, char* argv[]) {

	signal(SIGUSR1, handler_SIGUSR1);
	signal(SIGUSR2, handler_SIGUSR2);
	signal(SIGTERM, exiter);
	while(1) {
		pause();
	}

	return 0;

}
