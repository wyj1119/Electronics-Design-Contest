/*
 * my_usart.c
 *
 *  Created on: 2023年7月13日
 *      Author: wyj1119
 */
//只能初始化USART 0 1 2
#include "my_usart.h"
#include "delay.h"
static const uint32_t g_ui32UARTBase[3] =
{
    UART0_BASE, UART1_BASE, UART2_BASE
};

static const uint32_t g_ui32UARTPeriph[3] =
{
    SYSCTL_PERIPH_UART0, SYSCTL_PERIPH_UART1, SYSCTL_PERIPH_UART2
};

void UARTStdioConfig(uint32_t ui32PortNum, uint32_t ui32Baud, uint32_t ui32SrcClock)
{
    uint32_t g_ui32Base=0;
    //
    // Check the arguments.
    //
    ASSERT((ui32PortNum == 0) || (ui32PortNum == 1) ||
           (ui32PortNum == 2));
    //
    // Check to make sure the UART peripheral is present.
    //
    if(!MAP_SysCtlPeripheralPresent(g_ui32UARTPeriph[ui32PortNum]))
    {
        return;
    }

    //
    // Select the base address of the UART.
    //
    g_ui32Base = g_ui32UARTBase[ui32PortNum];

    //
    // Enable the UART peripheral for use.
    //
    MAP_SysCtlPeripheralEnable(g_ui32UARTPeriph[ui32PortNum]);

    //
    // Configure the UART for 115200, n, 8, 1
    //
    MAP_UARTConfigSetExpClk(g_ui32Base, ui32SrcClock, ui32Baud,
                            (UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_WLEN_8));

    //
    // Enable the UART operation.
    //
    MAP_UARTEnable(g_ui32Base);
    delay_ms(50);
}

void ConfigureUART0_debug(uint32_t systemClock)
{
    /* Enable the clock to GPIO port A and UART 0 */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    /* Configure the GPIO Port A for UART 0 */
    MAP_GPIOPinConfigure(GPIO_PA0_U0RX);
    MAP_GPIOPinConfigure(GPIO_PA1_U0TX);
    MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    /* Configure the UART for 115200 bps 8-N-1 format */
    UARTStdioConfig(0, 115200, systemClock);
}

void ConfigureUART1_screen(uint32_t systemClock)
{

    /* Enable the clock to GPIO port B and UART 1 */
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);

        /* Configure the GPIO Port B for UART 1 */
        MAP_GPIOPinConfigure(GPIO_PB0_U1RX);
        MAP_GPIOPinConfigure(GPIO_PB1_U1TX);
        MAP_GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
        UARTStdioConfig(1, 115200, systemClock);
        delay_ms(50);
}

void ConfigureUART7_screen(uint32_t systemClock)
{
    uint32_t g_ui32Base;
    /* Enable the clock to GPIO port B and UART 1 */
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART7);

        /* Configure the GPIO Port B for UART 1 */
        MAP_GPIOPinConfigure(GPIO_PC4_U7RX);
        MAP_GPIOPinConfigure(GPIO_PC5_U7TX);
        MAP_GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);

        MAP_IntMasterEnable();


        /* Configure the UART for 115200 bps 8-N-1 format */
       // Check to make sure the UART peripheral is present.
       //
       if(!MAP_SysCtlPeripheralPresent(SYSCTL_PERIPH_UART7))
       {
           return;
       }

       //
       // Select the base address of the UART.
       //
       g_ui32Base = UART7_BASE;

       //
       // Enable the UART peripheral for use.
       //
       MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART7);

       //
       // Configure the UART for 115200, n, 8, 1
       //
       MAP_UARTConfigSetExpClk(g_ui32Base, systemClock, 115200,
                               (UART_CONFIG_PAR_NONE | UART_CONFIG_STOP_ONE |
                                UART_CONFIG_WLEN_8));


       MAP_IntEnable(INT_UART7);
        MAP_UARTIntEnable(UART7_BASE, UART_INT_RX | UART_INT_RT);
       //
       // Enable the UART operation.
       //
       MAP_UARTEnable(g_ui32Base);
       delay_ms(50);
}
//============================DDS使用该引脚===================================
//void ConfigureUART2_bluetooth(uint32_t systemClock)
//{
//    /* Enable the clock to GPIO port A and UART 2 */
//        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
//        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
//
//        /* Configure the GPIO Port A for UART 2 */
//        MAP_GPIOPinConfigure(GPIO_PD4_U2RX);
//        MAP_GPIOPinConfigure(GPIO_PD5_U2TX);
//        MAP_GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_4 | GPIO_PIN_5);
//
//        /* Configure the UART for 115200 bps 8-N-1 format */
//        UARTStdioConfig(2, 115200, systemClock);
//}
//============================DDS使用该引脚===================================


void UART_Transmit_nums(uint32_t Base_UART,uint8_t *data,uint32_t length_data)
{
    uint32_t i = 0;
    for(i=0;i<length_data;i++)
    {
        UARTCharPut(Base_UART,data[i]);
    }
}

void USART_printf (uint32_t Base_UART,char *fmt, ...)
{
    static char buffer[256];
    va_list args;
    va_start(args,fmt);
    vsprintf(buffer,fmt,args);
    va_end(args);
    UART_Transmit_nums(Base_UART,(uint8_t *)buffer,strlen(buffer));
}

