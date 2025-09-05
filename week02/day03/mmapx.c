// #define _XOPEN_SOURCE_EXTENDED 1
// #include<stdio.h>
// #include <sys/mman.h>

// // void *mmap(void *addr, size_t len, int prot, int flags, int fildes, off_t off);
// int
// main(int argc, char ** args)
// {
//     FILE* 
//     mmap();

//    return 0;
// }
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd = open("test.txt", O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1) {
        perror("fstat");
        exit(1);
    }

    char *addr = mmap(NULL, sb.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (addr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    printf("Before: %s\n", addr);
    strcpy(addr, "Hello mmap!\n");
    printf("After: %s\n", addr);

    if (msync(addr, sb.st_size, MS_SYNC) == -1) {
        perror("msync");
    }

    munmap(addr, sb.st_size);
    close(fd);

    return 0;
}
