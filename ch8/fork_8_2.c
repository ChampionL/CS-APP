#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int main()
{
	int i;
	for ( i=0; i < 3; i++){
		if (fork() < 0){
			fprintf(stderr, "ERROR:%d\n", strerror(errno));
			exit(0);
			}
	}
	printf("hello!!\n");
	return 0;
}
