#ifndef _TIMER_H
#define _TIMER_H

#include "sys.h"
#include "motor.h"
#include "control.h"
#include "pwm.h"
#include "oled.h"
#include "pid.h"
#include "encoder.h"
#include "inv_mpu.h"
#include "delay.h"

void TIM5_Int_Init(u16 arr,u16 psc);

extern float pitch , roll , yaw;
extern short accx , accy , accz;
extern short gyrox , gyroy , gyroz;
extern short Encoder_Left , Encoder_Right;
extern int MOTO1 , MOTO2;
extern float Med_Angle;
extern int8_t g_ThisState , g_LastState;
extern int16_t speed;
extern int flag;

#endif
