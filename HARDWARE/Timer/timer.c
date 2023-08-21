#include "timer.h"

extern int time;

void TIM5_Int_Init(u16 arr,u16 psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM5, TIM_IT_Update ,ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM5, ENABLE);  //ʹ��TIMx����
							 
}

void TIM5_IRQHandler(void)   //TIM3�ж�
{
	if(TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		mpu_dmp_get_data(&pitch , &roll , &yaw);//�Ƕ�
		yaw = yaw + 8.2;	
		
		Sensor_Init();
		
		xun_ji();
//		if(flag == 2)
//			if(pidMPU6050YawMovement.target_val <= 180)			//��ת90��
//				pidMPU6050YawMovement.target_val += 90;
//		if(flag == 3)
//			if(pidMPU6050YawMovement.target_val >= -180)			//��ת90��
//				pidMPU6050YawMovement.target_val -= 90;

		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);  //���TIMx���жϴ�����λ:TIM �ж�Դ 
	}
}
