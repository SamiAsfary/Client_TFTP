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
	char *hostname;
	char *filename;
	
	
	if(argc != 3){
		sprintf(reponse, "The correct syntax for this program is: %s [host] [file]\n", argv[0]);
		write(STDOUT_FILENO, reponse ,strlen(reponse));
		exit(EXIT_FAILURE);
	}else{
		hostname = argv[1];
		filename = argv[2];
	}
	
	
	filename = filename;
	hostname=hostname;
	
	
	
	return 0;
}
