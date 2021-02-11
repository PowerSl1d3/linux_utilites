#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int cmp(const void* lhs, const void* rhs) {
	char* lhs_p = (char*)lhs;
	char* rhs_p = (char*)rhs;
	
	if (*lhs_p < *rhs_p) {
		return 1;
	} else if (*lhs_p == *rhs_p) {
		return 0;
	}

	return -1;
}

int main(int argc, char* argv[]) {

        struct sockaddr_in local;

        if (argc != 2) {
                printf("Error\n");
                return 1;
        }

        int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	int client_socket;
        //printf("socket = %d\n", server_socket);

        inet_aton("127.0.0.1", &local.sin_addr);
        local.sin_port = htons(atoi(argv[1]));
        local.sin_family = AF_INET;

        int result = bind(server_socket, (struct sockaddr*) &local, sizeof(local));
        if (result == -1) {
                printf("ERROR: bind returned -1\n");
                return 2;
        }

	listen(server_socket, 5);

	client_socket = accept(server_socket, NULL, NULL);

        char buf[BUFSIZ];
        while (1) {
                int bytes = read(client_socket, buf, BUFSIZ - 1);
                buf[bytes] = '\0';
                if (strcmp(buf, "OFF\n") == 0) {
			shutdown(client_socket, SHUT_RDWR );
                        shutdown(server_socket, SHUT_RDWR );
			close(client_socket);
                        close(server_socket);
                        return 0;
                }
		qsort(buf, strlen(buf), sizeof(char), cmp);
		write(client_socket, buf, bytes);
        }

        return 0;

}
