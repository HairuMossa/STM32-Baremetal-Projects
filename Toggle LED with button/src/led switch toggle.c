#include "stm32f407xx.h"

// LED is connected to GPIOD pin 13
// button is connected to GIPOA pin 0


void delayMs(int n);

int main(void) {
    // Enable clocks for GPIOD and GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; // Enable GPIOD clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; // Enable GPIOA clock

    // Configure GPIOD pin 13 as output
    GPIOD->MODER &= ~(3U << (13 * 2));    // Clear mode bits for pin 13
    GPIOD->MODER |= (1U << (13 * 2));     // Set pin 13 to output mode

    // Configure GPIOA pin 0 as input
    GPIOA->MODER &= ~(3U << (0 * 2));     // Clear mode bits for pin 0 (input mode is 00)

    while (1) {
        // Check if button is pressed 
        if ((GPIOA->IDR & 1) == 0) {
            // Toggle LED
            GPIOD->ODR ^= (1U << 13);  // Toggle pin 13

            // Simple debounce delay
            delayMs(200);  

            // Wait for button release to avoid multiple toggles
            while ((GPIOA->IDR & 1) == 0);
        }
    }
}

void delayMs(int n) {
    int i;
    for (; n > 0; n--)
        for (i = 0; i < 10000; i++) ; // Adjust the value to control delay time
}
