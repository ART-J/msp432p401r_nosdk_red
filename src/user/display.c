/*
 * display.c
 *
 *  Created on: 2019年3月28日
 *      Author: 90342
 *  Fixed on :  2020-02-04 22:14
 *      Author: art-j <jjw903427521@gmail.com>
 */
#include <inc/devicelib/ssd1351.h>
#include <inc/system/fonts.h>
#include <inc/driverlib/ADC14.h>
#include "msp.h"

void display(void)
{
    static int i=0;

    //ssd1351_show_rainbow();                                       //彩虹刷屏
    //ssd1351_display_string(46, 72, "+", FONT_1608, Blue, Black);  //加号
/*单通道ADC*/
#ifdef sinple
    ssd1351_display_num(0, 0, A3value,5, FONT_1608, Blue, Black);
#endif
/*差分ADC*/
#ifdef differ
    ssd1351_display_num(0, 0, ADCvalue,5, FONT_1608, Blue, Black);  //x,y,value(unsigned int),显示字符长度，字体像素大小，蓝字，黑底
#endif
    if(i++>60)i=0;//计数

}

