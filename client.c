#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <termios.h>
#include <stdbool.h>

#include "handle.h"
#include "menu.h"

#define MAXLINE 250
#define SA struct sockaddr



int main(int argc, char* argv[])
{
    int sock;  
    struct sockaddr_in sAddr;

    memset((void *) &sAddr, 0, sizeof(struct sockaddr_in));
	sAddr.sin_family = AF_INET;
	sAddr.sin_addr.s_addr = INADDR_ANY;
	sAddr.sin_port = 0;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	bind(sock, (const struct sockaddr *) &sAddr, sizeof(sAddr));

	sAddr.sin_addr.s_addr = inet_addr(argv[1]);
	sAddr.sin_port = htons(atoi(argv[2]));
	if (connect(sock, (const struct sockaddr *) &sAddr, sizeof(sAddr)) != 0) 
	{
		perror("client");
		return 0;
	}

    menuLogin(sock);


    close(sock);
    return 0; 
}
