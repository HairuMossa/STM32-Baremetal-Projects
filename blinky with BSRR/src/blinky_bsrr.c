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
        GPIOD->BSRR = (1U << 13); // Turn on LED at PD13
        delayMs(1000);
        // for (int i = 0; i < 3199; i++) ; // Delay loop

        GPIOD->BSRR = (1U << 29); // Turn off LED at PD13
        // for (int i = 0; i < 3199; i++) ; // Delay loop
        delayMs(1000);
    }
}

void delayMs(int n) {
    
    for (int val=n; val > 0; val--){
       for (int i = 0; i < 3195; i++){} // Delay loop
    }
        
}
