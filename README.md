# ft_malloc – Custom Dynamic Memory Allocator in C

## Overview

**ft_malloc** is a custom implementation of the standard C dynamic memory management functions: `malloc`, `free`, and `realloc`. This project provides fine-grained control over memory allocations by managing zones of memory using the `mmap` and `munmap` system calls.

The allocator organizes memory into `TINY`, `SMALL`, and `LARGE` zones to minimize system calls, optimize performance, and reduce fragmentation. It is designed to behave similarly to the glibc allocator while conforming to strict constraints regarding system usage and safety.

## Features

- Memory allocation with `malloc(size_t size)`
- Deallocation with `free(void *ptr)`
- Dynamic resizing with `realloc(void *ptr, size_t size)`
- Memory usage visualization with `show_alloc_mem()`
- Zone separation into `TINY`, `SMALL`, and `LARGE` types
- Thread-safe via `pthread_mutex_t`
- Memory alignment to 16-byte boundaries
- Uses `mmap` and `munmap` (no standard `malloc` internally)
- Includes a custom `libft` to replace libc functions internally

## Technologies and Concepts

- **Language:** C
- **System calls:** `mmap`, `munmap`, `getpagesize`, `pthread_mutex`
- **Memory alignment:** 16 bytes
- **Zones:**
  - TINY: up to 128 bytes
  - SMALL: up to 2048 bytes
  - LARGE: above 2048 bytes
- **Data structures:** Linked lists for zones and blocks
- **Thread safety:** One global mutex for safe concurrent use

## Project Structure

```bash
ft_malloc/
├── include/
│ └── malloc.h      # Global structs, macros, and function declarations
├── src/
│ ├── malloc.c      # Implementation of malloc()
│ ├── free.c        # Implementation of free()
│ ├── realloc.c     # Implementation of realloc()
│ ├── zone.c        # Zone management, block allocation
│ ├── utils.c       # Alignment, helper functions
│ ├── show_alloc.c  # Memory usage visualization
├── libft/          # Custom libft with Makefile
│ └── ...           # String/memory functions using ft_malloc
├── Makefile        # Builds the shared object and handles host platform
└── README.md       # Project documentation
```


## Building the Project

The allocator is compiled as a shared library named:

```bash
libft_malloc_$(HOSTTYPE).so
```

The `Makefile` automatically detects your system architecture and creates a symbolic link:

```bash
libft_malloc.so -> libft_malloc_< platform >.so
```

### Build Instructions

```bash
make
```

### Requirements

- Linux system (Debian recommended)
- GCC or Clang
- make

### Usage
To preload the allocator in an application:

```bash
LD_PRELOAD=./libft_malloc.so ./your_program
```
Or for debugging:

```bash
LD_PRELOAD=./libft_malloc.so ./tests/test_malloc
```

## Functions Provided

### malloc

```c
void *malloc(size_t size);
```

Allocates memory of the specified size, aligned to 16 bytes.

### free

```c
void free(void *ptr);
```
Marks a block as free or unmaps it if it was a LARGE allocation.

### realloc
```c
void *realloc(void *ptr, size_t size);
```
Resizes the given block if possible, otherwise allocates a new one and copies the content.

### show_alloc_mem
```c
void show_alloc_mem(void);
```
Prints the current memory state of TINY, SMALL, and LARGE zones with memory ranges and total allocated size.

#### Example Output
```yaml
TINY : 0x10000000
0x10000020 - 0x10000064 : 68 bytes
SMALL : 0x10010000
0x10010020 - 0x10010220 : 512 bytes
LARGE : 0x10100000
0x10100020 - 0x10112345 : 74565 bytes
Total : 75145 bytes
```

## Restrictions
- No use of the standard malloc, free, or realloc functions internally
- No third-party libraries
- Memory must be aligned
- Must preallocate zones with at least 100 blocks
- Zone sizes must be a multiple of the page size
- Clean code required; undefined behavior or crashes result in 0

## Author
This allocator was developed as part of a systems programming module and demonstrates low-level memory management skills using raw system calls and custom logic.
