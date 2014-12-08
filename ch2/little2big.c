#include <stdio.h>
#define MASK 0xFF

int main()
{
	int little = 0;
	scanf("%d", &little);
	
	int big = 0;

	
	int i;
	for(i = 0; i < 4; i++){
		
		big |= (MASK & (little >> i * 8)) << (24 - i*8);
	}

	printf("little endian = %08x\nbig endian = %08x\n", little, big);

	return 0;	
}
