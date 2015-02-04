#ifndef __CSAPP__H
#define __CSAPP__H

#include <unistd.h>
#include <errno.h>
#include <string.h>
#define RIO_BUFSIZE 8192

typedef struct {
	int rio_fd; // descriptor for this internal buf
	int rio_cnt; //unread bytes in internal buf
	char *rio_bufptr; // next unread byte in internal buf
	char rio_buf[RIO_BUFSIZE]; //internal buf
} rio_t;

ssize_t rio_readn(int fd, void *userbuf, size_t n);

ssize_t rio_writen(int fd, void *userbuf, size_t n);

void rio_readinitb(rio_t *rp, int fd);

ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);

ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n);
#endif
