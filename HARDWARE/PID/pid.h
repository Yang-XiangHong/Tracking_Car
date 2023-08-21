#ifndef _PID_H
#define _PID_H

#include "sys.h"

typedef struct
{
	float target_val;	//目标值
	float actual_val;	//实际值
	float err;			//当前偏差
	float err_last;		//上次偏差
	float err_sum;		//误差累计值
	float kp , ki , kd;	//比例、积分、微分系数
}tpid;

void PID_Init(void);
float P_realize(tpid *pid , float actual_val);
float PI_realize(tpid *pid , float actual_val);
float PID_realize(tpid *pid , float actual_val);
int Position_PID (int Encoder,int Target);

int Vertical_Turn_PD(int gyro_Z, int RC);

int Incremental_PID(int reality,int target);

extern tpid pidMotorSpeed;
extern tpid pidHW_Tracking;
extern tpid pidMPU6050YawMovement;
extern float kp , ki , kd;


extern float g_fmpu6050YawMovePidOut;
extern float g_fmpu6050YawMovePidOut1;
extern float g_fmpu6050YawMovePidOut2;

#endif
