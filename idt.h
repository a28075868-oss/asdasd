#ifndef IDT_H
#define IDT_H

#include "types.h"

#define IDT_ENTRIES 256

typedef struct {
    uint16 base_low;
    uint16 selector;
    uint8 zero;
    uint8 flags;
    uint16 base_high;
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16 limit;
    uint32 base;
} __attribute__((packed)) idt_ptr_t;

typedef struct {
    uint32 ds;
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32 int_no, err_code;
    uint32 eip, cs, eflags, useresp, ss;
} registers_t;

typedef void (*isr_t)(registers_t*);

void idt_init(void);
void idt_set_gate(uint8 num, uint32 base, uint16 sel, uint8 flags);
void register_interrupt_handler(uint8 n, isr_t handler);

#endif
