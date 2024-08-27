/*
 * tim_10k_1k_90d.c
 *
 *  Created on: 2023年8月4日
 *      Author: wyj1119
 */
#include "tim_10k_1k_90d.h"
void Init_Timer_PWM_10k_90_d(void)
{
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
        while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM)))
        {
        }

        MAP_GPIOPinConfigure(GPIO_PM2_T3CCP0);
        MAP_GPIOPinConfigure(GPIO_PM3_T3CCP1);


        MAP_GPIOPinTypeTimer(GPIO_PORTM_BASE, (GPIO_PIN_2 | GPIO_PIN_3));


        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);


        MAP_TimerConfigure(TIMER3_BASE, (TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PWM | TIMER_CFG_B_PWM));
        TimerPrescaleSet(TIMER3_BASE,TIMER_BOTH,0);
        MAP_TimerLoadSet(TIMER3_BASE, TIMER_BOTH, 11999);
        MAP_TimerMatchSet(TIMER3_BASE, TIMER_BOTH,5999);
        //PM2 , PM3



        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
        while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM)))
        {
        }
        MAP_GPIOPinConfigure(GPIO_PM0_T2CCP0);
        MAP_GPIOPinConfigure(GPIO_PM1_T2CCP1);
        MAP_GPIOPinTypeTimer(GPIO_PORTM_BASE, (GPIO_PIN_0 | GPIO_PIN_1));
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);

        MAP_TimerConfigure(TIMER2_BASE, (TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PWM | TIMER_CFG_B_PWM));
        TimerPrescaleSet(TIMER2_BASE,TIMER_BOTH,0);
        MAP_TimerLoadSet(TIMER2_BASE, TIMER_BOTH, 11999);
        MAP_TimerMatchSet(TIMER2_BASE, TIMER_BOTH,5999);
        //PM0


        MAP_TimerEnable(TIMER3_BASE, TIMER_BOTH);//0度
        delay_us(23);
        Delay_ns(8);
        MAP_TimerEnable(TIMER2_BASE, TIMER_BOTH);//90度

}

void Init_Timer_PWM_1k_90_d(void)
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
       while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM)))
       {
       }

       MAP_GPIOPinConfigure(GPIO_PM2_T3CCP0);
       MAP_GPIOPinConfigure(GPIO_PM3_T3CCP1);


       MAP_GPIOPinTypeTimer(GPIO_PORTM_BASE, (GPIO_PIN_2 | GPIO_PIN_3));


       MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);


       MAP_TimerConfigure(TIMER3_BASE, (TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PWM | TIMER_CFG_B_PWM));
       TimerPrescaleSet(TIMER3_BASE,TIMER_BOTH,1);
       MAP_TimerLoadSet(TIMER3_BASE, TIMER_BOTH, 54466);
       MAP_TimerMatchSet(TIMER3_BASE, TIMER_BOTH,60066);
       //PM2 , PM3



       MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
       while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOM)))
       {
       }
       MAP_GPIOPinConfigure(GPIO_PM0_T2CCP0);
       MAP_GPIOPinConfigure(GPIO_PM1_T2CCP1);
       MAP_GPIOPinTypeTimer(GPIO_PORTM_BASE, (GPIO_PIN_0 | GPIO_PIN_1));
       MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);

       MAP_TimerConfigure(TIMER2_BASE, (TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PWM | TIMER_CFG_B_PWM));
       TimerPrescaleSet(TIMER2_BASE,TIMER_BOTH,1);
       MAP_TimerLoadSet(TIMER2_BASE, TIMER_BOTH, 54466);
       MAP_TimerMatchSet(TIMER2_BASE, TIMER_BOTH,60066);
       //PM0


       MAP_TimerEnable(TIMER3_BASE, TIMER_BOTH);//0度
       delay_us(247);
       Delay_ns(18);
       MAP_TimerEnable(TIMER2_BASE, TIMER_BOTH);//90度
}



