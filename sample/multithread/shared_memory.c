#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>


int main() {
	char* parent_message = "parents message";
	char* child_message = "childs message";

	void* shmem = mmap(NULL,512,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS, -1, 0);

	memcpy(shmem, parent_message, 16);

	int pid = fork();

	if (pid == 0) {
		printf("Child reads:%s\n", (char*) shmem);
		memcpy(shmem,child_message,sizeof(child_message));
		printf("Child wrote:%s\n", (char*) shmem);
	} else {
		printf("Parent reads:%s\n", (char*) shmem);
		sleep(1);
		printf("After 1 sec, parent reads: %s\n",(char*) shmem);
	}

	return 0;
}
