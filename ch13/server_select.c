#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/select.h>

#define MAX_FD 1024
int main()
{
	int serverfd;

	int fds[MAX_FD];// all clinet fd
	int id = 0; // number of monitor fd

	fd_set allfds;
	FD_ZERO(&allfds);

	int maxfd = -1;
	int i;
	for(i = 0; i < MAX_FD; i++)
		fds[i] = -1;
	
	struct sockaddr_in addr;
	/* 1. open socket */
	serverfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == serverfd){
		printf("open socket error\n");
		exit(-1);
	}

	/* 2.bind to socket */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	inet_aton("192.168.153.135", &addr.sin_addr);
	if(-1 == bind(serverfd, (struct sockaddr *)&addr, sizeof(addr))){
		printf("bind socket error\n");
		close(serverfd);
		exit(-1);
	}

	/* 3.listen to socket*/
	if(-1 == listen(serverfd, 10)){
		printf("listen error\n");
		close(serverfd);
		exit(-1);
	}	

	while(1){
		FD_ZERO(&allfds);
		maxfd = -1;
		FD_SET(serverfd, &allfds);
		maxfd = maxfd > serverfd? maxfd:serverfd;
		
		// add all clinet to monitor fd
		for(i = 0; i < id; i++)
		{
			if(-1 != fds[i]){
				FD_SET(fds[i], &allfds);
				maxfd = fds[i] > maxfd ? fds[i]:maxfd;
			}
		}

		// monitor socket
		int r = select(maxfd + 1, &allfds, NULL, NULL, NULL);
		if(-1 == r){
			printf("select error\n");
			// close all socket
			for(i = 0; i < id; i++){
				if(-1 != fds[i]){
					fds[i] = -1;
					close(fds[i]);
				}
			}
			exit(-1);
		}

		if(FD_ISSET(serverfd, &allfds)){
			/* 4.accept client connect */
			struct sockaddr_in from_addr;
			int len = sizeof(from_addr);
			fds[id] = accept(serverfd, (struct sockaddr*)&from_addr, &len);
			if(-1 == fds[id]){
				printf("client connect error\n");
				// close all socket
				for(i = 0; i < id; i++){
					if(-1 != fds[i]){
						fds[i] = -1;
						close(fds[i]);
					}
				}
				exit(-1);
				
			}
			printf("connect from:%s\n", inet_ntoa(from_addr.sin_addr));
			id++;
		}

		//	recv data from client
		for(i = 0; i < id; i++){
			if((-1 != fds[i]) && FD_ISSET(fds[i], &allfds)){
				int buf;
				int ret;
				ret = recv(fds[i], &buf, MSG_WAITALL, 0);
				if(0 == ret){
					printf("The client is shutdown\n");
					fds[i] = -1;
					close(fds[i]);
					continue;
				}
				else if(-1 == ret){
					printf("netork error\n");
				}
				else{
					printf("read from clinet:%d\n", buf);
				}
			}
		}
		
	}

	/* 7. server socket */
	close(serverfd);

	return 0;
}

