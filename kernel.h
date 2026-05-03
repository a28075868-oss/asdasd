#ifndef KERNEL_H
#define KERNEL_H

#include "types.h"

#define NULL ((void*)0)

// Port I/O
static inline void outb(uint16 port, uint8 val) {
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8 inb(uint16 port) {
    uint8 ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void io_wait(void) {
    outb(0x80, 0);
}

// String functions
int strlen(const char* str);
int strcmp(const char* s1, const char* s2);
void strcpy(char* dest, const char* src);
void memset(void* dest, uint8 val, uint32 len);
void memcpy(void* dest, const void* src, uint32 len);

// Kernel functions
void kernel_main(void);
void kernel_panic(const char* message);

// Subsystem initialization
void gdt_init(void);
void idt_init(void);
void timer_init(uint32 frequency);

#endif
