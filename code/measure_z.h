/*
 * measure_z.h
 *
 *  Created on: 2023��8��3��
 *      Author: wyj1119
 */

#ifndef MEASURE_Z_H_
#define MEASURE_Z_H_



#include <ti/devices/msp432e4/driverlib/driverlib.h>
#define MEASURE_TIMES 50
typedef struct
{
    float Z;

    float C;
    float L;

    float D;
    float Q;

    float Phase_dif;
    float Phase_i;
    float U_dif;
    float U_i;
    uint8_t rec_cmd;

    float f_LC;

    float save_D[MEASURE_TIMES];
    float save_Q[MEASURE_TIMES];
}MEASURE_Z_Structure;



void Init_Switch_GPIO(void);
void get_C(uint16_t U1,
           uint16_t U2,
           float R,
           float f,
           MEASURE_Z_Structure *MEASURE_Z_Str,
           uint8_t printf_option);

void get_L(uint16_t U1,
           uint16_t U2,
           float R,
           float f,
           MEASURE_Z_Structure *MEASURE_Z_Str,
           uint8_t printf_option);

void get_D(float r1,float i1,float r2,float i2,MEASURE_Z_Structure *MEASURE_Z_Str,uint8_t printf_option);
void cal_Z_mag_and_Phase(MEASURE_Z_Structure *MEASURE_Z_Str,
                         int16_t *adc_buf1,
                         int16_t *adc_buf2,
                         uint32_t length,
                         uint8_t U_I_option,
                         uint8_t printf_option);
void get_Phase_C(uint16_t *adc0_buf,uint16_t *adc2_buf,MEASURE_Z_Structure *MEASURE_Z_Str);
void get_Phase_L(uint16_t *adc0_buf,uint16_t *adc2_buf,MEASURE_Z_Structure *MEASURE_Z_Str);

#define SWITCH_MEASURE_C (MAP_GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_2 , 0))
#define SWITCH_5K       (MAP_GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_1|GPIO_PIN_0, GPIO_PIN_1))
#define SWITCH_10K      (MAP_GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0|GPIO_PIN_1, 0))
#define SWITCH_100K     (MAP_GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0 , GPIO_PIN_0))

#define SWITCH_L        (MAP_GPIOPinWrite(GPIO_PORTL_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2 , GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2))

#endif /* MEASURE_Z_H_ */
