/*
 * adc_fft.c
 *
 *  Created on: 2023��7��13��
 *      Author: wyj1119
 */
#include "adc_fft.h"
#include "my_math.h"
#include "my_usart.h"
#include "delay.h"
/* The control table used by the uDMA controller.  This table must be aligned
 * to a 1024 byte boundary. */
#if defined(__ICCARM__)
#pragma data_alignment=1024
uint8_t pui8ControlTable[1024];
#elif defined(__TI_ARM__)
#pragma DATA_ALIGN(pui8ControlTable, 2048)
uint8_t pui8ControlTable[2048];
#else
uint8_t pui8ControlTable[1024] __attribute__ ((aligned(1024)));
#endif

#define SYS_CLK 120000000





void adc01_tim_config(uint32_t Fs)
{
    /* Enable Timer-0 clock and configure the timer in periodic mode with
     * a frequency of 1 KHz. Enable the ADC trigger generation from the
     * timer-0. */
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_TIMER0)))
    {
    }

    MAP_TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC);
    MAP_TimerLoadSet(TIMER0_BASE, TIMER_A, (uint32_t)(SYS_CLK/Fs));
    MAP_TimerADCEventSet(TIMER0_BASE, TIMER_ADC_TIMEOUT_A);
    MAP_TimerControlTrigger(TIMER0_BASE, TIMER_A, true);
    MAP_TimerEnable(TIMER0_BASE, TIMER_A);
}


void Init_adc0_dma(int16_t *adc_buffer_0)
{

    /* Enable the clock to GPIO Port E and wait for it to be ready */
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
        while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)))
        {
        }

        /* Configure PE0-PE3 as ADC input channel */
        MAP_GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);

        /* Enable the clock to ADC-0 and wait for it to be ready */
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
        while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)))
        {
        }

        /* Configure Sequencer 2 to sample the analog channel : AIN0-AIN3. The
         * end of conversion and interrupt generation is set for AIN3 */

        MAP_ADCSequenceStepConfigure(ADC0_BASE, 2, 0, ADC_CTL_CH0 | ADC_CTL_IE |
                                     ADC_CTL_END);

        /* Enable sample sequence 2 with a timer signal trigger.  Sequencer 2
         * will do a single sample when the timer generates a trigger on timeout*/
        MAP_ADCSequenceConfigure(ADC0_BASE, 2, ADC_TRIGGER_TIMER, 1);

        /* Clear the interrupt status flag before enabling. This is done to make
         * sure the interrupt flag is cleared before we sample. */
        MAP_ADCIntClearEx(ADC0_BASE, ADC_INT_DMA_SS2);
        MAP_ADCIntEnableEx(ADC0_BASE, ADC_INT_DMA_SS2);

        /* Enable the DMA request from ADC0 Sequencer 2 */
        MAP_ADCSequenceDMAEnable(ADC0_BASE, 2);

        /* Since sample sequence 2 is now configured, it must be enabled. */
        MAP_ADCSequenceEnable(ADC0_BASE, 2);

        MAP_ADCReferenceSet(ADC0_BASE,ADC_REF_INT);
        /* Enable the Interrupt generation from the ADC-0 Sequencer */
        MAP_IntEnable(INT_ADC0SS2);

        /* Enable the DMA and Configure Channel for TIMER0A for Ping Pong mode of
         * transfer */
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
        while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_UDMA)))
        {
        }

        MAP_uDMAEnable();

        /* Point at the control table to use for channel control structures. */
        MAP_uDMAControlBaseSet(pui8ControlTable);

        /* Map the ADC0 Sequencer 2 DMA channel */
        MAP_uDMAChannelAssign(UDMA_CH16_ADC0_2);

        /* Put the attributes in a known state for the uDMA ADC0 Sequencer 2
         * channel. These should already be disabled by default. */
        MAP_uDMAChannelAttributeDisable(UDMA_CH16_ADC0_2,
                                        UDMA_ATTR_ALTSELECT | UDMA_ATTR_USEBURST |
                                        UDMA_ATTR_HIGH_PRIORITY |
                                        UDMA_ATTR_REQMASK);

        /* Configure the control parameters for the primary control structure for
         * the ADC0 Sequencer 2 channel. The primary control structure is used for
         * copying the data from ADC0 Sequencer 2 FIFO to srcBuffer. The transfer
         * data size is 16 bits and the source address is not incremented while
         * the destination address is incremented at 16-bit boundary.
         */
        MAP_uDMAChannelControlSet(UDMA_CH16_ADC0_2 | UDMA_PRI_SELECT,
                                  UDMA_SIZE_16 | UDMA_SRC_INC_NONE | UDMA_DST_INC_16 |
                                  UDMA_ARB_1);

        /* Set up the transfer parameters for the ADC0 Sequencer 2 primary control
         * structure. The mode is Basic mode so it will run to completion. */
        MAP_uDMAChannelTransferSet(UDMA_CH16_ADC0_2 | UDMA_PRI_SELECT,
                                   UDMA_MODE_BASIC,
                                   (void *)&ADC0->SSFIFO2, (void *)&adc_buffer_0,
                                   sizeof(adc_buffer_0)/2);

        /* The uDMA ADC0 Sequencer 2 channel is primed to start a transfer. As
         * soon as the channel is enabled and the Timer will issue an ADC trigger,
         * the ADC will perform the conversion and send a DMA Request. The data
         * transfers will begin. */
        MAP_uDMAChannelEnable(UDMA_CH16_ADC0_2);
}


