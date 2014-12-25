#include <stdio.h>
#include <stdlib.h>


int main()
{
	int *ptr = (int *)malloc(sizeof(int));
	
	*ptr = 100;
	return 0;
}
