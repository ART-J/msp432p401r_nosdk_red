/*
 * wdt.c
 *
 *  Created on: 2016-10-20
 *      Author: Jack Chen <redchenjs@live.com>
 */

#include <msp432.h>
#include <mylib.h>

 uint8_t systik_flag=0;

void wdt_init(void)
{
	WDTCTL = WDTPW | WDTSSEL__ACLK | WDTTMSEL | WDTCNTCL | WDTIS_5;//250ms

	// Configure GPIO
	P1DIR |= BIT0;                          // Set P1.0 to output direction

	SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;           // Wake up after ISR
	__enable_interrupt();
	NVIC->ISER[0] = 1 << ((WDT_A_IRQn) & 31);
}
void WDT_A_IRQHandler(void)
{
	static uint16_t i=0;
	//P1OUT ^= BIT0;//
	if(i++>3)
	{
		i=0;
		systik_flag=1;
		P1OUT ^= BIT0;
	}

	LMP3_EXIT;
}

