# msp432p401r_nosdk_red
The code for msp432p401r (red board / nosdk)

V1.3
1.��䣺��SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk; ���� ��__sleep();��������	
	1��SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk  ���ܣ�ʹ�ܽ����жϻ�������
	2��__sleep();�� __wfi()                  ���ܣ�ʹ��ֹͣģʽ   ��CPUֹͣ�ڵ�ǰλ�ã��ȴ��˳�ֹͣģʽ		 
		��Щָ���ΪARMָ�������		
2.���ʣ���ʹ��SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk ʱ��ʵ��  �������߲����ж����˳�����
		����__sleep();��__low_power_mode_off_on_exit()������ʵ��ֹͣ���˳�ֹͣģʽ		
3.���ĵȼ��޷��ı䡣

V1.4
1.�����͹���ģʽ���룺	
	1�����ֽ���͹���ģʽ�Ĵ��룬MCU��һֱ���ߣ��޷������ѡ�����һֱֹͣ��__WFI()�ϣ��ȵ��жϻ��Ѳſ��ԡ�	
	__STATIC_INLINE void EMU_EnterEM1(void)
	{
	/* Just enter Cortex-M3 sleep mode */
	 SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
	 SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
	 __sleep();
	}	
	2) �ӵ͹��Ķ�ʱ���жϴ�������Ҫ����һ�����ſ��Ի���MCUȥ�������������� �����жϹ����ˣ�����������ҳ�޷�����MCUȥ����������	
	(SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk) //�˳�����ģʽ�����жϴ�����������������֮�� �ſ��Խ��л���MCU
	--------------------- 
	ԭ�ģ�https://blog.csdn.net/wang2425559/article/details/77895047 

2.�ı����ṹ��	
	1�����뿴�Ź���ʱ�� ÿ250ms�ж�һ�Σ�4�κ󣨴ﵽ1sʱ������MCU����ADCת�� ����8�β���	
	2������mylib.h ���������Զ����H�ļ�����������ģʽ
			SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
			 SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
			 __sleep();
	 		���ó�Ԥ����ɵ͹���0 �� LMP0 ��������ã�			
	3��	(SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk) //�˳�����ģʽ
			���ó�Ԥ���� �˳��͹���0 �� LMP0_EXIT ���������

V1.5
1.����DAC8571���� �� USCI_B0 i2c ������δ���ԣ������������Ƿ���ȷ��
2.����soft_spi ������δ���ԣ���ʱʱ����

V1.6
1.����ADC14��ֲ���ģʽ��A0/A1������룬�������MEM0��
	A0>A1ʱ   	 16384> ADC14->MEM[0] >8192
	A0==A1ʱ 	 ADC14->MEM[0] =8192
	A0<A1ʱ     	 0<ADC14->MEM[0] <8192	
2.ADC14ģʽ���Ĳ�ȡ    Ԥ���뷽ʽѡ��    Ԥ�����ַ������ADC14.h

V1.7
1.�����͹���ģʽ     SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;  __sleep(); Ϊ����LMP3
		__sleep();    Ϊ����LPM0

V2.1
1.�������µĺ�ɫ�����壬��Ҫ����ϵͳʱ���ļ���system_msp432p401r.c����
2.��������ʱ���������ж�汾�ģ���ȡ������Ĭ�ϵ�ǰ�汾���ɡ������޷����ӿ����塣

V2.2	
1.�޸�ϵͳʱ�����ã�����ʱ�ӳ�ʼ������CSInit();������system_msp432p401r.c������
MCLK=HSMCLK	=48 Mhz��SMCLK=12Mhz��ACLK=32Khz
2.���� UCSIA0Ϊuartģʽ���ش�ADC���㷨��������ݣ������¼��ֻʵ�ֵ��ֽڣ����ӽӿڻ�δ��ɣ�

V2.3 ʵ��printf���ڳ����ַ��������շ�����
