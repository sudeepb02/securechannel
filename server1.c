#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int clientfd = 0;
	char buffer[1024];

	struct sockaddr_in saddr;

	clientfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&saddr, '0', sizeof(saddr));
	memset(buffer, '0', sizeof(buffer));

	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(5000);

	bind(clientfd, (struct sockaddr*)&saddr, sizeof(saddr));

	listen(clientfd, 10);

	/* File descriptor of accepted connection 	*/

	int connfd = 0; 
	while(1)
	{
		connfd = accept(clientfd, (struct sockaddr*)NULL, NULL);

		strcpy(buffer, "Some hardcoded message\n");
		write(connfd, buffer, strlen(buffer));

		close(connfd);
		sleep(1);
	}
}

