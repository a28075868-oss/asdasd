#include "idt.h"
#include "kernel.h"

static idt_entry_t idt_entries[IDT_ENTRIES];
static idt_ptr_t idt_ptr;
static isr_t interrupt_handlers[IDT_ENTRIES];

extern void idt_flush(uint32);
extern void isr0(void);
extern void isr1(void);
extern void irq0(void);
extern void irq1(void);

void idt_set_gate(uint8 num, uint32 base, uint16 sel, uint8 flags) {
    idt_entries[num].base_low = base & 0xFFFF;
    idt_entries[num].base_high = (base >> 16) & 0xFFFF;
    idt_entries[num].selector = sel;
    idt_entries[num].zero = 0;
    idt_entries[num].flags = flags;
}

void idt_init(void) {
    idt_ptr.limit = sizeof(idt_entry_t) * IDT_ENTRIES - 1;
    idt_ptr.base = (uint32)&idt_entries;
    
    memset(&idt_entries, 0, sizeof(idt_entry_t) * IDT_ENTRIES);
    memset(&interrupt_handlers, 0, sizeof(isr_t) * IDT_ENTRIES);
    
    // Remap PIC
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
    
    // Set IDT gates
    idt_set_gate(0, (uint32)isr0, 0x08, 0x8E);
    idt_set_gate(1, (uint32)isr1, 0x08, 0x8E);
    idt_set_gate(32, (uint32)irq0, 0x08, 0x8E);
    idt_set_gate(33, (uint32)irq1, 0x08, 0x8E);
    
    idt_flush((uint32)&idt_ptr);
    
    // Прерывания будут включены позже через sti
}

void register_interrupt_handler(uint8 n, isr_t handler) {
    interrupt_handlers[n] = handler;
}

void isr_handler(registers_t* regs) {
    if (interrupt_handlers[regs->int_no] != 0) {
        isr_t handler = interrupt_handlers[regs->int_no];
        handler(regs);
    }
}

void irq_handler(registers_t* regs) {
    if (regs->int_no >= 40) {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);
    
    if (interrupt_handlers[regs->int_no] != 0) {
        isr_t handler = interrupt_handlers[regs->int_no];
        handler(regs);
    }
}
