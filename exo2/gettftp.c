#include <unistd.h>
#include <stdio.h>
#include  "string.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


int main(int argc, char* argv[]){
	char reponse[256];
	int s;
	char *hostname;
	char *filename;
	struct addrinfo hints = {0};
	struct addrinfo *result;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	
	
	if(argc != 3){
		sprintf(reponse, "The correct syntax for this program is: %s [host] [file]\n", argv[0]);
		write(STDOUT_FILENO, reponse ,strlen(reponse));
		exit(EXIT_FAILURE);
	}else{
		hostname = argv[1];
		filename = argv[2];
	}
	
	s = getaddrinfo(hostname,"1069",&hints,&result);
	if (s != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}
	
	
	freeaddrinfo(result);

	filename = filename;
	
	
	
	return 0;
}
