#include "turn_task.h"
#include "usart.h"
#include "time_delay.h"
#include "stdio.h"
#include "lsc.h"

/*����ż��*/
#define photogate HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4)
//#define photogate_right HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_1)

extern int waittime;

/*�Ƿ����ת����־λ*/
bool span_flag = true;

/**********************************************************************
  * ��������span
  * ����: Բ��ת������Ӧ��ſ�λ
  * ��������  λ    
  * ����ֵ:��
***********************************************************************/
void span(int store_id)
{
  static int zm_now = 0;
	int zm_count,zm_dir;
	//-----------------------------
	if(span_flag && zm_now == 0 && store_id == 0)
	{
		span_flag = false;
		Set_Steering_anticlockwise(&turnover_steering);
		while((photogate== 0));
		Set_Steering_stop(&turnover_steering);
		return;
	}//��ʼ��span(0)������Խ��
	//-----------------------------
	zm_count = store_id - zm_now;	
//	if(zm_count > 6) zm_count -= 12;
//	else if(zm_count < -6) zm_count += 12;
	zm_dir = zm_count > 0? 1:-1;
	zm_now += zm_count;
	if(zm_now >= 10)  zm_now -= 10;
	else if(zm_now < 0)	zm_now += 10;
	if(zm_dir == 1)	Set_Steering_anticlockwise(&turnover_steering);     //pan = TIM->CCR1 //���ƶ�����ٶ�  90  210
	else 	Set_Steering_clockwise(&turnover_steering);
	if( (photogate== 1))zm_count += zm_dir;    //photo �Ǻ��������  &&->||
	//if(photo1 == 1 )zm_count += zm_dir;
	while(zm_count != 0)
	{
    
		if((photogate == 1))
		{
			//PGout(15) = 0;
			zm_count -= zm_dir;
			printf("%d\n",zm_count);
			if(zm_count == 0)	{
				 Set_Steering_stop(&turnover_steering);
			   return;
		  }	//���
		delay_ms(400);
		}
	}
}

void span_find_zero(void)
{
	waittime = 100;
	Set_Steering_clockwise(&turnover_steering);
	while(1)
	{
		
		if(photogate == 1)
		{
			waittime = 100;
		}
		if(waittime == 0)break;
	}
	Set_Steering_stop(&turnover_steering);
	delay_ms(300);
	while(1)
	{
		Set_Steering_anticlockwise(&turnover_steering);
		if(photogate == 1)break;
	}
	Set_Steering_stop(&turnover_steering);
}

void span_init(void)
{
	cmd_action_group_run(0x00,1);
	delay_ms(1500);
	span_find_zero();
	span(0);
}

void span_find_flag(void)
{
	waittime = 40;
	Set_Steering_clockwise(&turnover_steering);
	while(1)
	{
		if(waittime == 0)break;
	}
	Set_Steering_stop(&turnover_steering);
	delay_ms(200);
	while(1)
	{
		Set_Steering_anticlockwise(&turnover_steering);
		if(photogate == 1)break;
	}
	Set_Steering_stop(&turnover_steering);
}

