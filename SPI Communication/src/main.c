#include "stm32f407xx.h"


// SPI communication is established between the MCU and the Accelerometer
// from the STM32F407VG discovery datasheet the SDA and SCL connections are as follows
// PA5 - SPI1 SCK
// PA6 - SPI1 MISO
// PA7 - SPI1 MOSI
// PE3 - SPI CS
// PE0 - INT1 / DRDY
// PE1 - INT2


#define SPI1EN          (1U<<12)
#define GPIOAEN         (1U<<0)
#define GPIOEEN         (1U<<4)


int main(void){

    
    // enable the clock for the SPI1, from the block diaram, APB2 84 MHz
        
    RCC->APB2ENR |= SPI1EN;     // enable the clock for the SPI1    
    RCC->AHB1ENR |= GPIOAEN;    // enable clock for GPIOA 
    GPIOA->MODER &= 0xFFFF03FF; // Reset bits 10-15 to clear old values
    // set GPIOA as alternate function mode, shift 10 to bit 10
    GPIOA->MODER |= (0x2<<10); // PA5
    // or
    /*
    GPIOA->MODER |= (1U<<11);  
    GPIOA->MODER &= ~(1U<<10); 
    */ 

    GPIOA->MODER |= (0x2<<12); // PA6
    // or
    /*
    GPIOA->MODER |= (1U<<13);  
    GPIOA->MODER &= ~(1U<<12); 
    */
    
    GPIOA->MODER |= (0x2<<13); // PA7
    // or
    /*
    GPIOA->MODER |= (1U<<14);  
    GPIOA->MODER &= ~(1U<<13); 
    */

    GPIOA->OSPEEDR |= 0x0000FC00; // Set pin 5/6/7 to very high speed mode (0b11)
    // now choose the alternate mode to SPI1 ,  0101(0x5): AF5
    // choose AF5 for SPI1 in Alternate Function registers
    GPIOA->AFR[0] |= (0x5 << 20); // for pin 5
    GPIOA->AFR[0] |= (0x5 << 24); // for pin 6
    GPIOA->AFR[0] |= (0x5 << 28); // for pin 7
    // set pin modes as very high speed
    

    RCC->AHB1ENR |= GPIOEEN;    // enable clock for GPIOE 
    GPIOE->MODER &= 0xFFFFFF3F; // reset bits 6-7
    GPIOE->MODER |= (1U<<6); // set bits 6-7 to 0b01 (output)
    GPIOE->ODR |= (1 << 3); // the chip is selected ??

    // configure SPI
    // the default CPU clock(given in the datasheet) 16MHz system clock , same goes for APB1 since default prescaler is diveded by 1x

    // set baudrate to fPCLK/32 , i.e. 0b100
    SPI1->CR1 = (0x4 << 3); 
                                                                                    // try 8 bit mode as well
    // choose 8/16 bit mode 
    SPI1->CR1 |= (1 << 11); // 1 - 16-bit mode

     // motion sensor expects clk to be high and
    //  transmission happens on the falling edge
    // clock polarity - CPOL bit 1
    SPI1->CR1 |= (0 << 1); // clk goes 1 when idle

    // clock phase - CPHA bit 0
    SPI1->CR1 |= (0 << 0); // first clock transaction

    // software slave management - SSM bit 9
    SPI1->CR1 |= (1 << 9); // 1- ssm enabled
    // internal slave select - SSI bit 8
    SPI1->CR1 |= (1 << 8); // set ssi to 1

    // master config - MSTR bit 2
    SPI1->CR1 |= (1 << 2); // 1 - master mode

    // enable SPI - SPE bit 6
    SPI1->CR1 |= (1 << 6);

    int16_t rbuf[3];

    SPI1->CR1 = 0x31C; /* set the Baud rate, 8-bit data frame */ 
    SPI1->CR2 = 0;
    SPI1->CR1 |= 0x40; /* enable SPI1 module */
    GPIOA->BSRR = 0x00100000; /* assert slave select */ 
    SPI1->DR = data; /* write data */
    while (SPI1->SR & 0x80) {} /* wait for transmission done */ 
    GPIOA->BSRR = 0x00000010; /* deassert slave select */

    









    


    
    
    while(1){
        
    }
}               