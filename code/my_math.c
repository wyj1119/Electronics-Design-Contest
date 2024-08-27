/*
 * my_math.c
 *
 *  Created on: 2023��7��13��
 *      Author: wyj1119
 */
#include "my_math.h"
#include "adc_fft.h"


void cplx_abs_q15(int16_t *input,uint16_t *output,uint32_t length_cplx)
{
    uint32_t i=0;
    for(i=0;i<length_cplx;i++)
    {
        output[i] =(uint16_t)sqrt( (double)( input[2*i]*input[2*i] + input[2*i+1]*input[2*i+1] ) );
    }
}
void cplx_abs_square_q15(int16_t *input,uint32_t *output,uint32_t length_cplx)
{
    uint32_t i=0;
    for(i=0;i<length_cplx;i++)
    {
        output[i] = input[2*i]*input[2*i] + input[2*i+1]*input[2*i+1]  ;
    }
}

void max_ui16_normal(uint16_t *input,
              uint32_t length,
              uint16_t *max_val,
              uint32_t *max_idx)
{
    uint16_t max_temp=0;
    uint32_t i=0;
    for(i=0;i<length;i++)
    {
        if(input[i]>max_temp)
        {
            max_temp = input[i];
            *max_idx = i;
        }

    }
    *max_val=max_temp;

}

void max_ui16_normal_st_end(uint16_t *input,
              uint32_t st,
              uint32_t end,
              uint16_t *max_val,
              uint32_t *max_idx)
{
    uint16_t max_temp=0;
    uint32_t i=0;
    for(i=st ; i<end+1 ; i++)
    {
        if(input[i]>max_temp)
        {
            max_temp = input[i];
            *max_idx = i;
        }

    }
    *max_val=max_temp;

}

void average_ui16_normal(uint16_t *input,
                         uint32_t length,
                         uint16_t *average_val)
{
    uint32_t sum=0;
    uint32_t i=0;
    for(i=0;i<length;i++)
    {
        sum+=input[i];
    }
    *average_val=(uint16_t)((float)sum/(float)length);

}



void hanning_window(int16_t *input,int16_t *output,uint32_t length)
{
    uint32_t i;
        for(i=0;i<length;i++)
        {
                output[i] = input[i] * (0.5f + 0.5f*cosf(PI*(2.0f*i-(length-1))/(float)(length-1.0f)));
        }
}


void get_RMS(int16_t *input,int16_t average_val,uint16_t *RMS,uint32_t length)
{
   uint32_t i=0;
   int32_t sum=0;
   int16_t val_temp_no_dc=0;


   for(i=0;i<length;i++)
   {
       val_temp_no_dc = input[i] - average_val;
       sum += val_temp_no_dc*val_temp_no_dc;
   }
   sum = sqrtf(((float)sum / (float)length));
   *RMS = sum;
}

void find_max_min(float *data,uint32_t length,float *max,float *min)
{
        uint32_t i=0;
        float max_temp=0;
        float min_temp=100000000;

        for(i=0;i<length;i++)
        {
                if(data[i]>max_temp)
                    max_temp = data[i];

                if(data[i]<min_temp)
                    min_temp = data[i];
        }

        *max = max_temp;
        *min = min_temp;
}

float sum(float *data,uint32_t length)
{
        float sum_res = 0;
        uint32_t i;
        for(i=0;i<length;i++)
        {
                sum_res+=data[i];
        }
        return sum_res;

}

void smooth(float *data,uint32_t length,float *output_data,uint32_t WINDOW_LENGTH)
{
        uint32_t i=0;
        float max_temp;
        float min_temp;


        for(i=0;i<length;i++)
        {
                if(i<(uint32_t)((float)WINDOW_LENGTH/2.0f+0.5f))
                {
                        find_max_min(data+i,WINDOW_LENGTH,&max_temp,&min_temp);
                        output_data[i] = (sum(data+i,WINDOW_LENGTH) - max_temp - min_temp)/(float)(WINDOW_LENGTH-2);
                }
                else if((length-i)<(uint32_t)((float)WINDOW_LENGTH/2.0f+0.5f))
                {
                        find_max_min(data+i-WINDOW_LENGTH,WINDOW_LENGTH,&max_temp,&min_temp);
                        output_data[i] = (sum(data+i-WINDOW_LENGTH,WINDOW_LENGTH) - max_temp - min_temp)/(float)(WINDOW_LENGTH-2);
                }
                else
                {
                        find_max_min(data+i-(uint32_t)((float)WINDOW_LENGTH/2.0f),WINDOW_LENGTH,&max_temp,&min_temp);
                        output_data[i] = (sum(data+i-(uint32_t)((float)WINDOW_LENGTH/2.0f),WINDOW_LENGTH) - max_temp - min_temp)/(float)(WINDOW_LENGTH-2);
                }
        }
}

void quick_sort(float *arr, int left, int right) {
    int j;
    float temp;
    float pivot;
    int i;

    if (left >= right) {
        return;
    }

    pivot = arr[right];
    i = left - 1;

    for (j = left; j < right; j++) {
        if (arr[j] < pivot) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[right];
    arr[right] = temp;

    quick_sort(arr, left, i);
    quick_sort(arr, i + 2, right);
}


