#include <stdio.h>
#include <pthread.h>
#define N 20

void *thread(void *vargp)
{
	int myid = *((int *)vargp);
	printf("Hello Number from thread:%d\n", myid);
}

int main()
{
	pthread_t tid[N];
	int i=2;
	for(i = 0; i < N; i++){
		pthread_create(&tid[i], NULL, thread, &i);
		sleep(1);
	}
	for(i = 0; i< N; i++){
		pthread_join(tid[i], NULL);
	}
	return 0;
}
