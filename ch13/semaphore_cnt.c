#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX 10000000

unsigned int cnt = 0;
sem_t mutex;
void *count(void *vptr)
{
	int i;
	for(i = 0; i< MAX; i++){
		sem_wait(&mutex);
		cnt++;
		sem_post(&mutex);
	}
}

int main()
{
	pthread_t tid1, tid2;
	sem_init(&mutex, 0, 1);
	pthread_create(&tid1,NULL,count, NULL);
	pthread_create(&tid2,NULL,count, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	if(MAX*2 != cnt)
		printf("BOOM!!!!!cnt = %d\n", cnt);
	else
		printf("OK cnt = %d\n", cnt);
	sem_destroy(&mutex);
	exit(0);
}
