#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main()
{
	struct hostent *host = gethostbyname("www.google.com");
	if(NULL != host){
		printf("host name:%s\n", host->h_name);
		
		char **pp;
		for(pp = host->h_aliases; *pp != NULL; pp++)
			printf("alias:%s\n", *pp);

	   struct in_addr addr;
		for(pp = host->h_addr_list; *pp != NULL; pp++){	
			addr.s_addr = *((unsigned int *)*pp);
			printf("address:%s\n", inet_ntoa(addr));
		}
	}

	return 0;
}
