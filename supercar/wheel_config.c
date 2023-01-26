#include "wheel_config.h"
#include "wheel.h"

/* �������������� */
motor_t motor1;
motor_t motor2;
motor_t motor3;
motor_t motor4;
uint16_t val;
//������������ʱ������˳ʱ��תΪ��ת��A��Ϊ0��ת��
extern double motor_target[5];

	/**********************************************************************************************************
*�� �� ��: set_motor1val
*����˵��: ����ĳ��ʱ����ĳ��ͨ����ռ�ձ�
*��    ��: ռ�ձȴ�С
*�� �� ֵ: ��
*��    ע: Ϊ����usmartд�ĺ�������С����ʻ��������ʵ��Ӧ��
**********************************************************************************************************/
void set_motor1val(uint16_t val)
{
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,val);
}


	/**********************************************************************************************************
*�� �� ��: set_motor
*����˵��: ����ĳ�������Ŀ���ٶ�ֵ
*��    ��: Ŀ���ٶ�ֵ�Ĵ�С
*�� �� ֵ: ��
*��    ע: Ϊ��������pidд��������usmart�ĺ�������С����ʻ��������ʵ������
**********************************************************************************************************/
void set_motor(uint16_t speed)
{
	motor_target[1]=speed;
}


	/**********************************************************************************************************
*�� �� ��: motor1_Enable
*����˵��: ��ʼ��motor1�ṹ�� ��ʹ�����Ӧʱ�����ж�
*��    ��: motor�ṹ��ĵ�ַ
*�� �� ֵ: ��
**********************************************************************************************************/
void motor1_Enable(motor_t *motor)
{
    motor->htim_pwm = &htim1;
    motor->channel_A = TIM_CHANNEL_2;
    motor->channel_B = TIM_CHANNEL_1;
    motor->speed = 0;

    motor->htim_ic = &htim5;
    motor->ic_channel = TIM_CHANNEL_1;
    motor->IC_GPIO_Port_v = MOTOR3_ENCODER_GPIO_Port;
    motor->IC_Pin_v = MOTOR3_ENCODER_Pin;

    motor->updata = 0;
    motor->freq = 0 ;

    HAL_TIM_PWM_Start(motor->htim_pwm, motor->channel_A);
    HAL_TIM_PWM_Start(motor->htim_pwm, motor->channel_B);
    HAL_TIM_IC_Start_IT(motor->htim_ic, motor->ic_channel);
}


/**********************************************************************************************************
*�� �� ��: motor2_Enable
*����˵��: ��ʼ��motor2�ṹ�� ��ʹ�����Ӧʱ�����ж�
*��    ��: motor�ṹ��ĵ�ַ
*�� �� ֵ: ��
**********************************************************************************************************/

void motor2_Enable(motor_t *motor)
{
    motor->htim_pwm = &htim1;
    motor->channel_A = TIM_CHANNEL_3;
    motor->channel_B = TIM_CHANNEL_4;
    motor->speed = 0;

    motor->htim_ic = &htim5;
    motor->ic_channel = TIM_CHANNEL_3;
    motor->IC_GPIO_Port_v = MOTOR4_ENCODER_GPIO_Port;
    motor->IC_Pin_v = MOTOR4_ENCODER_Pin;

    motor->updata = 0;
    motor->freq = 0;

    HAL_TIM_PWM_Start(motor->htim_pwm, motor->channel_A);
    HAL_TIM_PWM_Start(motor->htim_pwm, motor->channel_B);
    HAL_TIM_IC_Start_IT(motor->htim_ic, motor->ic_channel);
}

/**********************************************************************************************************
*�� �� ��: motor3_Enable
*����˵��: ��ʼ��motor2�ṹ�� ��ʹ�����Ӧʱ�����ж�
*��    ��: motor�ṹ��ĵ�ַ
*�� �� ֵ: ��
**********************************************************************************************************/
void motor3_Enable(motor_t *motor)
{
    motor->htim_pwm = &htim2;
    motor->channel_A = TIM_CHANNEL_4;
    motor->channel_B = TIM_CHANNEL_3;
    motor->speed = 0;

    motor->htim_ic = &htim3;
    motor->ic_channel = TIM_CHANNEL_1;
    motor->IC_GPIO_Port_v = MOTOR1_ENCODER_GPIO_Port;
    motor->IC_Pin_v = MOTOR1_ENCODER_Pin;

    motor->updata = 0;
    motor->freq = 0;

    HAL_TIM_PWM_Start(motor->htim_pwm, motor->channel_A);
    HAL_TIM_PWM_Start(motor->htim_pwm, motor->channel_B);
    HAL_TIM_IC_Start_IT(motor->htim_ic, motor->ic_channel);
}

/**********************************************************************************************************
*�� �� ��: motor4_Enable
*����˵��: ��ʼ��motor2�ṹ�� ��ʹ�����Ӧʱ�����ж�
*��    ��: motor�ṹ��ĵ�ַ
*�� �� ֵ: ��
**********************************************************************************************************/
void motor4_Enable(motor_t *motor)
{
    motor->htim_pwm = &htim2;
    motor->channel_A = TIM_CHANNEL_1;
    motor->channel_B = TIM_CHANNEL_2;
    motor->speed = 0;

    motor->htim_ic = &htim3;
    motor->ic_channel = TIM_CHANNEL_3;
    motor->IC_GPIO_Port_v = MOTOR2_ENCODER_GPIO_Port;
    motor->IC_Pin_v = MOTOR2_ENCODER_Pin;

    motor->updata = 0;
    motor->freq = 0;

    HAL_TIM_PWM_Start(motor->htim_pwm, motor->channel_A);
    HAL_TIM_PWM_Start(motor->htim_pwm, motor->channel_B);
    HAL_TIM_IC_Start_IT(motor->htim_ic, motor->ic_channel);
}

void car_go(void)
{
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,0);//1�ַ�ת
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_3,0);//2����ת
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,0);//4�ַ�ת
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,0);//3����ת
	
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,0);
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_4,0);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,0);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_4,0);

}

void car_left(void)
{
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,2000);//1����ת
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_3,0);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,0);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,2000);//3�ַ�ת
	
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,0);
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_4,2000);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,2000);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_4,0);

}

void car_rightback(void)
{
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,0);
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_3,0);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,0);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,0);
	
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,2000);//1�ַ�ת
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_4,2000);//2�ַ�ת
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,2100);//3����ת
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_4,2000);//4����ת

}

void car_turn(void)
{
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,2000);//1����ת
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_3,2000);//2����ת
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,0);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,0);
	
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,0);
	__HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_4,0);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_2,2100);//3����ת
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_4,2000);//4����ת

}


