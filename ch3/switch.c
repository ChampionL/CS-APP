#include <stdio.h>

int switch2asm(int x)
{
	int result =1;
	switch(x){
		case 1:
			result = x * 12;
			break;
		case 2: 
		case 3: 
		case 4: 
		case 5: 
			result = x * 14;
			break;
		default:
			result = 10;
	}

	return result;
}
