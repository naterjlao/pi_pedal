#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int pid;
	pid = fork();
	printf("pid: %d\n",pid);

	if (!pid) {
		printf("I am the child\n");
		execlp("ls","ls",NULL);
	} else {
		printf("I am the parent\n");
		wait(NULL); // wait for all child processes
		printf("Child is done\n");
	}

	return 0;
}
