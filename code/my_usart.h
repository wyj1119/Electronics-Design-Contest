/*
 * my_usart.h
 *
 *  Created on: 2023Äê7ÔÂ13ÈÕ
 *      Author: wyj1119
 */

#ifndef MY_USART_H_
#define MY_USART_H_
#include <ti/devices/msp432e4/driverlib/driverlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

void UARTStdioConfig(uint32_t ui32PortNum, uint32_t ui32Baud, uint32_t ui32SrcClock);
void ConfigureUART0_debug(uint32_t systemClock);
void ConfigureUART1_screen(uint32_t systemClock);
void ConfigureUART7_screen(uint32_t systemClock);
//void ConfigureUART2_bluetooth(uint32_t systemClock);
void UART_Transmit_nums(uint32_t Base_UART,uint8_t *data,uint32_t length_data);
void USART_printf (uint32_t Base_UART,char *fmt, ...);
#endif /* MY_USART_H_ */
