#include <stdio.h>
#define MASK_FF 0xFF
#define MASK_00 0x00
#define MASK_01 0x01
typedef unsigned char * byte_pointer;

void mask_height_bit(byte_pointer start, int n)
{
	int i;
	for(i = 3; i > 0; i--){
		start[i] |= MASK_FF;
	}
}

void complement_least(byte_pointer start)
{
	start[0] = ~start[0];
}

void reset_least(byte_pointer start)
{
	start[0] &= MASK_00;
}

/* bit set */
int bis(int n, int m)
{
	int result = n | MASK_01 << m;
	return result;
}

/* bit clear */
int bic(int n, int m)
{
	int result = n & ~(MASK_01 << m);
	return result;
}
int main()
{
	int x = 0x98FDECBA;

	int temp = x;	
	mask_height_bit((byte_pointer)&temp, sizeof(x));
	printf("reset all bit without least:%x\n", temp);

	int temp1 = x;
	complement_least((byte_pointer)&temp1);
	printf("complement least without other:%x\n", temp1);

	int temp2 = x;
	reset_least((byte_pointer)&temp2);
	printf("reset least bit without other:%x\n", temp2);

	int temp3 = bis(0x0000000, 31);
	printf("0 after bis operator:%08x\n", temp3);

	
	int temp4 = bic(0x80000000, 31);
	printf("0 after bic operator:%08x\n", temp4);
	return 0;
}