void Init_adc1_dma(int16_t *adc_buffer_1)
{

    /*  Enable the clock to GPIO Port E and wait for it to be ready */
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
        while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)))
        {
        }

        /* Configure PE0-PE3 as ADC input channel */
        MAP_GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_1);

        /* Enable the clock to ADC-0 and wait for it to be ready */
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
        while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_ADC0)))
        {
        }

        /* Configure Sequencer 2 to sample the analog channel : AIN0-AIN3. The
         * end of conversion and interrupt generation is set for AIN3 */
        MAP_ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH2 |
                                     ADC_CTL_SHOLD_32 | ADC_CTL_IE | ADC_CTL_END);

        /* Enable sample sequence 2 with a timer signal trigger.  Sequencer 2
         * will do a single sample when the timer generates a trigger on timeout*/
        MAP_ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_TIMER, 0);

        /* Clear the interrupt status flag before enabling. This is done to make
         * sure the interrupt flag is cleared before we sample. */
        MAP_ADCIntClearEx(ADC0_BASE, ADC_INT_DMA_SS1);
        MAP_ADCIntEnableEx(ADC0_BASE, ADC_INT_DMA_SS1);

        /* Enable the DMA request from ADC0 Sequencer 2 */
        MAP_ADCSequenceDMAEnable(ADC0_BASE, 1);

        /* Since sample sequence 2 is now configured, it must be enabled. */
        MAP_ADCSequenceEnable(ADC0_BASE, 1);

        /* Enable the Interrupt generation from the ADC-0 Sequencer */
        MAP_IntEnable(INT_ADC0SS1);

        /* Enable the DMA and Configure Channel for TIMER0A for Ping Pong mode of
         * transfer */
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
        while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_UDMA)))
        {
        }

        MAP_uDMAEnable();

        /* Point at the control table to use for channel control structures. */
        MAP_uDMAControlBaseSet(pui8ControlTable);

        /* Map the ADC0 Sequencer 2 DMA channel */
        MAP_uDMAChannelAssign(UDMA_CH15_ADC0_1);

        /* Put the attributes in a known state for the uDMA ADC0 Sequencer 2
         * channel. These should already be disabled by default. */
        MAP_uDMAChannelAttributeDisable(UDMA_CH15_ADC0_1,
                                        UDMA_ATTR_ALTSELECT | UDMA_ATTR_USEBURST |
                                        UDMA_ATTR_HIGH_PRIORITY |
                                        UDMA_ATTR_REQMASK);

        /* Configure the control parameters for the primary control structure for
         * the ADC0 Sequencer 2 channel. The primary control structure is used for
         * copying the data from ADC0 Sequencer 2 FIFO to srcBuffer0. The transfer
         * data size is 16 bits and the source address is not incremented while
         * the destination address is incremented at 16-bit boundary.
         */
        MAP_uDMAChannelControlSet(UDMA_CH15_ADC0_1 | UDMA_PRI_SELECT,
                                  UDMA_SIZE_16 | UDMA_SRC_INC_NONE | UDMA_DST_INC_16 |
                                  UDMA_ARB_1);

        /* Set up the transfer parameters for the ADC0 Sequencer 2 primary control
         * structure. The mode is Basic mode so it will run to completion. */
        MAP_uDMAChannelTransferSet(UDMA_CH15_ADC0_1 | UDMA_PRI_SELECT,
                                   UDMA_MODE_BASIC,
                                   (void *)&ADC0->SSFIFO1, (void *)&adc_buffer_1,
                                   sizeof(adc_buffer_1)/2);

        /* The uDMA ADC0 Sequencer 2 channel is primed to start a transfer. As
         * soon as the channel is enabled and the Timer will issue an ADC trigger,
         * the ADC will perform the conversion and send a DMA Request. The data
         * transfers will begin. */
        MAP_uDMAChannelEnable(UDMA_CH15_ADC0_1);
}


