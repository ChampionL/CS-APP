#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define MAX 10000000

unsigned int cnt = 0;
void *count(void *vptr)
{
	int i;
	for(i = 0; i< MAX; i++){
		cnt++;
	}
}

int main()
{
	pthread_t tid1, tid2;
	pthread_create(&tid1,NULL,count, NULL);
	pthread_create(&tid2,NULL,count, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	if(MAX*2 != cnt)
		printf("BOOM!!!!!cnt = %d\n", cnt);
	else
		printf("OK cnt = %d\n", cnt);
	exit(0);
}
