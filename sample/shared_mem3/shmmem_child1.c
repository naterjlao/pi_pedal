#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


int main() {

	char counter;
	int memFd; 
	if ((memFd = shm_open("example_memory", O_RDWR, 0)) == -1) {
		perror("CHILD 1: Can't open file\n");
		return 1;
	}

	char *buffer; 
	if ((buffer = mmap(NULL, sizeof(char), PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0)) == NULL) {
		perror("CHILD 1: Can't map\n");
		return -1;
	}

	printf("CHILD 1: writing seconds into shared memory\n");
	counter = 0;
	while (counter < 10) {
		memcpy(buffer,&counter,sizeof(char));
		sleep(1);
		counter++;
	}	
	
	return 0;

}
