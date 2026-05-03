#include "keyboard.h"
#include "kernel.h"
#include "idt.h"

static const char scancode_to_ascii[] = {
    0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
    0, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
    0, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
    '*', 0, ' '
};

static char key_buffer[256];
static uint8 buffer_start = 0;
static uint8 buffer_end = 0;

void keyboard_init(void) {
    buffer_start = 0;
    buffer_end = 0;
    
    // Регистрируем обработчик прерывания клавиатуры (IRQ1 = INT 33)
    register_interrupt_handler(33, (isr_t)keyboard_handler);
}

void keyboard_handler(void) {
    uint8 scancode = inb(KEYBOARD_DATA_PORT);
    
    if (scancode & 0x80) {
        // Key release
        return;
    }
    
    if (scancode < sizeof(scancode_to_ascii)) {
        char c = scancode_to_ascii[scancode];
        if (c != 0) {
            key_buffer[buffer_end] = c;
            buffer_end = (buffer_end + 1) % 256;
        }
    }
}

char keyboard_getchar(void) {
    while (buffer_start == buffer_end) {
        asm volatile("hlt");
    }
    
    char c = key_buffer[buffer_start];
    buffer_start = (buffer_start + 1) % 256;
    return c;
}
