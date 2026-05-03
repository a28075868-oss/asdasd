#include "memory.h"
#include "kernel.h"

typedef struct block {
    uint32 size;
    uint8 used;
    struct block* next;
} block_t;

static block_t* heap_start = NULL;

void memory_init(void) {
    heap_start = (block_t*)HEAP_START;
    heap_start->size = HEAP_SIZE - sizeof(block_t);
    heap_start->used = 0;
    heap_start->next = NULL;
}

void* kmalloc(uint32 size) {
    if (size == 0) return NULL;
    
    // Выравнивание по 4 байта
    if (size % 4 != 0) {
        size += 4 - (size % 4);
    }
    
    block_t* current = heap_start;
    
    while (current != NULL) {
        if (!current->used && current->size >= size) {
            if (current->size > size + sizeof(block_t) + 16) {
                block_t* new_block = (block_t*)((uint32)current + sizeof(block_t) + size);
                new_block->size = current->size - size - sizeof(block_t);
                new_block->used = 0;
                new_block->next = current->next;
                
                current->size = size;
                current->next = new_block;
            }
            
            current->used = 1;
            return (void*)((uint32)current + sizeof(block_t));
        }
        current = current->next;
    }
    
    return NULL;
}

void kfree(void* ptr) {
    if (ptr == NULL) return;
    
    block_t* block = (block_t*)((uint32)ptr - sizeof(block_t));
    block->used = 0;
    
    // Merge with next block if free
    if (block->next != NULL && !block->next->used) {
        block->size += sizeof(block_t) + block->next->size;
        block->next = block->next->next;
    }
}
