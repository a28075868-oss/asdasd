#include "syscall.h"
#include "idt.h"
#include "screen.h"
#include "process.h"

static void syscall_handler(registers_t* regs) {
    switch (regs->eax) {
        case SYSCALL_WRITE:
            screen_write((const char*)regs->ebx, COLOR_WHITE);
            break;
        case SYSCALL_READ:
            // TODO: implement read
            break;
        case SYSCALL_EXIT:
            // TODO: terminate process
            break;
        case SYSCALL_GETPID:
            regs->eax = process_get_current_pid();
            break;
    }
}

void syscall_init(void) {
    register_interrupt_handler(0x80, syscall_handler);
}
