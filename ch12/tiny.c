/**
 * Tiny.c - A simple iterative HTTP/1.0 Web server that uses the
 * GET method to serve static and dynamic content
 **/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <arpa/inet.h>

void doit(int fd);
void read_requesthdrs(char *rp);
int parse_uri(char *uri, char *filename, char *cgiargs);
void serve_static(int fd, char *filename, int filesize);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *cause, char *errnum, char *shortmasg, char *longmsg);

int main()
{
	int listenfd, confd, port, clientlen;
	struct socketaddr_in clinetaddr;

	// Open a socket on Port
	if(2 != argc){
		fprintf(stderr, "usage:%s<port>\n", argv[0]);
		exit(1);
	}
	port = atoi(argv[1]);

	int serverfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == serverfd){
		fprintf(stderr, "open socket error~~\n");
		exit(-1);
	}
	
	struct socketaddr_in serveraddr;
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	inet_aton("192.168.153.135", &serveraddr.sin_addr);
	if( -1 == bind(serverfd, (strcuct sockaddr *)serveraddr, sizeof(serveraddr))){
		fprintf(stderr, "bind error\n");
		close(serverfd);
		exit(-1);
	}	

	if(-1 == listen(serverfd, 10)){
		fprint(stderr, "listen error\n");
		close(serverfd);
		exit(-1);
	}
	
	while(1){
		int len = sizoef(clinetaddr);
		int clinetfd = accept(serverfd, (struct sockaddr *)&clinetaddr, &len);
		fprint(stdout, "connect from %s\n", inet_ntoa(clinetaddr.sin_addr));
		doit(clinetfd);
		close(clinetfd);
	}
	return 0;
}
