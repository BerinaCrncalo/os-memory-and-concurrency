# os-memory-and-concurrency 
Berina Crnčalo & Ahmed Hasković
Project regarding memory and concurrency.

UNDERSTANDING OF MMAP AND MUNMAP SYSTEM CALLS:
The mmap system call establishes memory mappings between a process's virtual address space and objects in the system, such as files, devices, or anonymous memory, while munmap removes these mappings and deallocates the associated memory regions. mmap creates mappings by updating the page table to track virtual-to-physical memory or file locations. munmap removes specified mappings and deallocates associated resources, facilitating efficient memory management in Unix-like systems.

Explore how to use mmap to obtain pages of memory from the OS, and allocate chunks from these pages dynamically when requested:

To employ mmap for acquiring pages of memory from the OS and dynamically allocating chunks, first allocate a large memory region using mmap, serving as a memory pool. Subsequently, when a smaller memory chunk is required, subdivide this pool dynamically, possibly employing a free list or bitmap to manage available blocks. Allocate requested chunks from these subdivisions, ensuring efficient tracking of sizes and positions. Upon completion of use, deallocate chunks to avoid memory leaks. Finally, when the program concludes or memory becomes unnecessary, deallocate the entire memory region with munmap, returning memory resources to the OS. This systematic approach provides a flexible means of dynamic memory allocation, essential for efficient memory management.

Familiarization with the various arguments to the mmap system call:

The mmap system call in Unix-like systems accepts crucial arguments for defining memory mappings. These include addr for the starting address, length for the size, prot for memory protection, flags for behavior control, fd for file descriptor if backed by a file, and offset for file mapping start point. Understanding and configuring these parameters are vital for effective memory management, enabling tailored solutions such as memory-mapped files, shared memory, or dynamic memory allocation.