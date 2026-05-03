#include "kernel.h"
#include "screen.h"
#include "keyboard.h"
#include "memory.h"

#define CMD_BUFFER_SIZE 256

static char cmd_buffer[CMD_BUFFER_SIZE];
static int cmd_pos = 0;

void shell_execute(const char* cmd) {
    if (strcmp(cmd, "help") == 0) {
        screen_write("Entrada OS Commands:\n", COLOR_CYAN);
        screen_write("  help    - Show this help\n", COLOR_WHITE);
        screen_write("  clear   - Clear screen\n", COLOR_WHITE);
        screen_write("  about   - About Entrada OS\n", COLOR_WHITE);
        screen_write("  meminfo - Memory information\n", COLOR_WHITE);
    } else if (strcmp(cmd, "clear") == 0) {
        screen_clear();
    } else if (strcmp(cmd, "about") == 0) {
        screen_write("Entrada OS v1.0\n", COLOR_GREEN);
        screen_write("A minimal 32-bit operating system\n", COLOR_WHITE);
        screen_write("Features: GDT, IDT, Memory, Keyboard, Timer\n", COLOR_WHITE);
    } else if (strcmp(cmd, "meminfo") == 0) {
        screen_write("Heap Start: 0x100000\n", COLOR_WHITE);
        screen_write("Heap Size: 1MB\n", COLOR_WHITE);
    } else if (cmd[0] != '\0') {
        screen_write("Unknown command: ", COLOR_RED);
        screen_write(cmd, COLOR_RED);
        screen_write("\n", COLOR_WHITE);
    }
}

void shell_main(void) {
    while (1) {
        screen_write("entrada> ", COLOR_CYAN);
        cmd_pos = 0;
        memset(cmd_buffer, 0, CMD_BUFFER_SIZE);
        
        while (1) {
            char c = keyboard_getchar();
            
            if (c == '\n') {
                screen_putchar('\n', COLOR_WHITE);
                cmd_buffer[cmd_pos] = '\0';
                shell_execute(cmd_buffer);
                break;
            } else if (c == '\b') {
                if (cmd_pos > 0) {
                    cmd_pos--;
                    cmd_buffer[cmd_pos] = '\0';
                    screen_putchar('\b', COLOR_WHITE);
                }
            } else if (c >= 32 && c <= 126 && cmd_pos < CMD_BUFFER_SIZE - 1) {
                cmd_buffer[cmd_pos++] = c;
                screen_putchar(c, COLOR_WHITE);
            }
        }
    }
}