void Init_adc2_dma(int16_t *adc_buffer_2)
{

    /* Enable the clock to GPIO Port E and wait for it to be ready */
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
        while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)))
        {
        }

        /* Configure PE0-PE3 as ADC input channel */
        MAP_GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_2);

        /* Enable the clock to ADC-0 and wait for it to be ready */
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
        while(!(MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_ADC1)))
        {
        }

        /* Configure Sequencer 2 to sample the analog channel : AIN0-AIN3. The
         * end of conversion and interrupt generation is set for AIN3 */

        MAP_ADCSequenceStepConfigure(ADC1_BASE, 3, 0, ADC_CTL_CH1 | ADC_CTL_IE |
                                     ADC_CTL_END);

        /* Enable sample sequence 2 with a timer signal trigger.  Sequencer 2
         * will do a single sample when the timer generates a trigger on timeout*/
        MAP_ADCSequenceConfigure(ADC1_BASE, 3, ADC_TRIGGER_TIMER, 3);

        /* Clear the interrupt status flag before enabling. This is done to make
         * sure the interrupt flag is cleared before we sample. */
        MAP_ADCIntClearEx(ADC1_BASE, ADC_INT_DMA_SS3);
        MAP_ADCIntEnableEx(ADC1_BASE, ADC_INT_DMA_SS3);

        /* Enable the DMA request from ADC0 Sequencer 2 */
        MAP_ADCSequenceDMAEnable(ADC1_BASE, 3);

        /* Since sample sequence 2 is now configured, it must be enabled. */
        MAP_ADCSequenceEnable(ADC1_BASE, 3);

        MAP_ADCReferenceSet(ADC1_BASE,ADC_REF_INT);
        /* Enable the Interrupt generation from the ADC-0 Sequencer */
        MAP_IntEnable(INT_ADC1SS3);

        /* Enable the DMA and Configure Channel for TIMER0A for Ping Pong mode of
         * transfer */
        MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
        while(!(SysCtlPeripheralReady(SYSCTL_PERIPH_UDMA)))
        {
        }

        MAP_uDMAEnable();

        /* Point at the control table to use for channel control structures. */
        MAP_uDMAControlBaseSet(pui8ControlTable);

        /* Map the ADC0 Sequencer 2 DMA channel */
        MAP_uDMAChannelAssign(UDMA_CH27_ADC1_3);

        /* Put the attributes in a known state for the uDMA ADC0 Sequencer 2
         * channel. These should already be disabled by default. */
        MAP_uDMAChannelAttributeDisable(UDMA_CH27_ADC1_3,
                                        UDMA_ATTR_ALTSELECT | UDMA_ATTR_USEBURST |
                                        UDMA_ATTR_HIGH_PRIORITY |
                                        UDMA_ATTR_REQMASK);

        /* Configure the control parameters for the primary control structure for
         * the ADC0 Sequencer 2 channel. The primary control structure is used for
         * copying the data from ADC0 Sequencer 2 FIFO to srcBuffer. The transfer
         * data size is 16 bits and the source address is not incremented while
         * the destination address is incremented at 16-bit boundary.
         */
        MAP_uDMAChannelControlSet(UDMA_CH27_ADC1_3 | UDMA_PRI_SELECT,
                                  UDMA_SIZE_16 | UDMA_SRC_INC_NONE | UDMA_DST_INC_16 |
                                  UDMA_ARB_1);

        /* Set up the transfer parameters for the ADC0 Sequencer 2 primary control
         * structure. The mode is Basic mode so it will run to completion. */
        MAP_uDMAChannelTransferSet(UDMA_CH27_ADC1_3 | UDMA_PRI_SELECT,
                                   UDMA_MODE_BASIC,
                                   (void *)&ADC1->SSFIFO3, (void *)&adc_buffer_2,
                                   sizeof(adc_buffer_2)/2);

        /* The uDMA ADC0 Sequencer 2 channel is primed to start a transfer. As
         * soon as the channel is enabled and the Timer will issue an ADC trigger,
         * the ADC will perform the conversion and send a DMA Request. The data
         * transfers will begin. */
        MAP_uDMAChannelEnable(UDMA_CH27_ADC1_3);
}



