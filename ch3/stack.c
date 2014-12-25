#include <stdio.h>
#include <stdlib.h>

int globalx = 12;
void print()
{
	int localx = 0;
	printf("address of function print's localx=%p\n", &localx);
}

int main()
{
	int localx = 0l;
	int localy = 02;
	int *mallocx = (int *)malloc(sizeof(int));
	printf("address of function main's localx=%p\n", &localx);
	printf("address of function main's localy=%p\n", &localy);
	printf("address of globalx=%p\n", &globalx);
	printf("address of mallocx=%p\n", mallocx);
	printf("address of print=%p\n", print);
	print();	
	
	printf("pid = %d\n", getpid());	

	//LOOP
	while(1);
	return 0;
}
