#ifndef _PID_H
#define _PID_H

#include "sys.h"

typedef struct
{
	float target_val;	//Ŀ��ֵ
	float actual_val;	//ʵ��ֵ
	float err;			//��ǰƫ��
	float err_last;		//�ϴ�ƫ��
	float err_sum;		//����ۼ�ֵ
	float kp , ki , kd;	//���������֡�΢��ϵ��
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
