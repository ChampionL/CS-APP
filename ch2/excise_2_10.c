#include <stdio.h>

int bit_level_equal(int x, int y)
{
	return !(x ^ y);
}
int main()
{
	printf("compare 2 == 3 ?: %d\n", bit_level_equal(2,3));
	printf("compare 2 == 2 ?: %d\n", bit_level_equal(2,2));

	return 0;;
}
