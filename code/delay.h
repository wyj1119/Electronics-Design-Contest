/*
 * delay.h
 *
 *  Created on: 2023年7月12日
 *      Author: wyj1119
 */

#ifndef DELAY_H_
#define DELAY_H_



/*******************************************
//MSP432P401R
//4 移植滴答延时
//Bilibili：m-RNA
//E-mail:m-RNA@qq.com
//创建日期:2021/7/22
*******************************************/

/********      正点原子@ALIENTEK      ********
 * 技术论坛:www.openedv.com
 * 创建日期:2010/1/1
 * 版本：V1.8
 *
 * 说明 ：
 * 源码为正点原子@ALIENTEK 编写
 * 本人RNA，只是移植到了MSP432平台
 * 仅作为学习使用
 * 在此也感谢正点原子
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
