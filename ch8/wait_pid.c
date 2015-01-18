#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int status, i;
	pid_t pid;

	//create 3 process
	for(i = 0; i< 3; i++){
		if ((pid = fork()) == 0){
			exit(1);
		}
	}

	//parent waits for all its children to terminate
	while((pid = waitpid(-1, &status, 0)) > 0){
		if(WIFEXITED(status)){
			printf("child %d terminated normally with exit status = %d\n", pid, WEXITSTATUS(status));
		}
		else
			printf("child %d terminate abnormally\n", pid);
	}
	return 0;
}
