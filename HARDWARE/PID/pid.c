#include "pid.h"

//定义一个结构体类型变量
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

//比例p调节控制函数
float P_realize(tpid *pid , float actual_val)
{
	pid->actual_val = actual_val;	//传递真实值
	pid->err = pid->target_val - pid->actual_val;//当前误差=目标值-真实值
	//比例控制调节	输出 = kp*当前误差
	pid->actual_val = pid->kp * pid->err;
	return pid->actual_val;
}

//比例P 积分I 控制函数
float PI_realize(tpid *pid , float actual_val)
{
	pid->actual_val = actual_val;//传递真实函数
	pid->err = pid->target_val - pid->actual_val;//当前误差=目标值-真实值
	pid->err_sum += pid->err;//累计误差 = 当前误差累计和
	//PI控制 输出 = Kp*当前误差 + Ki*累计误差
	pid->actual_val = pid->kp * pid->err + pid->ki * pid->err_sum;
	
	return pid->actual_val;
}

//PID控制函数
float PID_realize(tpid *pid , float actual_val)			//Target：0  actual_val = -2
{
	pid->actual_val = actual_val;
	pid->err = pid->target_val - pid->actual_val;//当前误差=目标值-真实值		//2
	pid->err_sum += pid->err;//累计误差 = 当前误差累计和
	//PID控制 输出 = Kp*当前误差 + Ki*累计误差值 + Kd*（当前误差 - 上次误差）
	pid->actual_val = pid->kp * pid->err + pid->ki * pid->err_sum + pid->kd * (pid->err - pid->err_last);
	//保存上次偏差：这次偏差赋值给上次偏差
	pid->err_last = pid->err;
	
	return pid->actual_val;
	
}

int Position_PID (int Encoder,int Target)   //差速PID控制器//这里Encoder=error，Target=0;
{ 	
	 static float Bias,Pwm,Integral_bias,Last_Bias;
	 Bias=Encoder-Target;                                  //计算偏差
	 Integral_bias+=Bias;	                                 //求出偏差的积分
	 Pwm=pidMPU6050YawMovement.kp*Bias+pidMPU6050YawMovement.ki*Integral_bias+pidMotorSpeed.kd*(Bias-Last_Bias);       //位置式PID控制器
	 Last_Bias=Bias;                                       //保存上一次偏差 
	 return Pwm;                                           //返回PWM值
}

/*
转向环：系数 * Z轴角速度
*/
int Vertical_Turn_PD(int gyro_Z, int RC)
{
    int PWM_out;
	
	PWM_out=Turn_Kd * gyro_Z + Turn_Kp * RC;
	return PWM_out;
}


