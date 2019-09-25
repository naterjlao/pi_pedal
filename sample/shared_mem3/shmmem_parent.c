#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
	int memFd = shm_open("example_memory", O_CREAT | O_RDWR, S_IRWXU);
	if (memFd == -1) {
		perror("cant open");
		return 1;
	} else {
		//Expand the file to 2 bytes
		ftruncate(memFd, sizeof(char) * 2);
	}

	int pid1 = fork();
	//Child process
	if (pid1 == 0) {
		printf("Running Child 1...\n");
		execlp("./child1.x", "./child1.x",(char *)NULL);
	} 

	int pid2 = fork();
	//Child process
	if (pid2 == 0) {
		printf("Running Child 2...\n");
		execlp("./child2.x", "./child2.x",(char *)NULL);
	} 

	char *buffer = mmap(NULL,sizeof(char)*2, PROT_READ, MAP_SHARED, memFd,0);
	char current_state1 = -1;
	char current_state2 = -1;
	while(waitpid(pid1,NULL,WNOHANG) == 0 && waitpid(pid2,NULL,WNOHANG) == 0) {
		if (current_state1 != buffer[0] || current_state2 != buffer[1]) {
			current_state1 = buffer[0];
			current_state2 = buffer[1];
			printf("%d %d\n",(int) current_state1, (int) current_state2);
		}
	}

	memFd =	shm_unlink("example_memory");
	if (memFd == 0) {
		printf("memory unlinked\n");
	}

	return 0;
}
