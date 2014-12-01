#include <stdio.h>
#define MASK 0x01
typedef unsigned char * byte_point;

void show_binary(byte_point start, int n)
{
	int i,j;
	for(i = 0; i < n; i++){
		for(j = 0; j < 8; j++){
		//	printf("%.2x", start[i]);
			printf("%.2x -- %d = %c \n", start[i], j, (start[i] >> j) & MASK + '0');
		}
	}
	putchar('\n');

}
int main()
{
	int i = 12345;
	float f = i;
	show_binary((byte_point)&i, sizeof(int) );
}
