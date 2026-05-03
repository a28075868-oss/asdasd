#include "screen.h"
#include "kernel.h"

static uint16* vga_buffer = (uint16*)VGA_MEMORY;
static uint8 cursor_x = 0;
static uint8 cursor_y = 0;

void screen_init(void) {
    screen_clear();
    screen_set_cursor(0, 0);
}

void screen_clear(void) {
    uint16 blank = (COLOR_BLACK << 12) | (COLOR_WHITE << 8) | ' ';
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga_buffer[i] = blank;
    }
    cursor_x = 0;
    cursor_y = 0;
    screen_set_cursor(0, 0);
}

void screen_putchar(char c, uint8 color) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c == '\r') {
        cursor_x = 0;
    } else if (c == '\t') {
        uint8 spaces = 4 - (cursor_x % 4);
        for (uint8 i = 0; i < spaces; i++) {
            if (cursor_x < VGA_WIDTH) {
                vga_buffer[cursor_y * VGA_WIDTH + cursor_x] = (COLOR_BLACK << 12) | (color << 8) | ' ';
                cursor_x++;
            }
        }
    } else if (c == '\b') {
        if (cursor_x > 0) {
            cursor_x--;
            vga_buffer[cursor_y * VGA_WIDTH + cursor_x] = (COLOR_BLACK << 12) | (color << 8) | ' ';
        }
    } else if (c >= 32 && c <= 126) {
        vga_buffer[cursor_y * VGA_WIDTH + cursor_x] = (COLOR_BLACK << 12) | (color << 8) | c;
        cursor_x++;
    }
    
    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
    
    while (cursor_y >= VGA_HEIGHT) {
        screen_scroll();
        cursor_y--;
    }
    
    screen_set_cursor(cursor_x, cursor_y);
}

void screen_write(const char* str, uint8 color) {
    while (*str) {
        screen_putchar(*str++, color);
    }
}

void screen_scroll(void) {
    uint16 blank = (COLOR_BLACK << 12) | (COLOR_WHITE << 8) | ' ';
    
    for (int i = 0; i < (VGA_HEIGHT - 1) * VGA_WIDTH; i++) {
        vga_buffer[i] = vga_buffer[i + VGA_WIDTH];
    }
    
    for (int i = (VGA_HEIGHT - 1) * VGA_WIDTH; i < VGA_HEIGHT * VGA_WIDTH; i++) {
        vga_buffer[i] = blank;
    }
    
    cursor_y = VGA_HEIGHT - 1;
}

void screen_set_cursor(uint8 x, uint8 y) {
    uint16 pos = y * VGA_WIDTH + x;
    
    // Устанавливаем позицию курсора
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8)((pos >> 8) & 0xFF));
    
    // Включаем курсор (если он был отключен)
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | 0x0E);  // Начало курсора
    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | 0x0F);  // Конец курсора
}
