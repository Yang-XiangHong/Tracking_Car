#ifndef _MOTOR_H
#define _MOTOR_H

#include "sys.h"
#include "stm32f10x_tim.h"

#define AIN1 PBout(13)
#define AIN2 PBout(12)
#define BIN1 PBout(14)
#define BIN2 PBout(15)

void Motor_Init(void);
void Car_Forward(void);
void Car_Stop(void);


extern int MOTO1 , MOTO2;

#endif
