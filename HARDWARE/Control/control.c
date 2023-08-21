#include "control.h"

int8_t last_err = 0;
extern int8_t err;
extern int16_t out1 , out2 , speed , PID_value;
extern int temp;

extern int g_read_value[5];

void Sensor_Init(void)
{
	g_read_value[0] = READ_HW_1;
	g_read_value[1] = READ_HW_2;
	g_read_value[2] = READ_HW_3;
	g_read_value[3] = READ_HW_4;
	g_read_value[4] = READ_HW_5;
	if(g_read_value[0]==0&&g_read_value[1]==0&&g_read_value[2]==1&&g_read_value[3]==0&&g_read_value[4]==0)
	{
		err = 0; //1500
	}
	else if(g_read_value[0]==0&&g_read_value[1]==1&&g_read_value[2]==0&&g_read_value[3]==0&&g_read_value[4]==0)
	{
		err = 1; //1500  2000
	}
	else if(g_read_value[0]==1&&g_read_value[1]==0&&g_read_value[2]==0&&g_read_value[3]==0&&g_read_value[4]==0)
	{
		err = 2;	//1500 2500
		flag = 2;
	}
	else if(g_read_value[0]==0&&g_read_value[1]==0&&g_read_value[2]==0&&g_read_value[3]==1&&g_read_value[4]==0)
	{
		err = -1;
	}
	else if(g_read_value[0]==0&&g_read_value[1]==0&&g_read_value[2]==0&&g_read_value[3]==0&&g_read_value[4]==1)
	{
		err = -2;
		flag = 3;
	}
}

void xun_ji(void)
{
	PID_value = PID_realize(&pidMotorSpeed, err);
	
	out1 = speed + PID_value;
	out2 = speed - PID_value;

	if(out1 >5000)	//�޷�
		out1 = 5000;
	if(out1 < 0 )
		out1 = 0;
	if(out2 >5000)
		out1 = 5000;
	if(out2 < 0 )
		out1 = 0;

	if(err != last_err)
	{
		TIM_SetCompare1(TIM1,out1);
		TIM_SetCompare4(TIM1,out2);
	}
	last_err = err;
}

void Turn_Angle(void)
{
	g_fmpu6050YawMovePidOut = PID_realize(&pidMPU6050YawMovement , yaw);
		
	g_fmpu6050YawMovePidOut1 = 2000 + g_fmpu6050YawMovePidOut;	//�ٶȲ�
	g_fmpu6050YawMovePidOut2 = 2000 - g_fmpu6050YawMovePidOut;
	
	if(g_fmpu6050YawMovePidOut1 > 3000)		//�޷�
		g_fmpu6050YawMovePidOut1 = 3000;
	if(g_fmpu6050YawMovePidOut1 < 0)
		g_fmpu6050YawMovePidOut1 = 0;
	if(g_fmpu6050YawMovePidOut2 > 3000)
		g_fmpu6050YawMovePidOut2 = 3000;
	if(g_fmpu6050YawMovePidOut2 < 0)
		g_fmpu6050YawMovePidOut2 = 0;
	TIM_SetCompare1(TIM1,g_fmpu6050YawMovePidOut2);
	TIM_SetCompare4(TIM1,g_fmpu6050YawMovePidOut1);
}

/**************************************************************************
函数功能：增量PI控制器
入口参数：编码器测量值，目标速度
返回  值：电机PWM
根据增量式离散PID公式 
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
pwm代表增量输出
在我们的速度控制闭环系统里面，只使用PI控制
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI (int Encoder,int Target)
{ 	
     float Kp=20,Ki=30;	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //计算偏差
	 Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //增量式PI控制器
	 Last_bias=Bias;	                 //保存上一次偏差 
	 return Pwm;                         //增量输出
}


