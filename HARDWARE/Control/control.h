#ifndef _CONTROL_H
#define _CONTROL_H

#include "sys.h"
#include "led.h"
#include "pid.h"
#include "pwm.h"
#include "delay.h"

void Sensor_Init(void);
void xun_ji(void);
void Turn_Angle(void);
int Incremental_PI (int Encoder,int Target);

extern float yaw;
extern int flag;;

#endif
