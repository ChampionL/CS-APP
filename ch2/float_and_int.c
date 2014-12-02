#include <stdio.h>
#define MASK 0x80
typedef unsigned char * byte_point;

void show_binary(byte_point start, int n)
{
	int i,j;
	for(i = n - 1; i >= 0; i--){
		for(j = 0; j < 8; j++){
		//	printf("%.2x", start[i]);
			printf("%c",(((start[i] << j) & MASK) >> 7) + '0');
		}
		putchar(' ');
	}
	putchar('\n');

}
int main()
{
	int i = 12345;
	float f = i;
	show_binary((byte_point)&i, sizeof(int));
	show_binary((byte_point)&f, sizeof(float));
	return 0;
}
