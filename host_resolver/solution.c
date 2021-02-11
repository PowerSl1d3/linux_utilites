#include <stdio.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char* argv[]) {

	if ( argc != 2 ) {
		return 1;
	}

	struct hostent* h;
	h = gethostbyname(argv[1]);

	if ( NULL == h ) {
		printf("Error\n");
		return 2;
	}

	//printf("Canonycal name = %s\n", h->h_name );
	//printf("Type = %s Len = %d\n", (h->h_addrtype == AF_INET) ? "IPv4" : "IPv6", h->h_length);

	int i = 0;

	while (h->h_addr_list[i] != NULL) {

		struct in_addr* a = (struct in_addr*) h->h_addr_list[i];
		printf("%s\n", inet_ntoa(*a));
		++i;

	}

	return 0;

}
