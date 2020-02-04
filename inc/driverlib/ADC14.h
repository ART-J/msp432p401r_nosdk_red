/*
 * ADC14.h
 *
 *  Created on: 2019年3月28日
 *      Author: 90342
 *  Fixed on :  2020-02-04 22:14
 *      Author: art-j <jjw903427521@gmail.com>
 */

#ifndef INC_DRIVERLIB_ADC14_H_
#define INC_DRIVERLIB_ADC14_H_

#include "stdint.h"

void ADC14init(void);
extern  void ADC14_ISR(void);
/************************************************/
/*select differ sample or sinple sample*/
#define   differ
//#define   sinple
/************************************************/
#ifdef   sinple
extern volatile uint16_t A0results[];
extern volatile uint16_t A1results[];
extern volatile uint16_t A2results[];
extern volatile uint16_t A3results[];

extern volatile uint32_t A0value;
extern volatile uint32_t A1value;
extern volatile uint32_t A2value;
extern volatile uint32_t A3value;
#endif

extern volatile uint32_t  ADCvalue; //ADC处理值


#endif /* INC_DRIVERLIB_ADC14_H_ */
