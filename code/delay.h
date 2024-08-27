/*
 * delay.h
 *
 *  Created on: 2023��7��12��
 *      Author: wyj1119
 */

#ifndef DELAY_H_
#define DELAY_H_



/*******************************************
//MSP432P401R
//4 ��ֲ�δ���ʱ
//Bilibili��m-RNA
//E-mail:m-RNA@qq.com
//��������:2021/7/22
*******************************************/

/********      ����ԭ��@ALIENTEK      ********
 * ������̳:www.openedv.com
 * ��������:2010/1/1
 * �汾��V1.8
 *
 * ˵�� ��
 * Դ��Ϊ����ԭ��@ALIENTEK ��д
 * ����RNA��ֻ����ֲ����MSP432ƽ̨
 * ����Ϊѧϰʹ��
 * �ڴ�Ҳ��л����ԭ��
 *********************************************/

#ifndef __DELAY_H
#define __DELAY_H
#include <ti/devices/msp432e4/driverlib/driverlib.h>

void delay_init(void);
void delay_ms(uint32_t nms);
void delay_us(uint32_t nus);
void Delay_ns (uint8_t t);
#endif


#endif /* DELAY_H_ */
