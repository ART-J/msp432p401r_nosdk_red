/*
 * IO_init.c
 *
 *  Created on: 2020年2月13日
 *      Author: 90342
 */

#include "msp.h"
#include <inc/driverlib/IO_init.h>

void io_init(void)
{
    P1DIR=P2DIR=P3DIR=P4DIR=P5DIR=P6DIR=P7DIR=P8DIR=P9DIR=P10DIR=0xff;
    P1OUT=P2OUT=P3OUT=P4OUT=P5OUT=P6OUT=P7OUT=P8OUT=P9OUT=P10OUT=0x00;
}


