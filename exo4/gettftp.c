#include <unistd.h>
#include <stdio.h>
#include  "string.h"
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>


int main(int argc, char* argv[]){
	const char* mode = "octet";
	char message[517];
	int sfd, s, msglen,fd;
	unsigned int loop;
	char *hostname;
	char *filename;
	char buff[513];
	struct addrinfo hints = {0};
	struct addrinfo *result, *rp;
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	
	
	if(argc != 3){
		sprintf(message, "The correct syntax for this program is: %s [host] [file]\n", argv[0]);
		write(STDOUT_FILENO, message ,strlen(message));
		exit(EXIT_FAILURE);
	}else{
		hostname = argv[1];
		filename = argv[2];
	}
	
	//recuperation de l'adresse et du port
	s = getaddrinfo(hostname,"1069",&hints,&result);
	if (s < 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		exit(EXIT_FAILURE);
	}
	
	//ouverture du socket
	for (rp = result; rp != NULL; rp = rp->ai_next) {
		sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if (sfd == -1){continue;}
		if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1){break;}
		close(sfd);
	}
	
	//construction du message
	message[0] = 0;message[1]=1;
	
	for(loop = 0; loop < strlen(filename); loop++){
		message[loop+2] = filename[loop];
	}
	msglen = loop+2;
	message[msglen]=0;
	msglen++;
	
	for(loop = 0; loop < strlen(mode); loop++){
		message[msglen-1+loop] = mode[loop];
	}
	msglen = loop+msglen;
	message[msglen]=0;
	msglen++;
	
	//envoie du message et reception de la reponce
	write(sfd, message, msglen);
	read(sfd,message, 517);
	
	fd = open(filename, O_CREAT | O_WRONLY | O_RDONLY, S_IRWXU);
	
	//ACK
	message[1] = 4;
	write(sfd,message,4);
	
	//ecriture du fichier
	for(loop = 0;loop < 513; loop++){
		buff[0] = message[loop+4];
	}	
	write(fd, message, strlen(message));
	
	
	
	freeaddrinfo(result);
	close(sfd);
	
	
	
	buff[0]=buff[0];
	
	
	return 0;
}
