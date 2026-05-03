#include "process.h"
#include "memory.h"
#include "kernel.h"

static process_t processes[MAX_PROCESSES];
static uint32 current_process = 0;
static uint32 next_pid = 1;

void process_init(void) {
    memset(processes, 0, sizeof(processes));
    
    processes[0].pid = 0;
    processes[0].state = PROCESS_RUNNING;
    strcpy(processes[0].name, "kernel");
}

uint32 process_create(void (*entry)(void), const char* name) {
    for (uint32 i = 1; i < MAX_PROCESSES; i++) {
        if (processes[i].state == PROCESS_TERMINATED || processes[i].pid == 0) {
            void* stack = kmalloc(4096);
            if (stack == NULL) return 0;
            
            processes[i].pid = next_pid++;
            processes[i].eip = (uint32)entry;
            processes[i].esp = (uint32)stack + 4096;
            processes[i].ebp = processes[i].esp;
            processes[i].state = PROCESS_READY;
            
            uint32 name_len = 0;
            while (name[name_len] && name_len < 31) name_len++;
            for (uint32 j = 0; j < name_len; j++) {
                processes[i].name[j] = name[j];
            }
            processes[i].name[name_len] = '\0';
            
            return processes[i].pid;
        }
    }
    return 0;
}

void process_schedule(void) {
    uint32 next = (current_process + 1) % MAX_PROCESSES;
    
    while (next != current_process) {
        if (processes[next].state == PROCESS_READY) {
            processes[current_process].state = PROCESS_READY;
            current_process = next;
            processes[current_process].state = PROCESS_RUNNING;
            return;
        }
        next = (next + 1) % MAX_PROCESSES;
    }
}

uint32 process_get_current_pid(void) {
    return processes[current_process].pid;
}
