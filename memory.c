#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

#define PAGE_SIZE 4096 // Size of a memory page

int main() {
    printf("Press Enter to continue...\n");
    getchar(); // Wait for user input
    
    // Memory mapping
    void *ptr = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    printf("Memory mapped successfully...\n");

    // Writing data into memory-mapped page
    char *data = "Hello, Memory Mapped Page!";
    memcpy(ptr, data, strlen(data));

    printf("Data written into memory mapped page: %s\n", (char *)ptr);

    // Pausing indefinitely
    while (1) {
        sleep(1); // Sleep for 1 second
    }

    // Unmapping memory
    if (munmap(ptr, PAGE_SIZE) == -1) {
        perror("munmap");
        return 1;
    }

    return 0;
}
