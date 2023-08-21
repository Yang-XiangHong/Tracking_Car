#include "motor.h"
#include "oled.h"

/*电机初始化函数*/
void Motor_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB , &GPIO_InitStruct);
}

void Car_Forward(void)
{
	AIN1 = 1;
	AIN2 = 0;
	BIN1 = 0;
	BIN2 = 1;
}

void Car_Stop(void)
{
	AIN1 = 0;
	AIN2 = 0;
	BIN1 = 0;
	BIN2 = 0;
}
