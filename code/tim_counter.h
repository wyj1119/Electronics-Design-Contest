/*
 * tim_counter.h
 *
 *  Created on: 2023Äê7ÔÂ13ÈÕ
 *      Author: wyj1119
 */

#ifndef TIM_COUNTER_H_
#define TIM_COUNTER_H_

#include <ti/devices/msp432e4/driverlib/driverlib.h>

void Init_counter(uint32_t count);
void Init_Tim2_int(uint32_t cnt);
#endif /* TIM_COUNTER_H_ */
