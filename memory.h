#ifndef MEMORY_H
#define MEMORY_H

#include "types.h"

#define HEAP_START 0x100000
#define HEAP_SIZE 0x100000

void memory_init(void);
void* kmalloc(uint32 size);
void kfree(void* ptr);

#endif
