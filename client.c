#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int sockfd = 0;
	char buffer[1024];
	struct sockaddr_in saddr;

	if(argc != 2)
	{
		printf("Usage : %s <IP> \n", argv[0]);
		return 1;
	}

	memset(buffer, '0', sizeof(buffer));

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("Error creating socket\n");
		return 1;
	}

	memset(&saddr, '0', sizeof(saddr));

	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(5000);

	if(inet_pton(AF_INET, argv[1], &saddr.sin_addr)<=0)
	{
		printf("Error\n");
		return 1;
	}

	if(connect(sockfd, (struct sockaddr*)&saddr, sizeof(saddr)) < 0)
	{
		printf("Error : connection failed\n");
		return 1;
	}

	int n;		//No of bytes read
	while((n = read(sockfd, buffer, sizeof(buffer)-1))>0)
	{
		buffer[n] = 0;
		if(fputs(buffer, stdout) == EOF)
		{
			printf("Error\n");
		}
	}

	if(n < 0)
	{
		printf("No data received\n");
	}

	return 0;
}

