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
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "csapp.h"


#define MAXLINE 1024
extern char **environ;

void doit(int fd);
void read_requesthdrs(rio_t *rp);
int parse_uri(char *uri, char *filename, char *cgiargs);
void serve_static(int fd, char *filename, int filesize);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *filename, char *filetype);
void clienterror(int fd, char *cause, char *errnum, char *shortmasg, char *longmsg);

int main(int argc, char **argv)
{
	int listenfd, confd, port, clientlen;
	struct sockaddr_in clientaddr;

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
	
	struct sockaddr_in serveraddr;
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	inet_aton("127.0.0.1", &serveraddr.sin_addr);
	if( -1 == bind(serverfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr))){
		fprintf(stderr, "bind error\n");
		close(serverfd);
		exit(-1);
	}	

	if(-1 == listen(serverfd, 10)){
		fprintf(stderr, "listen error\n");
		close(serverfd);
		exit(-1);
	}
	
	while(1){
		int len = sizeof(clientaddr);
		int clinetfd = accept(serverfd, (struct sockaddr *)&clientaddr, &len);
		fprintf(stdout, "connect from %s\n", inet_ntoa(clientaddr.sin_addr));
		doit(clinetfd);
		close(clinetfd);
	}
	return 0;
}

void doit(int fd)
{
	int is_static;
	struct stat sbuf;
	char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
	char filename[MAXLINE], cgiargs[MAXLINE];
	rio_t rio;

	// read request line and headers
	rio_readinitb(&rio, fd);
	rio_readlineb(&rio, buf,MAXLINE);
	sscanf(buf, "%s %s %s", method, uri, version);
	if(0 != strcmp(method, "GET")){
		clienterror(fd, method, "501", "Not Implemented",
		"Tiny does not implement this method");
		return;
	}

	read_requesthdrs(&rio);

	// parse URI from GET request
	is_static = parse_uri(uri, filename, cgiargs);
	if(stat(filename, &sbuf) < 0){
		clienterror(fd, filename, "404", "Not found","Tiny couldn't find this file");
		return;
	}

	if(is_static){
		if(!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR && sbuf.st_mode)){
			clienterror(fd, filename, "403", "Forbidden", "Ting couldn't read the file");
			return;
		}
		serve_static(fd, filename, sbuf.st_size);
	}
	else{
		if(!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)){
			clienterror(fd, filename, "403", "Forbidden", "Tiny couldn't run the CGI program");
			return;
		}
		serve_dynamic(fd, filename, cgiargs);
	}
}

void clienterror(int fd, char *cause, char *errnum, char *shormsg, char *longmsg)
{
	char buf[MAXLINE], body[MAXLINE];

	// Build the HTTP response body
	sprintf(body, "<html><title>Tiny Error<title>");
	sprintf(body, "%s <body bgcolor = ""ffffff"">\r\n", body);
	sprintf(body, "%s%s:%s\r\n", body, errnum, shormsg);
	sprintf(body, "%s<p>%s:%s\r\n", body, longmsg, cause);
	sprintf(body, "%s<hr><em> The Tiny Web Server</em>\r\n", body);

	sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shormsg);
	rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "Content-type: text/html\r\n");
	rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "Content-length:%ld\r\n\r\n", strlen(body));
	rio_writen(fd, buf, strlen(buf));
	rio_writen(fd, body, strlen(body));
}

void read_requesthdrs(rio_t *rp)
{
	char buf[MAXLINE];
		
	rio_readlineb(rp, buf, MAXLINE);
	while(strcmp(buf, "\r\n")){
		rio_readlineb(rp, buf, MAXLINE);
	}

	return;
}

int parse_uri(char *uri, char *filename, char *cgiargs)
{
	char *ptr;
	
	if(! strstr(uri, "cgi-bin")){
		strcpy(cgiargs, "");
		strcpy(filename, ".");
		strcat(filename, uri);
		if(uri[strlen(uri) - 1] == '/')
			strcat(filename, "home.html");
		return 1;
	}
	else{
		ptr = index(uri, '?');
		if(ptr){
			strcpy(cgiargs, ptr + 1);
			*ptr = '\0';
		}
		else
			strcpy(cgiargs, "");
		strcpy(filename, ".");
		strcpy(filename, uri);
		return 0;
	}
}

void serve_static(int fd, char *filename, int filesize)
{
	int srcfd;
	char *srcp, filetype[MAXLINE], buf[MAXLINE];

	// send response headers to client
	get_filetype(filename, filetype);
	sprintf(buf, "HTTP/1.0 200 OK \r\n");
	sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
	sprintf(buf, "%sContent-length:%d\r\n", buf, filesize);
	sprintf(buf, "%sContent-type:%s\r\n\r\n", buf, filetype);
	rio_writen(fd, buf, strlen(buf));

	// send response body to client
	srcfd = open(filename, O_RDONLY,0);
	srcp = mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
	close(srcfd);
	rio_writen(fd, srcp, filesize);
	munmap(srcp, filesize);
}

void get_filetype(char *filename, char *filetype)
{
	if(strstr(filename, ".html"))
		strcpy(filetype, "text/html");
	else if(strstr(filename, ".gif"))
		strcpy(filetype, "imag/gif");
	else if(strstr(filename, ".jpeg"))
		strcpy(filetype, "imag/jpeg");
	else
		strcpy(filetype, "text/plain");
}


void serve_dynamic(int fd, char *filename, char *cgiargs)
{
	char buf[MAXLINE],*emptylist[] = {NULL};
	
	// return first part of HTTP response
	sprintf(buf, "HTTP/1.0 200 OK \r\n");
	rio_writen(fd, buf, strlen(buf));
	
	if(fork() == 0){
		setenv("QUERY_STRING", cgiargs, 1);
		dup2(fd, STDOUT_FILENO);
		execve(filename, emptylist, environ);
	}

	wait(NULL);
}
