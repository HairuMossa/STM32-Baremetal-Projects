#include "delay.h"

void timer_init(void) {
    // Enable the clock for TIM2
    RCC->APB1ENR |= (1U<<0);

    // Configure the timer
    // depending on the cpu clock the following line of code will need some change
    TIM2->PSC = 16 - 1;  // Prescaler value (the default CPU clock(given in the datasheet) 16MHz system clock, this sets the timer clock to 1MHz)
    TIM2->ARR = 1000 - 1; // Auto-reload value (1000 ticks = 1 millisecond delay at 1MHz timer clock)

    // Enable the timer
    TIM2->CR1 |= (1U<<0);
}


void delay_ms(uint32_t ms) {
    for (uint32_t i = 0; i < ms; i++) {
        // Reset the counter
        TIM2->CNT = 0;

        // Wait until the counter reaches the auto-reload value
        while ((TIM2->SR & (1U<<0)) == 0);

        // Clear the update flag
        TIM2->SR &= ~(1U<<0);
    }
}




