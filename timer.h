#ifndef TIMER_H
#define TIMER_H

#include "types.h"

void timer_init(uint32 frequency);
uint32 timer_get_tick(void);

#endif
