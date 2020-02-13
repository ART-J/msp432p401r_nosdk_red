/*
 * user.h
 *
 *  Created on: 2019-05-29
 *      Author: 90342
 *  Fixed on :  2020-02-13 22:14
 *      Author: art-j <jjw903427521@gmail.com>
 */

#ifndef INC_USER_USER_H_
#define INC_USER_USER_H_

#include "msp.h"
#include <inc/driverlib/driverlib.h>
#include <inc/devicelib/devicelib.h>
#include <inc/user/display.h>


#define LMP3 {SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;__sleep();}
#define LMP3_EXIT SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;


#endif /* INC_USER_USER_H_ */
