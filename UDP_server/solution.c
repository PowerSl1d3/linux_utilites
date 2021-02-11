#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {

	struct sockaddr_in local;

	if (argc != 2) {
		printf("Error\n");
		return 1;
	}

	int server_socket = socket(AF_INET, SOCK_DGRAM, 0);
	//printf("socket = %d\n", server_socket);

	inet_aton("127.0.0.1", &local.sin_addr);
	local.sin_port = htons(atoi(argv[1]));
	local.sin_family = AF_INET;

	int result = bind(server_socket, (struct sockaddr*) &local, sizeof(local));
	if (result == -1) {
		printf("ERROR: bind returned -1\n");
		return 2;
	}

	char buf[BUFSIZ];
	while (1) {
		int bytes = read(server_socket, buf, BUFSIZ - 1);
		buf[bytes] = '\0';
		if (strcmp(buf, "OFF\n") == 0) {
			shutdown(server_socket, SHUT_RDWR );
			close(server_socket);
			return 0;
		}
		printf("%s\n", buf);
	}

	return 0;

}
