#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <linux/un.h>
#include <string.h>

int main()
{
	/* 1.open client socket */
	int fd = socket(AF_INET,SOCK_STREAM, 0);
	if(-1 == fd){
		printf("open socket failed\n");
		exit(-1);
	}

	/* 2.connect to server*/
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	inet_aton("192.168.153.130", &addr.sin_addr);
	if(connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1){
		printf("connect error\n");
		close(fd);
		exit(-1);
	}
	
	/* 3.send data */
	int i;
	for( i = 0; i < 10; i++){
		sleep(1);
		send(fd, &i, sizeof(int), 0);
	}

	/* 4.close socket*/
	close(fd);
}
