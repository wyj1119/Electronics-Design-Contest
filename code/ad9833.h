/*
 * ad9833.h
 *
 *  Created on: 2023Äê8ÔÂ3ÈÕ
 *      Author: wyj1119
 */

#ifndef AD9833_H_
#define AD9833_H_


#ifndef __AD9833_H
#define __AD9833_H

#include "stdbool.h"
#include <ti/devices/msp432e4/driverlib/driverlib.h>
#define CS_0        MAP_GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_3 , 0)
#define CS_1        MAP_GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_3 , GPIO_PIN_3)

#define FSYNC_0     MAP_GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_0 , 0)
#define FSYNC_1     MAP_GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_0 , GPIO_PIN_0)

#define SCK_0       MAP_GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_1 , 0)
#define SCK_1       MAP_GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_1 , GPIO_PIN_1)

#define DAT_0       MAP_GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_2 , 0)
#define DAT_1       MAP_GPIOPinWrite(GPIO_PORTK_BASE, GPIO_PIN_2 , GPIO_PIN_2)
void AD9833_Init_GPIO(void);
void AD9833_Init(void);
void AD9833_Set_Amplitude(uint16_t Amp);
void AD9833_Transmit(uint16_t content);
void AD9833_Reset(void);
void AD9833_Set_Freq(uint32_t output_freq);
void AD9833_Set_Phase(uint16_t init_phase);
void AD9833_Set(void);
void AD9833_Default_Set(uint32_t output_freq);

#endif


#endif /* AD9833_H_ */
