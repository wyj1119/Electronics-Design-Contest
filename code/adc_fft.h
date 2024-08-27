/*
 * adc_fft.h
 *
 *  Created on: 2023��7��13��
 *      Author: wyj1119
 */

#ifndef ADC_FFT_H_
#define ADC_FFT_H_


#include <ti/devices/msp432e4/driverlib/driverlib.h>
#include "DSPLib.h"

#define BUFFER_SIZE 1024
#define PI 3.14159265
#define BIAS_IDX 10

typedef struct
{
    int16_t adc_fft_buffer[BUFFER_SIZE];
    uint16_t fft_mag_buf[BUFFER_SIZE/2];

    uint16_t max_val;
    uint32_t max_idx;

    uint16_t sec_val;
    uint32_t sec_idx;

    int16_t max_Real;
    int16_t max_Imag;

    uint16_t RMS;
}ADC_FFT_Structure;

void adc01_tim_config(uint32_t Fs);
void Init_adc0_dma(int16_t *adc_buffer_0);
void Init_adc1_dma(int16_t *adc_buffer_1);
void Init_adc2_dma(int16_t *adc_buffer_2);

void Init_fft(msp_fft_q15_params *params);
void set_Fs(uint32_t Fs,uint8_t start_adc);
void cal_fft(msp_fft_q15_params *params_fft_1024,int16_t *ADC_buffer,ADC_FFT_Structure *ADC_FFT_Str,uint8_t printf_option);

#endif /* ADC_FFT_H_ */
