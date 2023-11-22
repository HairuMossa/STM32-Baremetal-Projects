#include "stm32f407xx.h"

// from the STM32F407VG discovery datasheet the SDA and SCL connections are as follows
// SDA - PA7
// SCL - PA5


#define WHO_AM_I       00001111
#define OUT_T          00001100 // temperature output


// acceleration High and Low registers
#define OUT_X_L        00101000 
#define OUT_X_H        00101001
#define OUT_Y_L        00101010
#define OUT_Y_H        00101011
#define OUT_Z_L        00101100
#define OUT_Z_H        00101101