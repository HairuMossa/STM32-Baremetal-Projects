#include "stm32F4xx.h"

void USART2_init(void); 
void USART2_write(int ch); 
void delayMs(int n);

#define GPIOAEN                     (1U<<0)
#define USART2EN                    (1U<<17)

int main (void) {
    USART2_init(); 

    while(1) { 
        USART2_write('Y');
        USART2_write('e');
        USART2_write('s');
        delayMs(100);
    }
}

void USART2_init (void) {
    RCC->AHB1ENR |= GPIOAEN; // Enable GPIOA clock 
    RCC->APB1ENR |= USART2EN; // Enable USART2 clock, APB1

    // Configure PA2 for USART2_TX
    GPIOA->AFR[0] &= ~(0xF << 8); // Clear existing settings
    GPIOA->AFR[0] |= (0b0111 << 8); // AF07 for USART2
    GPIOA->MODER &= ~(0x3 << 4); // Clear existing settings
    GPIOA->MODER |= (0b10 << 4); // Enable alternate function for PA2

    // Baud rate calculation (assuming 16MHz PCLK)
    USART2->BRR = 0x0683; // 9600 baud @ 16 MHz
    USART2->CR1 = (1U << 3); // Enable Tx, 8-bit data
    USART2->CR2 = 0x0000; // 1 stop bit
    USART2->CR3 = 0x0000; // No flow control 
    USART2->CR1 |= (1U << 13); // Enable USART2

}

void delayMs(int n) {
    for (volatile int val = n; val > 0; val--){
        for (volatile int i = 0; i < 2000; i++) {}; 
    }
}


void USART2_write (int ch) {
    while (!(USART2->SR & 0x0080)) {} 
    USART2->DR = (ch & 0xFF);
}