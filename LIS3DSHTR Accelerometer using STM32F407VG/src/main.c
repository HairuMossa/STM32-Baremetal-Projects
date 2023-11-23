#include "stm32f407xx.h"

// SPI communication is established between the MCU and the Accelerometer
// from the STM32F407VG discovery datasheet the SDA and SCL connections are as follows
// SPI1_SCK   - PA5
// SPI1_MISO  - PA6
// SPI1_MOSI  - PA7
 


#define WHO_AM_I       00001111 // device slave address
#define OUT_T          00001100 // temperature output


// acceleration High and Low registers
#define OUT_X_L        00101000 
#define OUT_X_H        00101001
#define OUT_Y_L        00101010
#define OUT_Y_H        00101011
#define OUT_Z_L        00101100
#define OUT_Z_H        00101101