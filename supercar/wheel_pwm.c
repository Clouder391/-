#include "wheel_pwm.h"

/* PWM�������ֵ */
#define MOTOR_SPEED_MAX 10000

///**********************************************************************************************************
//*�� �� ��: motor_set_speed
//*����˵��: ��pwm_pluse��ֵ��motor�ṹ���е�speed ������ͨ��ע�붯��
//*��    ��: motor�ṹ��ĵ�ַ   ����
//*�� �� ֵ: ��
//*��    ע: Ϊ��Ӧusmart������ڲ�������Ϊ  ������  ����( 8.1 �޸� ��
//				   Ϊ��Ӧʮ�ֽ���ȫ���ֲ��֣����ж� 
//**********************************************************************************************************/
//void set_motor_speed(uint16_t num, int32_t speed)
//{
//    int32_t ccr = 0;
//		motor_t* motor;
//		if(num == 1)
//			motor = &motor1;
//		else if(num == 2)
//			motor  = &motor2;
//		else if(num == 3)
//			motor = &motor3;
//		else 
//			motor = &motor4;
//	
//		if(num==1||num==2)
//		{
//    if (speed >= 0)
//    {
//        if (speed > MOTOR_SPEED_MAX)
//            ccr = MOTOR_SPEED_MAX;
//        else
//            ccr = speed;

//        motor->speed = ccr;

//        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_A, motor->speed);
//        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_B, 0);
//    }

//    else if (speed < 0)
//    {
//        if (speed < -MOTOR_SPEED_MAX)
//            ccr = MOTOR_SPEED_MAX;
//        else
//            ccr = -speed;

//        motor->speed = ccr;

//        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_B, motor->speed);
//        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_A, 0);
//    }
//		}
//		
//		if(num==3||num==4)
//		{
//    if (speed >= 0)
//    {
//        if (speed > MOTOR_SPEED_MAX)
//            ccr = MOTOR_SPEED_MAX;
//        else
//            ccr = speed;

//        motor->speed = ccr;

//        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_B, motor->speed);
//        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_A, 0);
//    }

//    else if (speed < 0)
//    {
//        if (speed < -MOTOR_SPEED_MAX)
//            ccr = MOTOR_SPEED_MAX;
//        else
//            ccr = -speed;

//        motor->speed = ccr;

//        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_A, motor->speed);
//        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_B, 0);
//    }
//		}
//}

/**********************************************************************************************************
*�� �� ��: motor_set_speed
*����˵��: ��pwm_pluse��ֵ��motor�ṹ���е�speed ������ͨ��ע�붯��
*��    ��: motor�ṹ��ĵ�ַ   ����
*�� �� ֵ: ��
**********************************************************************************************************/
void set_motor_speed(motor_t *motor, int32_t speed)
{
    int32_t ccr = 0;

    if (speed >= 0)
    {
        if (speed > MOTOR_SPEED_MAX)
            ccr = MOTOR_SPEED_MAX;
        else
            ccr = speed;

        motor->speed = ccr;

        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_A, motor->speed);
        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_B, 0);
    }

    else if (speed < 0)
    {
        if (speed < -MOTOR_SPEED_MAX)
            ccr = MOTOR_SPEED_MAX;
        else
            ccr = -speed;

        motor->speed = ccr;

        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_B, motor->speed);
        __HAL_TIM_SET_COMPARE(motor->htim_pwm, motor->channel_A, 0);
    }
}

