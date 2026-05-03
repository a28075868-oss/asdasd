// Entrada OS Kernel

#include "kernel.h"
#include "screen.h"
#include "keyboard.h"
#include "memory.h"
#include "process.h"
#include "syscall.h"

void kernel_main(void) {
    screen_clear();
    screen_write("Entrada OS v1.0\n", COLOR_GREEN);
    screen_write("Initializing kernel...\n", COLOR_WHITE);
    
    // Initialize subsystems
    gdt_init();
    idt_init();
    memory_init();
    keyboard_init();
    timer_init(50);
    process_init();
    syscall_init();
    
    // Включаем прерывания
    asm volatile("sti");
    
    screen_write("Kernel initialized successfully\n", COLOR_GREEN);
    screen_write("Type 'help' for commands\n\n", COLOR_CYAN);
    
    // Start shell
    shell_main();
    
    // Should never reach here
    while(1) {
        asm volatile("hlt");
    }
}
