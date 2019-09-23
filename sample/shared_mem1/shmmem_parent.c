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
		//Expand the file to 10 characters
		ftruncate(memFd, sizeof(char) * 10);
	}


	int pid = fork();

	//Child process
	if (pid == 0) {
		printf("Running Child...\n");
		execlp("./child.x", "./child.x",(char *)NULL);
	} else {
		wait(NULL);
		char *buffer = mmap(NULL,sizeof(char)*10, PROT_READ, MAP_SHARED, memFd,0);
		printf("Child's message: %s\n",buffer);


		buffer = 0;
		memFd =	shm_unlink("example_memory");
		if (memFd == 0) {
			printf("memory unlinked\n");
		}
	}



	return 0;
}
