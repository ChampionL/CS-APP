#include <stdio.h>

void f(void);

int __attribute__((weak))x = 15213;

int main()
{
	printf("before f x = %d\n", x);
	f();
	printf("after x x = %d\n", x);
	return 0;
}
