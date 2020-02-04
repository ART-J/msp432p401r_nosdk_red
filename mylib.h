/*
 * user.h
 *
 *  Created on: 2019Äê5ÔÂ29ÈÕ
 *      Author: 90342
 */

#ifndef INC_USER_USER_H_
#define INC_USER_USER_H_

#include "msp.h"
#include <inc/devicelib/ssd1351.h>
#include <inc/devicelib/dac8571.h>
#include <inc/driverlib/ADC14.h>
#include <inc/driverlib/usci_b3_spi.h>
#include <inc/driverlib/wdt.h>
#include <inc/system/fonts.h>
#include <inc/system/init.h>
#include <inc/system/user.h>

#define LMP3 {SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;__sleep();}
#define LMP3_EXIT SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;


#endif /* INC_USER_USER_H_ */
