#include <stdio.h>
#include <unistd.h>

int main()
{
	int i;
	for ( i=0; i < 3; i++){
		if (fork() < 0)
			printf("ERROR");
	}
	printf("hello!!\n");
	while(1);
	return 0;
}
