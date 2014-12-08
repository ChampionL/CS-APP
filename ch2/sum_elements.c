#include <stdio.h>

float sum_elements(float a[], unsigned int length)
{
	float sum = 0.0;
	
	int i;
	for(i = 0; i < length-1; i++)
		sum += a[i];

	return sum;
}

int main()
{
	float s[] = {1,2,3,4};

	float result = sum_elements(s, 4);

	printf("result of sum is %lf\n", result);

	result = sum_elements(s, 0);

	printf("result of sum is %lf\n", result);
}
