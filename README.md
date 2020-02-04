# msp432p401r_nosdk_red
The code for msp432p401r (red board / nosdk)
V1.3
1.语句：“SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk; ”和 “__sleep();”的区别
	1）SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk  功能：使能进入中断唤醒休眠
	2）__sleep();即 __wfi()                  功能：使能停止模式   ：CPU停止于当前位置，等待退出停止模式
		 
		这些指令皆为ARM指令集函数。
		
2.疑问：当使用SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk 时能实现  进入休眠并在中断中退出休眠
		但是__sleep();与__low_power_mode_off_on_exit()；不能实现停止后退出停止模式
3.功耗等级无法改变。

V1.4
1.更换低功耗模式代码：
	1）这种进入低功耗模式的代码，MCU会一直休眠，无法被唤醒。程序一直停止在__WFI()上，等到中断唤醒才可以。
	
	__STATIC_INLINE void EMU_EnterEM1(void)
	{
	/* Just enter Cortex-M3 sleep mode */
	 SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
	 SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
	 __sleep();
	}
	
	2) 从低功耗定时器中断处理函数中要加上一句代码才可以唤醒MCU去运行主函数否则 就是中断过来了，不加这句代码页无法唤醒MCU去运行主函数
	
	(SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk) //退出休眠模式。在中断处理函数中添加这个函数之后 才可以进行唤醒MCU
	--------------------- 
	原文：https://blog.csdn.net/wang2425559/article/details/77895047 

2.改变程序结构：
	1）加入看门狗定时器 每250ms中断一次，4次后（达到1s时）唤醒MCU开启ADC转换 进行8次采样
	2）加入mylib.h 引用所有自定义的H文件，并将休眠模式
			SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
			 SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
			 __sleep();
	 		设置成预定义成低功耗0 “ LMP0 ”方便调用，
	3）	(SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk) //退出休眠模式
			设置成预定义 退出低功耗0 “ LMP0_EXIT ”方便调用

V1.5
1.增加DAC8571驱动 和 USCI_B0 i2c 驱动（未测试，波特率设置是否正确）
2.增加soft_spi 驱动（未测试，延时时间误差）

V1.6
1.增加ADC14差分采样模式，A0/A1差分输入，结果存入MEM0；
	A0>A1时   	 16384> ADC14->MEM[0] >8192
	A0==A1时 	 ADC14->MEM[0] =8192
	A0<A1时     	 0<ADC14->MEM[0] <8192
2.ADC14模式更改采取    预编译方式选择    预定义字符存放于ADC14。h

V1.7
1.更正低功耗模式     SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;  __sleep(); 为进入LMP3     
			__sleep();    									     为进入LPM0
			

V2.1
1.适配最新的红色开发板，需要更改系统时钟文件（system_msp432p401r.c）。
2.调试下载时工程中若有多版本的，点取消，即默认当前版本即可。否则无法链接开发板。			
