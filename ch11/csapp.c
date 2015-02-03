#ifndef __CSAPP__H
#include "csapp.h"
#endif

ssize_t rio_readn(int fd, void *userbuf, size_t n)
{
	size_t nleft = n;
	ssize_t nread;
	char *bufp = userbuf;

	while(nleft > 0){
		if((nread = read(fd, bufp, nleft)) < 0){
			if(errno < EINTR)
				nread = 0;
			else
				return -1;
		}
		else if(nread == 0)
			break;
		nleft -= nread;
		bufp += nread;
	}
	return n - nleft;
}

ssize_t rio_writen(int fd, void *userbuf, size_t n)
{
	size_t nleft = n;
	ssize_t nwritten;
	char *bufp = userbuf;
	
	while(nleft > 0){
		if(nwritten = write(fd, bufp, nleft) <= 0){
			if(errno == EINTR)
				nwritten = 0;
			else
				return -1;
		}
		nleft -= nwritten;
		bufp += nwritten;
	}
	return n;
}



