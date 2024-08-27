/*
 * my_math.h
 *
 *  Created on: 2023��7��13��
 *      Author: wyj1119
 */

#ifndef MY_MATH_H_
#define MY_MATH_H_

#include <ti/devices/msp432e4/driverlib/driverlib.h>
#include "DSPLib.h"
#include <math.h>

void cplx_abs_q15(int16_t *input,uint16_t *output,uint32_t length_cplx);
void cplx_abs_square_q15(int16_t *input,uint32_t *output,uint32_t length_cplx);
void max_ui16_normal(uint16_t *input,
              uint32_t length,
              uint16_t *max_val,
              uint32_t *max_idx);
void max_ui16_normal_st_end(uint16_t *input,
              uint32_t st,
              uint32_t end,
              uint16_t *max_val,
              uint32_t *max_idx);
void average_ui16_normal(uint16_t *input,
                         uint32_t length,
                         uint16_t *average_val);
void hanning_window(int16_t *input,int16_t *output,uint32_t length);
void get_RMS(int16_t *input,int16_t average_val,uint16_t *RMS,uint32_t length);
void Init_LOW_PASS(msp_biquad_cascade_df1_q15_params *Filter_Params);
void smooth(float *data,uint32_t length,float *output_data,uint32_t WINDOW_LENGTH);
void quick_sort(float *arr, int left, int right);
#endif /* MY_MATH_H_ */
