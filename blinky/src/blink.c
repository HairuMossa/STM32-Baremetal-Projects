#include "stm32f407xx.h"
void delayMs(int n); 

// The goal here is to toggle the built-in orange LED at pin PD13 

int main(void){

    // Enable clock for GPIOD, which is connected to the AHB1 bus
    RCC->AHB1ENR |= 1U << 3; // Enable GPIOD clock (bit 3)

    // Configure PD13 as output
    GPIOD->MODER &= ~(1u<<27); // Clear the bit field for pin 13
    GPIOD->MODER |= (1U << (13 * 2));  // Set pin 13 to output mode

    while(1) {
        GPIOD->ODR |= (1U << 13); // Turn on LED at PD13
        delayMs(5000);

        // GPIOD->ODR &= ~(1U << 13); // Turn off LED at PD13
        delayMs(5000);
    }
}

void delayMs(int n) {
    int i;
    for (; n > 0; n--)
        for (i = 0; i < 3195; i++) ; // Delay loop
}
