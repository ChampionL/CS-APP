#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char **argv)
{
	char *query_string = getenv("QUERY_STRING");
	char *op1 = strtok(query_string, "&");
	char *op2 = strtok(NULL, "&");
	fprintf(stdout, "Welecome to add.com: The Internet addition portal\r\n");
	fprintf(stdout, "<p>the answer is:15000 + 213 = 15213</p>\r\n");
	fprintf(stdout, "<p>Thanks for visiting!!</p>\r\n");
	return 0;
}
