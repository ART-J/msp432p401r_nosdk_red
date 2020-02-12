/*
 * user.c
 *
 *  Created on: 2018-02-16 18:00
 *      Author: Jack Chen <redchenjs@live.com>
 *  Fixed on :  2020-02-04 22:14
 *      Author: art-j <jjw903427521@gmail.com>
 */


#include "msp.h"
#include <inc/user/display.h>

void user_init(void)
{

}
void user_loop(void)
{
	 display();
	 ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC; //使能采样，开始转换

//    input_update();
//    measure_update();
//    control_update();
//    display();
}
