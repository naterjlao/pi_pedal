#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main() {
	int memFd = shm_open("example_memory", O_RDWR, 0);

	if (memFd == -1) {
		perror("CHILD: Can't open file\n");
		return 1;
	}

	char *buffer = mmap(NULL, sizeof(char) * 10, PROT_READ | PROT_WRITE, MAP_SHARED, memFd, 0);
	if (buffer == NULL) {
		perror("CHILD: Can't map\n");
		return -1;
	}

	printf("CHILD: writing message into shared memory\n");
	memcpy(buffer, "message\0", sizeof(char)*10);

	return 0;

}
