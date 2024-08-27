/*
 * tim_counter.c
 *
 *  Created on: 2023Äê7ÔÂ13ÈÕ
 *      Author: wyj1119
 */

#include "tim_counter.h"
//TIM3 PJ1
void Init_counter(uint32_t count)
{
    /* Enable the clock to the GPIO Port J and wait for it to be ready */
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
        while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ)))
        {
        }

        /* Configure the GPIO PJ0-PJ1 as input */
        MAP_GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_1);
        GPIOJ->PUR = GPIO_PIN_1;

        /* Enable the clock to the GPIO Port A and wait for it to be ready */
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
        while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA)))
        {
        }

        /* Configure the GPIO PA7 as Timer-3 CCP1 pin */
        MAP_GPIOPinConfigure(GPIO_PA7_T3CCP1);
        MAP_GPIOPinTypeTimer(GPIO_PORTA_BASE, GPIO_PIN_7);

        /* Enable the Timer-3 in 16-bit Edge Count mode */
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
        while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER3)))
        {
        }

        /* Configure the Timer-3B in Edge Count Mode. Load the internal counter to
         * count from 5 to 0, When the counter reaches 0, an interrupt is
         * generated */
        MAP_TimerConfigure(TIMER3_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_CAP_COUNT);

        MAP_TimerControlEvent(TIMER3_BASE, TIMER_B, TIMER_EVENT_POS_EDGE);

        MAP_TimerLoadSet(TIMER3_BASE, TIMER_B, count);

        MAP_TimerMatchSet(TIMER3_BASE, TIMER_B, 0);

        MAP_TimerIntEnable(TIMER3_BASE, TIMER_CAPB_MATCH);

        MAP_TimerEnable(TIMER3_BASE, TIMER_B);

        /* Enable the timer interrupt */
        MAP_IntEnable(INT_TIMER3B);
}

void Init_Tim2_int(uint32_t cnt)
{
    /* Enable the Timer-0 in 16-bit periodic mode with interrupt generated
         * every 0.1 sec */
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
        while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER2)))
        {
        }
        MAP_TimerConfigure(TIMER2_BASE, TIMER_CFG_A_PERIODIC);
        MAP_TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
        /* Since the 16-bit timer can count only 65536 value, we use the pre
         * scaler of 256 to divide down the count rate by 256. Thus the actual
         * count load is 120e6/256 = 468750. Now when to count at 0.1 sec the
         * load value in the timer would be 468750 * 0.1 = 46875 = 0xB71B. */
//        MAP_TimerPrescaleSet(TIMER2_BASE, TIMER_B, 255);
        MAP_TimerLoadSet(TIMER2_BASE, TIMER_A, cnt);
        /* Enable Timer Interrupt */
        MAP_IntEnable(INT_TIMER2A);
        /* Enable the timer count */
        MAP_TimerEnable(TIMER2_BASE, TIMER_A);
}


//uint32_t get_cnt_and_reset(void)
//{
//
//}
