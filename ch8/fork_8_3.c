#include <stdio.h>
#include <unistd.h>

void doit()
{
	fork();
	fork();
	printf("hello!!\n");

}
int main()
{
	doit();
	printf("hello!!\n");
	while(1);
	return 0;
}
