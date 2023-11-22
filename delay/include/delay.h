#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f407xx.h"

void timer_init(void);
void delay_ms(uint32_t ms);

#endif
