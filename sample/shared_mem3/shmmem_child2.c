#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

/*XXX child2 edits the char at position 1*/

int main() {

	char counter;
	int memFd; 
	if ((memFd = shm_open("example_memory", O_RDWR, 0)) == -1) {
		perror("CHILD 2: Can't open file\n");
		return 1;
	}

	char *buffer; 
	if ((buffer = mmap(NULL, sizeof(char), PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 1)) == NULL) {
		perror("CHILD 2: Can't map\n");
		return -1;
	}

	printf("CHILD 2: writing seconds into shared memory\n");
	counter = 10;
	while (counter < 20) {
		memcpy(buffer,&counter,sizeof(char));
		usleep(300*1000);
		counter++;
	}	

	return 0;
}
