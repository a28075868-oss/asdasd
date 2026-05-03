#include "kernel.h"
#include "idt.h"
#include "screen.h"

static uint32 tick = 0;

static void timer_callback(registers_t* regs) {
    tick++;
}

void timer_init(uint32 frequency) {
    register_interrupt_handler(32, timer_callback);
    
    uint32 divisor = 1193180 / frequency;
    
    outb(0x43, 0x36);
    
    uint8 l = (uint8)(divisor & 0xFF);
    uint8 h = (uint8)((divisor >> 8) & 0xFF);
    
    outb(0x40, l);
    outb(0x40, h);
}

uint32 timer_get_tick(void) {
    return tick;
}
