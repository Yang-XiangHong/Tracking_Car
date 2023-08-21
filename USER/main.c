#include "led.h"
#include "usart.h"
#include "delay.h"
#include "sys.h"
#include "key.h"
#include "motor.h"
#include "pwm.h"
#include "oled.h"
#include "timer.h"
#include "pid.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "mpu6050.h"
#include "encoder.h"

uint8_t g_ucalHW_Read[4] = {0};		//保存红外对管电平的数值
int8_t err;
int16_t out1 , out2 , speed , PID_value;
int8_t g_ThisState , g_LastState;
int16_t speed = 1700;	//3200
int flag = 0;

float pitch , roll , yaw;
short accx , accy , accz;
short gyrox , gyroy , gyroz;

short Encoder_Left , Encoder_Right;

int time = 50;

int temp;

int g_read_value[5];
 
int main(void)
{	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(9600);
	delay_init();	    	 //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	Key_Init();
	
	PWM_Init_TIM1(7199 , 0);
	Encoder_Init_TIM2();
	Encoder_Init_TIM3();
	
	Motor_Init();
	HW_Init();
	OLED_Init();
	PID_Init();
	
	OLED_Clear();
	
	MPU_Init();			//MPU6050初始化
	
	while(mpu_dmp_init())
	{
		OLED_ShowString(2 , 2 , "MPU6050 error:",16);
		delay_ms(200);
		OLED_Clear();
		delay_ms(200);
	}
	TIM5_Int_Init(99 , 7199);	//10ms
	
	while(1)
	{		
		OLED_ShowString(2 , 1 , "kp:",12);
		OLED_ShowNumber(50, 1, pidMotorSpeed.kp, 3, 12);
		OLED_ShowString(2 , 2 , "kd:",12);
		OLED_ShowNumber(50, 2, pidMotorSpeed.kd, 3, 12);
		OLED_ShowString(2 , 3 , "ki:",12);
		OLED_Float(50, 3, pidMotorSpeed.ki, 1);
		OLED_ShowString(2 , 4 , "sp:",12);
		OLED_Num4(50, 4, speed);
		
		OLED_ShowString(2 , 6 , "yaw:",12);
		OLED_Float(50, 6, yaw, 1);
		
		OLED_Num2(50, 7, err);
	}		 
}
