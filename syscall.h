#ifndef SYSCALL_H
#define SYSCALL_H

#include "types.h"

#define SYSCALL_WRITE 1
#define SYSCALL_READ 2
#define SYSCALL_EXIT 3
#define SYSCALL_GETPID 4

void syscall_init(void);

#endif
