#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>


int main() {
	const int SIZE = 4096;
	const char *name = "OS";
	const char *message = "Hello";
	int shm_fd;
	void *ptr;
	
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, SIZE);
	ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);

	sprintf(ptr, "%s", message);
	printf("Writer wrote \' %s \'", message);
	return 0;
}
