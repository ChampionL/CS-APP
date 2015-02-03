#ifndef __CSAPP__H
#define __CSAPP__H

#include <unistd.h>
ssize_t rio_readn(int fd, void *userbuf, size_t n);
size_t rio_writen(int fd, void *buf, size_t n);

#endif
