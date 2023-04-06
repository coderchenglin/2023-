#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

#define SHM_NAME "/my_shm"
#define SHM_SIZE 4096

int main()
{
    int fd;
    char *shm_addr;

    fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    if (ftruncate(fd, SHM_SIZE) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    shm_addr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (shm_addr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    close(fd);

    strcpy(shm_addr, "Hello, world!\n");

    printf("Message sent: %s", shm_addr);

    if (munmap(shm_addr, SHM_SIZE) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    if (shm_unlink(SHM_NAME) == -1) {
        perror("shm_unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}

