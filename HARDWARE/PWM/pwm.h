#ifndef _PWM_H
#define _PWM_H

#include "sys.h"

void PWM_Init_TIM1(uint16_t arr , uint16_t psc);
void Set_Pwm(uint16_t left , uint16_t right);

#endif
