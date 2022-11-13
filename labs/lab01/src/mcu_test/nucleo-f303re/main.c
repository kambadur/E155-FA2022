/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*                        The Embedded Experts                        *
**********************************************************************
*                                                                    *
*       (c) 1995 - 2017 SEGGER Microcontroller GmbH & Co. KG         *
*                                                                    *
*       Internet: segger.com  Support: support_embos@segger.com      *
*                                                                    *
**********************************************************************

----------------------------------------------------------------------
File    : Main.c
Purpose : Generic SEGGER application start
--------  END-OF-HEADER  ---------------------------------------------
*/

//Target: Nucleo-F303RE
#include<stdio.h>
#include<stdint.h>

#define RCC_BASE_ADDRESS            0x40021000U
#define RCC_AHBENR_OFFSET           0x14U
#define GPIOA_BASE_ADDRESS          0x48000000U
#define GPIOx_MODEREG_OFFSET        0x0U
#define GPIOX_ODR_OFFSET            0x14U

int main(void)
{

uint32_t *const pRccAhbEnReg  = (uint32_t * const)(RCC_BASE_ADDRESS + RCC_AHBENR_OFFSET);
uint32_t *const pGpioAModeReg = (uint32_t * const)(GPIOA_BASE_ADDRESS + GPIOx_MODEREG_OFFSET);
uint32_t *const pGpioAOdReg   = (uint32_t * const)(GPIOA_BASE_ADDRESS + GPIOX_ODR_OFFSET); 

//Enable clock to GPIOA
*pRccAhbEnReg |= (1<<17);

//Set GPIOA pin5: port mode as Output (PA5- LED)
*pGpioAModeReg |= (1<<10);  //set bit 10
*pGpioAModeReg &= ~(1<<11); //clear bit 11

while(1) {

//Toggle PA5 LED
*pGpioAOdReg ^= (1<<5);  //toggle this bit
for(uint32_t i=0; i<405535; i++);

}

return 0;

}
