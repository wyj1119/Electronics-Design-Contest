/*
 * measure_z.c
 *
 *  Created on: 2023��8��3��
 *      Author: wyj1119
 */
#include "measure_z.h"
#include "my_math.h"
#include "adc_fft.h"
#include "my_usart.h"
#include "stdlib.h"
#include <stdlib.h>
#include <time.h>
void get_C(uint16_t U1,
           uint16_t U2,
           float R,
           float f,
           MEASURE_Z_Structure *MEASURE_Z_Str,
           uint8_t printf_option)

{
    float Z,C,Xc;
    Z = ((float)U1/U2)*R;


    if(MEASURE_Z_Str->D<=0.04)
        Xc = Z;

    else
        Xc = Z*cosf( atanf(MEASURE_Z_Str->D) );


    C = 1.0f/(2*PI*f*Xc);
    C*=1e9;

    MEASURE_Z_Str->Z = Z;
    MEASURE_Z_Str->C = C;

    if(printf_option)
        USART_printf(UART0_BASE,"C = %fnF\r\n",C);
}

void get_D(float r1,float i1,float r2,float i2,MEASURE_Z_Structure *MEASURE_Z_Str,uint8_t printf_option)
{
    float angle;

    angle = atanf(r1/i1) - atanf(r2/i2);

    if(angle<0)
        angle = -angle;

    angle -= PI/2;
    if(angle<0)
           angle = -angle;

    MEASURE_Z_Str->D = tanf(angle);


    if(printf_option)
        USART_printf(UART0_BASE,"D = %f\r\n",MEASURE_Z_Str->D);
}

void Init_Switch_GPIO(void)
{
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
    while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOL)))
    {

    }
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTL_BASE, (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3));
    MAP_GPIOPinWrite(GPIO_PORTL_BASE, (GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3), 0);
}


uint8_t adc0_temp[BUFFER_SIZE]={0};
uint8_t adc1_temp[BUFFER_SIZE]={0};
uint8_t get_phase_res[BUFFER_SIZE]={0};
#define NUM_REMOVE 10
void get_Phase_C(uint16_t *adc0_buf,uint16_t *adc2_buf,MEASURE_Z_Structure *MEASURE_Z_Str)
{
    uint16_t i,average0,average1;
    uint32_t cnt=0;
    static uint16_t idx=0;
    float average=0;
    float sum=0;

    float D,phase;
    average_ui16_normal(adc0_buf,BUFFER_SIZE,&average0);
    average_ui16_normal(adc2_buf,BUFFER_SIZE,&average1);

    for(i=0;i<BUFFER_SIZE;i++)
    {
        if(adc0_buf[i]>average0)
            adc0_temp[i] = 1;
        else
            adc0_temp[i] = 0;

        if(adc2_buf[i]>average1)
            adc1_temp[i] = 1;
        else
            adc1_temp[i] = 0;

        get_phase_res[i] = adc0_temp[i]^adc1_temp[i];

        if(get_phase_res[i]==1)
            cnt++;

//        USART_printf(UART0_BASE,"%u\r\n",get_phase_res[i]);
    }

    phase = (float)cnt/BUFFER_SIZE*360.0f/2.048f;

    phase -= 90;

    if(phase<0)
        phase=-phase;

    phase = phase/180*PI;
    D = tanf(phase);

    MEASURE_Z_Str->save_D[idx++] = D;

    if(idx>=MEASURE_TIMES)
    {
        idx = 0;

        // 对数组进行快速排序
        quick_sort(MEASURE_Z_Str->save_D, 0, MEASURE_TIMES - 1);

        // 计算中间30个元素（第10个到第40个元素）的和
        sum = 0;
        for (i = NUM_REMOVE; i < MEASURE_TIMES - NUM_REMOVE; i++) {
            sum += MEASURE_Z_Str->save_D[i];
        }

        // 计算平均值并打印结果
        average = (float)sum / (MEASURE_TIMES - 2 * NUM_REMOVE);

        MEASURE_Z_Str->D = average;

//        if(MEASURE_Z_Str->D <=0.04)
//        {
//            MEASURE_Z_Str->D = MEASURE_Z_Str->C;
//            while(1)
//            {
//                MEASURE_Z_Str->D /= 2.0f;
//                if(MEASURE_Z_Str->D < 0.04)break;
//
//            }
//
//        }



        USART_printf(UART0_BASE,"phase = %f\r\n",phase/PI*180);
        USART_printf(UART0_BASE,"D = %f\r\n",D);
    }
}

void get_Phase_L(uint16_t *adc0_buf,uint16_t *adc2_buf,MEASURE_Z_Structure *MEASURE_Z_Str)
{
    uint16_t i,average0,average1;
    uint32_t cnt=0;
    static uint16_t idx=0;
    float average=0;
    float sum=0;

    float Q,phase;
    average_ui16_normal(adc0_buf,BUFFER_SIZE,&average0);
    average_ui16_normal(adc2_buf,BUFFER_SIZE,&average1);

    for(i=0;i<BUFFER_SIZE;i++)
    {
        if(adc0_buf[i]>average0)
            adc0_temp[i] = 1;
        else
            adc0_temp[i] = 0;

        if(adc2_buf[i]>average1)
            adc1_temp[i] = 1;
        else
            adc1_temp[i] = 0;

        get_phase_res[i] = adc0_temp[i]^adc1_temp[i];

        if(get_phase_res[i]==1)
            cnt++;

    }

    phase = (float)cnt/BUFFER_SIZE*360.0f/2.048f;

    phase -= 90;

    if(phase<0)
        phase=-phase;

    phase = phase/180*PI;

    Q = 1.0f / tanf(phase);

    MEASURE_Z_Str->save_Q[idx++] = Q;

    if(idx>=MEASURE_TIMES)
    {
        idx = 0;

        // 对数组进行快速排序
        quick_sort(MEASURE_Z_Str->save_Q, 0, MEASURE_TIMES - 1);

        // 计算中间30个元素（第10个到第40个元素）的和
        sum = 0;
        for (i = NUM_REMOVE; i < MEASURE_TIMES - NUM_REMOVE; i++) {
            sum += MEASURE_Z_Str->save_Q[i];
        }

        // 计算平均值并打印结果
        average = (float)sum / (MEASURE_TIMES - 2 * NUM_REMOVE);

        MEASURE_Z_Str->Q = average;

        USART_printf(UART0_BASE,"phase = %f\r\n",phase/PI*180.0f);
        USART_printf(UART0_BASE,"Q = %f\r\n",Q);
    }
}

void get_L(uint16_t U1,
           uint16_t U2,
           float R,
           float f,
           MEASURE_Z_Structure *MEASURE_Z_Str,
           uint8_t printf_option)

{
    float Z,L,Xl;
    Z = ((float)U1/U2)*R;

    Xl = Z*cosf( atanf(MEASURE_Z_Str->Q) );
    L = Xl / (2*PI*f);

    L*=1e6;
    MEASURE_Z_Str->Z = Z;
    MEASURE_Z_Str->L = L;


    if(printf_option)
        USART_printf(UART0_BASE,"L = %fuH\r\n",L);
}