void set_Fs(uint32_t Fs,uint8_t start_adc)
{
    TimerDisable(TIMER0_BASE, TIMER_A);
    MAP_TimerLoadSet(TIMER0_BASE, TIMER_A, (SYS_CLK/Fs));
    if(start_adc==1)
        TimerEnable(TIMER0_BASE, TIMER_A);
}

void Init_fft(msp_fft_q15_params *params)
{
    params->length=BUFFER_SIZE;
    params->bitReverse=1;
    params->twiddleTable=MAP_msp_cmplx_twiddle_table_2048_q15;
}



void cal_fft(msp_fft_q15_params *params_fft_1024,int16_t *ADC_buffer,ADC_FFT_Structure *ADC_FFT_Str,uint8_t printf_option)
{
    uint8_t status=0;
    uint16_t average=0;



    average_ui16_normal((uint16_t*)ADC_buffer,BUFFER_SIZE,&average);
    get_RMS(ADC_buffer,average,&ADC_FFT_Str->RMS,BUFFER_SIZE);

    ADC_FFT_Str->RMS *= 0.806f;

//    hanning_window(ADC_buffer,ADC_FFT_Str->adc_fft_buffer,BUFFER_SIZE);
//    status = MAP_msp_fft_fixed_q15(params_fft_1024, ADC_FFT_Str->adc_fft_buffer);
//    cplx_abs_q15(ADC_FFT_Str->adc_fft_buffer,ADC_FFT_Str->fft_mag_buf,BUFFER_SIZE/2);
//    max_ui16_normal(ADC_FFT_Str->fft_mag_buf+BIAS_IDX,BUFFER_SIZE/2-BIAS_IDX,&ADC_FFT_Str->max_val,&ADC_FFT_Str->max_idx);
//    ADC_FFT_Str->max_idx += BIAS_IDX;
//
//    if(ADC_FFT_Str->max_idx<BUFFER_SIZE/2-50)
//    {
//        max_ui16_normal(ADC_FFT_Str->fft_mag_buf+ADC_FFT_Str->max_idx+BIAS_IDX,
//                    BUFFER_SIZE/2-(ADC_FFT_Str->max_idx+BIAS_IDX),
//                    &ADC_FFT_Str->sec_val,
//                    &ADC_FFT_Str->sec_idx);
//
//        ADC_FFT_Str->sec_idx += (ADC_FFT_Str->max_idx+BIAS_IDX);
//    }
//    else
//    {
//         USART_printf(UART0_BASE,"NO sec_val\r\n");
//    }
//
//    ADC_FFT_Str->max_Real = ADC_FFT_Str->adc_fft_buffer[ADC_FFT_Str->max_idx*2];
//    ADC_FFT_Str->max_Imag = ADC_FFT_Str->adc_fft_buffer[ADC_FFT_Str->max_idx*2+1];


    if(printf_option)
        USART_printf(UART0_BASE,"RMS = %u\r\n",ADC_FFT_Str->RMS);

    if(status==0)
      MAP_GPIOPinWrite(GPIO_PORTN_BASE, (GPIO_PIN_0 | GPIO_PIN_1), 3);
}



