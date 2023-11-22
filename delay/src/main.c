#include "delay.h"




int main(void) {
    // Initialize the timer
    timer_init();

    // Enable clock for GPIOD, which is connected to the AHB1 bus
    RCC->AHB1ENR |= 1U << 3; // Enable GPIOD clock (bit 3)

    // Configure PD13 as output
    GPIOD->MODER &= ~(1u<<27); // Clear the bit field for pin 13
    GPIOD->MODER |= (1U << (13 * 2));  // Set pin 13 to output mode

    // Main loop
    while (1) {
       
        GPIOD->BSRR = (1U << 13); // Turn on LED
        delay_ms(1000);

        GPIOD->BSRR = (1U << 29); // Turn off LED
        delay_ms(1000); // 1 second delay
    }
}
