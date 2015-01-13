#include <stdio.h>

void swap();

int buf[2] = {1,2};

int main()
{
	printf("before swap buf[0] = %d, buf[1] = %d\n", buf[0], buf[1]);
	swap();
	printf("after swap buf[0] = %d, buf[1] = %d\n", buf[0], buf[1]);
	return 0;
}
