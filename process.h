#ifndef PROCESS_H
#define PROCESS_H

#include "types.h"

#define MAX_PROCESSES 32

typedef enum {
    PROCESS_READY,
    PROCESS_RUNNING,
    PROCESS_BLOCKED,
    PROCESS_TERMINATED
} process_state_t;

typedef struct {
    uint32 pid;
    uint32 esp;
    uint32 ebp;
    uint32 eip;
    process_state_t state;
    char name[32];
} process_t;

void process_init(void);
uint32 process_create(void (*entry)(void), const char* name);
void process_schedule(void);
uint32 process_get_current_pid(void);

#endif
