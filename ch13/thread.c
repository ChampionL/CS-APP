#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

void *thread(void *vargp)
{
	printf("Hello world\n");
	return NULL;
}

int main()
{
	pthread_t tid;
	pthread_create(&tid, NULL, thread, NULL);
	pthread_join(tid, NULL);
	exit(0);
}
