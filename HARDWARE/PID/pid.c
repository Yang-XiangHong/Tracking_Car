#include "pid.h"

//����һ���ṹ�����ͱ���
tpid pidMotorSpeed;
tpid pidMPU6050YawMovement;

float g_fmpu6050YawMovePidOut = 0.00f;
float g_fmpu6050YawMovePidOut1 = 0.00f;
float g_fmpu6050YawMovePidOut2 = 0.00f;

int Turn_Kd , Turn_Kp;

void PID_Init(void)
{
	pidMotorSpeed.actual_val = 0.0;
	pidMotorSpeed.target_val = 0.00;
	pidMotorSpeed.err = 0.0;
	pidMotorSpeed.err_last = 0.0;
	pidMotorSpeed.err_sum = 0.0;
	pidMotorSpeed.kp = 300;
	pidMotorSpeed.ki = 0;
	pidMotorSpeed.kd = 300;
	
	pidMPU6050YawMovement.actual_val = 0.0;
	pidMPU6050YawMovement.target_val = 0.0;
	pidMPU6050YawMovement.err = 0.0;
	pidMPU6050YawMovement.err_last = 0.0;
	pidMPU6050YawMovement.err_sum = 0.0;
	pidMPU6050YawMovement.kp = 50;
	pidMPU6050YawMovement.ki = 0;
	pidMPU6050YawMovement.kd = 0;
}

//����p���ڿ��ƺ���
float P_realize(tpid *pid , float actual_val)
{
	pid->actual_val = actual_val;	//������ʵֵ
	pid->err = pid->target_val - pid->actual_val;//��ǰ���=Ŀ��ֵ-��ʵֵ
	//�������Ƶ���	��� = kp*��ǰ���
	pid->actual_val = pid->kp * pid->err;
	return pid->actual_val;
}

//����P ����I ���ƺ���
float PI_realize(tpid *pid , float actual_val)
{
	pid->actual_val = actual_val;//������ʵ����
	pid->err = pid->target_val - pid->actual_val;//��ǰ���=Ŀ��ֵ-��ʵֵ
	pid->err_sum += pid->err;//�ۼ���� = ��ǰ����ۼƺ�
	//PI���� ��� = Kp*��ǰ��� + Ki*�ۼ����
	pid->actual_val = pid->kp * pid->err + pid->ki * pid->err_sum;
	
	return pid->actual_val;
}

//PID���ƺ���
float PID_realize(tpid *pid , float actual_val)			//Target��0  actual_val = -2
{
	pid->actual_val = actual_val;
	pid->err = pid->target_val - pid->actual_val;//��ǰ���=Ŀ��ֵ-��ʵֵ		//2
	pid->err_sum += pid->err;//�ۼ���� = ��ǰ����ۼƺ�
	//PID���� ��� = Kp*��ǰ��� + Ki*�ۼ����ֵ + Kd*����ǰ��� - �ϴ���
	pid->actual_val = pid->kp * pid->err + pid->ki * pid->err_sum + pid->kd * (pid->err - pid->err_last);
	//�����ϴ�ƫ����ƫ�ֵ���ϴ�ƫ��
	pid->err_last = pid->err;
	
	return pid->actual_val;
	
}

int Position_PID (int Encoder,int Target)   //����PID������//����Encoder=error��Target=0;
{ 	
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //����ƫ��
	 Integral_bias+=Bias;	                                 //���ƫ��Ļ���
	 Pwm=pidMPU6050YawMovement.kp*Bias+pidMPU6050YawMovement.ki*Integral_bias+pidMotorSpeed.kd*(Bias-Last_Bias);       //λ��ʽPID������
	 Last_Bias=Bias;                                       //������һ��ƫ�� 
	 return Pwm;                                           //����PWMֵ
}

/*
ת�򻷣�ϵ�� * Z����ٶ�
*/
int Vertical_Turn_PD(int gyro_Z, int RC)
{
    int PWM_out;
	
	PWM_out=Turn_Kd * gyro_Z + Turn_Kp * RC;
	return PWM_out;
}


