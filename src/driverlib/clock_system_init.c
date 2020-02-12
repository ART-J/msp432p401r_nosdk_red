/*
 * clock_system_init.c
 *
 *  Created on: 2020年2月12日
 *      Author: 90342
 */
//******************************************************************************
//   MSP432P401 - Device configuration for operation @ MCLK = DCO = 48MHz
//
//   Description: Proper device configuration to enable operation at MCLK=48MHz
//   including:
//   1. Configure VCORE level to 1
//   2. Configure flash wait-state to 2
//   3. Configure HFXT sourced by 48MHz XTAL
//   4. Source MCLK & HSMCLK from HFXT ,SMCLK from HFXT
//   5. Configure SMCLK/4 = 12Mhz
//
//   After configuration is complete, MCLK & HSMCLK are output to port pins P4.3.

//
//                MSP432P401RPZ
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |             P1.0|----> LED
//            |             P4.2|----> ACLK = ~32kHz
//            |             P4.3|----> MCLK = ~48MHz
//            |             P4.4|----> HSMCLK = ~48MHz
//            |                 |
//            |             PJ.2|------
//            |                 |     |
//            |                 |    HFXT @ 48MHz
//            |                 |     |
//            |             PJ.3|------

//
#include <msp.h>
#include <inc/driverlib/driverlib.h>


void CSInit(void)
{
    uint32_t currentPowerState;


    /* NOTE: This example assumes the default power state is AM0_LDO.
     * Refer to  MSP4322001_pcm_0x code examples for more complete PCM operations
     * to exercise various power state transitions between active modes.
     */

    /* Step 1: Transition to VCORE Level 1: AM0_LDO --> AM1_LDO */

    /* Get current power state, if it's not AM0_LDO, error out */
    currentPowerState = PCM->CTL0 & PCM_CTL0_CPM_MASK;
    if (currentPowerState != PCM_CTL0_CPM_0)
        error();

    while ((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
    PCM->CTL0 = PCM_CTL0_KEY_VAL | PCM_CTL0_AMR_1;
    while ((PCM->CTL1 & PCM_CTL1_PMR_BUSY));
    if (PCM->IFG & PCM_IFG_AM_INVALID_TR_IFG)
        error();                            // Error if transition was not successful
    if ((PCM->CTL0 & PCM_CTL0_CPM_MASK) != PCM_CTL0_CPM_1)
        error();                            // Error if device is not in AM1_LDO mode

    /* Step 2: Configure Flash wait-state to 2 for both banks 0 & 1 */
    FLCTL->BANK0_RDCTL = FLCTL->BANK0_RDCTL & ~FLCTL_BANK0_RDCTL_WAIT_MASK | FLCTL_BANK0_RDCTL_WAIT_2;
    FLCTL->BANK1_RDCTL  = FLCTL->BANK0_RDCTL & ~FLCTL_BANK1_RDCTL_WAIT_MASK  | FLCTL_BANK1_RDCTL_WAIT_2 ;

    /* Step 3: Configure HFXT to use 48MHz crystal, source to MCLK & HSMCLK*/


    PJSEL0 |= BIT2 | BIT3;                  // Configure PJ.2/3 for HFXT function
    PJSEL1 &= ~(BIT2 | BIT3);

    CS->KEY = CS_KEY_VAL ;                      // Unlock CS module for register access
    CS->CTL2 |= CS_CTL2_HFXT_EN | CS_CTL2_HFXTFREQ_6 | CS_CTL2_HFXTDRIVE;
    while(CS->IFG & CS_IFG_HFXTIFG)
        CS->CLRIFG |= CS_CLRIFG_CLR_HFXTIFG;

    /* Select MCLK & HSMCLK = HFXT, no divider */
    CS->CTL1 = CS->CTL1 & ~(CS_CTL1_SELA_MASK |CS_CTL1_DIVA_MASK|CS_CTL1_SELM_MASK | CS_CTL1_DIVM_MASK | CS_CTL1_SELS_MASK | CS_CTL1_DIVHS_MASK) |CS_CTL1_SELA_2| CS_CTL1_SELM__HFXTCLK | CS_CTL1_SELS__HFXTCLK|CS_CTL1_DIVS__4;

    CS->KEY = 0;                             // Lock CS module from unintended accesses
}

void error(void)
{
    volatile uint32_t i;
    P1DIR |= BIT0;
    while (1)
    {
        P1OUT ^= BIT0;
        for(i=0;i<20000;i++);       // Blink LED forever
    }
}



