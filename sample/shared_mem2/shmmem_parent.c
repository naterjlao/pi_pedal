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
		//Expand the file to 1 character
		ftruncate(memFd, sizeof(char) * 2);
	}

	int pid = fork();

	//Child process
	if (pid == 0) {
		printf("Running Child...\n");
		execlp("./child.x", "./child.x",(char *)NULL);
	} else {
		char *buffer = mmap(NULL,sizeof(char)*2, PROT_READ, MAP_SHARED, memFd,0);
//		buffer[1] = '\0';
		char current_state = 0;
		while(waitpid(pid,NULL,WNOHANG) == 0) {
			if (current_state != *buffer) {
				current_state = *buffer;
				printf("%d\n",(int) current_state);
			}
		}

		memFd =	shm_unlink("example_memory");
		if (memFd == 0) {
			printf("memory unlinked\n");
		}
	}

	return 0;
}
