 /*  Fixed on :  2020-02-04 22:14
     Author: art-j <jjw903427521@gmail.com>
 */

//******************************************************************************
//  MSP432P401 Demo - ADC14, Repeated Sequence of Conversions
//
//  Description: This example shows how to perform a repeated sequence of
//  conversions using "repeat sequence-of-channels" mode.  AVcc is used for the
//  reference and repeated sequence of conversions is performed on Channels A0,
//  A1, A2, and A3. Each conversion result is stored in ADC14->MEM[0], ADC14->MEM[1],
//  ADC14->MEM[2], and ADC14->MEM[3] respectively. After each sequence, the 4 conversion
//  results are moved to A0results[], A1results[], A2results[], and A3results[].
//  Test by applying voltages to channels A0 - A3. Open a watch window in
//  debugger and view the results. Set Breakpoint1 in the index increment line
//  to see the array values change sequentially and Breakpoint2 to see the entire
//  array of conversion results in A0results[], A1results[], A2results[], and
//  A3results[]for the specified Num_of_Results.
//
//  Note that a sequence has no restrictions on which channels are converted.
//  For example, a valid sequence could be A0, A3, A2, A4, A2, A1, A0, and A7.
//  See the User's Guide for instructions on using the ADC14.
//
//               MSP432P401
//             -----------------
//         /|\|                 |
//          | |                 |
//          --|RST              |
//            |                 |
//    Vin0 -->|P5.5/A0          |
//    Vin1 -->|P5.4/A1          |
//    Vin2 -->|P5.3/A2          |
//    Vin3 -->|P5.2/A3          |
//            |                 |
//

#include "msp.h"
#include <stdint.h>
#include <inc/driverlib/ADC14.h>
#define   Num_of_Results   8

#ifdef   sinple
volatile uint16_t A0results[Num_of_Results];
volatile uint16_t A1results[Num_of_Results];
volatile uint16_t A2results[Num_of_Results];
volatile uint16_t A3results[Num_of_Results];

volatile uint32_t A0value=0;
volatile uint32_t A1value=0;
volatile uint32_t A2value=0;
volatile uint32_t A3value=0;

static uint8_t index;
#endif

volatile uint32_t  ADCvalue=0;

void ADC14init(void)
{
//******************************************************************************
#ifdef sinple
    P5SEL1 |= BIT5 | BIT4 | BIT3 |BIT2;       // Enable A/D channel A0-A3
    P5SEL0 |= BIT5 | BIT4 | BIT3 |BIT2;

    __enable_interrupt();
    NVIC->ISER[0] = 1 << ((ADC14_IRQn) & 31);// Enable ADC interrupt in NVIC module

    ADC14->CTL0 = ADC14_CTL0_ON | ADC14_CTL0_MSC | ADC14_CTL0_SHT0__192 | ADC14_CTL0_SHP | ADC14_CTL0_CONSEQ_3; // Turn on ADC14, extend sampling time
                                                                              // to avoid overflow of results

    ADC14->MCTL[0] = ADC14_MCTLN_INCH_0;                 // ref+=AVcc, channel = A0
    ADC14->MCTL[1] = ADC14_MCTLN_INCH_1;                 // ref+=AVcc, channel = A1
    ADC14->MCTL[2] = ADC14_MCTLN_INCH_2;                 // ref+=AVcc, channel = A2
    ADC14->MCTL[3] = ADC14_MCTLN_INCH_3+ADC14_MCTLN_EOS;        // ref+=AVcc, channel = A3, end seq.
    ADC14->IER0 = ADC14_IER0_IE3;                     // Enable ADC14IFG.3

    //SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;             // Wake up on exit from ISR
    ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;        // Start conversion-software trigger
#endif
//******************************************************************************
#ifdef differ
    P5SEL1 |= BIT5 | BIT4;                    // Configure P5.5/4 (A0/1) for ADC
    P5SEL0 |= BIT5 | BIT4;

    __enable_interrupt();
    NVIC->ISER[0] = 1 << ((ADC14_IRQn) & 31);         // Enable ADC interrupt in NVIC module

    // Configure ADC14
    ADC14->CTL0 = ADC14_CTL0_SHT0_2 | ADC14_CTL0_SHP | ADC14_CTL0_ON;          // Sampling time, S&H=16, ADC14 on
    ADC14->CTL1 = ADC14_CTL1_RES__14BIT;                   // Use sampling timer, 12-bit conversion results
    ADC14->MCTL[0] |= ADC14_MCTLN_INCH_0 | ADC14_MCTLN_DIF;     // A0 ADC input in dif. mode select; Vref=AVCC
    ADC14->IER0 |= ADC14_IER0_IE0;                    // Enable ADC conv complete interrupt
#endif
//******************************************************************************
}

// ADC14 interrupt service routine
void ADC14_IRQHandler(void)
{
//******************************************************************************
#ifdef sinple
    uint16_t i;
    if (ADC14->IFGR0 & ADC14_IFGR0_IFG3)
    {
        A0results[index] = ADC14->MEM[0];       // Move A0 results, IFG is cleared
        A1results[index] = ADC14->MEM[1];       // Move A1 results, IFG is cleared
        A2results[index] = ADC14->MEM[2];       // Move A2 results, IFG is cleared
        A3results[index] = ADC14->MEM[3];       // Move A3 results, IFG is cleared
        //index = (index + 1) & 0x7;          // Increment results index, modulo
        index++;
        if(index>=Num_of_Results )
        {
            A3value=0;
            for(i=0;i<Num_of_Results;i++)
                A3value+=A3results[i];
            A3value/=Num_of_Results;
            ADC14->CTL0 &= ~(ADC14_CTL0_ENC | ADC14_CTL0_SC);
            index=0;
            //SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;
        }

        __no_operation();                   //Set Breakpoint1 here
    }
#endif
//******************************************************************************
#ifdef differ
    ADCvalue=ADC14->MEM[0];
    //   A0>A1时      16384> ADC14->MEM[0] >8192
    //   A0==A1时     ADC14->MEM[0] =8192
    //   A0<A1时          0<ADC14->MEM[0] <8192
    __no_operation();

#endif

}
//******************************************************************************
//   Description: A single sample is made on differential channel A0-A1
//   with reference to AVcc.
//   A resistor ladder is used to provide two different voltage inputs one at
//   A2 and the other at A3. Since equal resistors are used, the input voltage
//   at A0 and A1 are 2/3Vin and 1/3Vin respectively.
//   Vin is varied from 1V to 3V. When Vin = 3V, A0 = 2V and A1 = 1V providing
//   a differential voltage of 1V across the ADC input.
//   If A0-A1 >= 1V, The full, correct handling of
//   and ADC14 interrupt is shown as well.
////                msp432p401
//  Vin= 1V-3V -----------------
//     |      |                 |
//    10K     |                 |
//     |      |                 |
//     |      |                 |
//     -------| A0=2/3Vin       |
//     |      |                 |
//     10K    |                 |
//     |      |                 |
//     -------| A1=1/3Vin       |
//     |      |                 |
//    10K     |                 |
//     |      |                 |
//    GND


//   A0>A1时      16384> ADC14->MEM[0] >8192
//   A0==A1时     ADC14->MEM[0] =8192
//   A0<A1时          0<ADC14->MEM[0] <8192


