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
	
	int shm_fd;
	void *ptr;
	
	shm_fd = shm_open(name, O_RDONLY, 0666);
	ftruncate(shm_fd, SIZE);
	ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

	printf("Writer wrote \' %s \'", (char *)ptr);

	shm_unlink(name);
	return 0;
}
