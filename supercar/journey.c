#include "wheel.h"
#include "journey.h"
#include "bar.h"
#include "imu.h"
#include "imu_task.h"
#include "openmv.h"
#include "lsc.h"
#include "time_delay.h"
#include "m294.h"
#include "qrcode.h"
#include "snow.h"
#include "turn_task.h"
#include "stack_transfer.h"

extern ATTITUDE_t attitude;
extern uint32_t waittime;
extern QRCODE_t qrcode;
#define HEIGHT_1 1      //�߶�1
#define HEIGHT_2 2      //�߶�2
#define HEIGHT_3 3      //�߶�3

/*���߶��õĺ���*/
#define SENSOR HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)

/*����ƽ̨�С��͸߶�״̬�л���־λ*/
uint8_t flag = 0;

/*����ƽ̨ץȡ�߶ȱ�־λ*/
uint8_t height = 0; 

uint8_t red_bit = 0, blue_bit = 0;
/*С��IC���洢˳��*/
uint8_t IDLocation[12] = {0};

/*С�����ֿ�˳��*/
uint8_t putBallOrder[9] = {0x33,0x23,0x13,0x32,0x22,0x12,0x31,0x21,0x11};

void run_to_stairs_red(void)
{
/***********************ȫ���ְ汾**************************************
	set_chassis_speed(-20,0,0);
	 HAL_Delay(500);
	 set_chassis_speed(-50,0,0);
	 HAL_Delay(1800);
	 set_chassis_speed(0,100,0);
	 HAL_Delay(3500);//�ߵ�����ƽ̨ǰ��
**************************************************************************/
	set_chassis_speed(120,0,0);
	delay_ms(1200);
	set_chassis_speed(0,0,0);
	delay_ms(100);
	move_by_encoder(2,8000);
}

void run_to_stairs_blue(void)
{
/****************************************************************************
	 set_chassis_speed(-20,0,0);
	 HAL_Delay(500);
	 set_chassis_speed(-50,0,0);
	 HAL_Delay(1800);
	 set_chassis_speed(0,-100,0);
	 HAL_Delay(3500);//�ߵ�����ƽ̨ǰ��
*****************************************************************************/
	set_chassis_speed(120,0,0); 
	delay_ms(1200);
	set_chassis_speed(0,0,0);
	delay_ms(100);
	move_by_encoder(2,-8500);
}

void hit_bar_blue(void)
{
	set_imu_status(&attitude,false);
	while(1) 
	{
      set_chassis_speed(50, 0, 0);
      if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14) == 1&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 0) {
          set_chassis_speed(30, 0, -30 );
        }
        
      if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14) == 0&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 1) {
          set_chassis_speed(30, 0,  30);  
        }
      if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14) == 1&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 1)break;
			}
}

void hit_bar_red(void)
{
	set_imu_status(&attitude,false);
	while(1) 
	{
      set_chassis_speed(50, 0, 0);
      if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14) == 1&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 0) {
          set_chassis_speed(30, 0, -30 );
        }
        
      if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14) == 0&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 1) {
          set_chassis_speed(30, 0,  30);  
        }
      if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14) == 1&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 1)break;
	}
}

void move_to_bar_left_blue(void)
{
	while(1) 
	{
       set_chassis_speed(10, -50, 0);
       if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 0&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 1) break;
    }
	set_chassis_speed(0,0,0);
	HAL_Delay(200);
}

void leave_bar_blue(void)
{
	while(1)
	{
		set_chassis_speed(-30,0,0);
		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == 1 )break;
	}
	HAL_Delay(50);
	set_chassis_speed(0,0,0);
//	imu_calibration();
	set_imu_status(&attitude,true);
}

void move_to_bar_right_red(void)
{
	while(1) 
	{
       set_chassis_speed(10, -50, 0);
       if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 0&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 1) break;
    }
	set_chassis_speed(0,0,0);
	HAL_Delay(200);
}

void leave_bar_red(void)
{
	while(1)
	{
		set_chassis_speed(30,0,0);
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9) == 1 )break;
	}
	HAL_Delay(50);
	set_chassis_speed(0,0,0);
//	imu_calibration();
	set_imu_status(&attitude,true);
}

void run_to_cornucopia_red(void)
{
	
	while(1)
	{
		set_chassis_speed(0,30,0);
		read_rowbar();
		if(count_rowbar_message()>4 )break;
	}
	while(1)
	{
		set_chassis_speed(0,50,0);
		read_rowbar();
		if(count_rowbar_message()<3)break;
	}
	while(1)
	{
		set_chassis_speed(0,60,0);
		read_rowbar();
		if(count_rowbar_message()>4)break;
	}
	set_chassis_speed(0,0,0);
	delay_ms(2500);

//ʶ������ʮ�ֵķ������ڶ���ʮ������ʶ��׼
//	while(1)
//	{
//		set_chassis_speed(30,0,0);
//		read_rowbar();
//		if(count_rowbar_message()<3)break;
//	}
//	while(1)
//	{
//		set_chassis_speed(70,0,0);
//		read_rowbar();
//		if(count_rowbar_message()>4)break;
//	}
//	set_chassis_speed(0,0,0);
//	delay_ms(200);
	set_chassis_speed(30,0,0);
	delay_ms(1000);
	set_chassis_speed(70,0,0);
	delay_ms(2000);
	set_imu_status(&attitude,false);
  set_chassis_speed(0, 0, 50); 
	delay_ms(1750);
	set_chassis_speed(0,0,0);

//	while(1)
//	{
//		set_chassis_speed(0,15,0);
//		read_verticalbar();
//		if(count_verticalbar_message()<7)break;
//	}
}

void run_to_cornucopia_blue(void)
{
	while(1)
	{
		set_chassis_speed(0,30,0);
		read_rowbar();
		if(count_rowbar_message()>4 )break;
	}
	while(1)
	{
		set_chassis_speed(0,50,0);
		read_rowbar();
		if(count_rowbar_message()<3)break;
	}
	while(1)
	{
		set_chassis_speed(0,60,0);
		read_rowbar();
		if(count_rowbar_message()>4)break;
	}
	set_chassis_speed(0,0,0);
	delay_ms(2500);

//ʶ������ʮ�ֵķ������ڶ���ʮ������ʶ��׼
//	while(1)
//	{
//		set_chassis_speed(30,0,0);
//		read_rowbar();
//		if(count_rowbar_message()<3)break;
//	}
//	while(1)
//	{
//		set_chassis_speed(70,0,0);
//		read_rowbar();
//		if(count_rowbar_message()>4)break;
//	}
//	set_chassis_speed(0,0,0);
//	delay_ms(200);
	set_chassis_speed(-30,0,0);
	delay_ms(1000);
	set_chassis_speed(-70,0,0);
	delay_ms(2000);
	set_imu_status(&attitude,false);
  set_chassis_speed(0, 0, 50); 
	delay_ms(1750);
	set_chassis_speed(0,0,0);

	//	while(1)
//	{
//		set_chassis_speed(0,15,0);
//		read_verticalbar();
//		if(count_verticalbar_message()<7)break;
//	}
}

void avoid_object_red(void)
{
	set_chassis_speed(-80,0,0);
	delay_ms(800);
	set_chassis_speed(0,0,0);
	delay_ms(300);
	set_imu_status(&attitude,true);
	delay_ms(500);
	set_chassis_speed(0,150,0);
	delay_ms(2250);
	
	while(1)
	{
		set_chassis_speed(-50,0,0);
		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == 0||HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 0)break;
	}
		set_chassis_speed(0,0,0);
		delay_ms(100);
		set_chassis_speed(0,-90,0);
		delay_ms(800);
		set_chassis_speed(0,0,0);
		delay_ms(100);
		set_chassis_speed(-150,0,0);
		delay_ms(1300);
		set_chassis_speed(0,0,0);
		delay_ms(100);
		set_chassis_speed(0,90,0);
		delay_ms(1000);
		set_imu_status(&attitude,false);
		set_chassis_speed(0,0,80);
		delay_ms(1800);
}


void avoid_object_blue(void)
{
	delay_ms(300);
	set_chassis_speed(0,0,0);
	delay_ms(300);
	set_chassis_speed(-80,0,0);
	delay_ms(800);
	set_chassis_speed(0,0,0);
	delay_ms(300);
	set_imu_status(&attitude,true);
	delay_ms(500);
		
		set_chassis_speed(0,-150,0);
		delay_ms(3270);
		while(1)
		{
			set_chassis_speed(-50,0,0);
			if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == 0||HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 0)break;
		}
		set_chassis_speed(0,0,0);
		delay_ms(100);
		set_chassis_speed(0,90,0);
		delay_ms(800);
		set_chassis_speed(0,0,0);
		delay_ms(100);
		set_chassis_speed(-150,0,0);
		delay_ms(1200);
		delay_ms(100);
		set_chassis_speed(0,-90,0);
		delay_ms(1000);
		set_imu_status(&attitude,false);
		set_chassis_speed(0,0,80);
		delay_ms(1800);
}


//�ú����ܵ�ʱ�������ת�����Ժ��ƶ���Բ���м�
void move_to_cornucopia_center(void)
{
		hit_bar_red();
		while(1)
		{
			set_chassis_speed(0,-30,0);
			if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_15) == 0)break;
		}
		while(1)
		{
			set_chassis_speed(0,30,0);
			if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_15) == 1)break;
		}
}

void leave_cornucopia_red(void)
{
/***************************************************************************************
	//��ѭ�����뿪���е㲻׼
	while(1)
	{
		set_chassis_speed(15,0,0);
		read_verticalbar();
		if(count_verticalbar_message()>4)break;
	}
*****************************************************************************************/
	set_chassis_speed(50,0,0);
	HAL_Delay(300);
	set_chassis_speed(0,0,0);
	HAL_Delay(500);
}

void leave_cornucopia_blue(void)
{
/***************************************************************************************
	//��ѭ�����뿪���е㲻׼
	while(1)
	{
		set_chassis_speed(15,0,0);
		read_verticalbar();
		if(count_verticalbar_message()>4)break;
	}
*****************************************************************************************/
	set_chassis_speed(-50,0,0);
	HAL_Delay(300);
	set_chassis_speed(0,0,0);
	HAL_Delay(500);
}

void run_to_scores_red(void)
{
/***************************************************************************************************
	while(1)
		{
			set_chassis_speed(0,50,0);
			if((HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9) == 0&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_4) == 0))break;
		}
		HAL_Delay(800);
		while(1)
		{
			set_chassis_speed(0,50,0);
			if((HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9) == 1&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_4) == 1))break;
		}
		while(1)
		{
			set_chassis_speed(0,80,0);
			if((HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9) == 0&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_4) == 0))break;
		}
		set_chassis_speed(0,50,0);
		HAL_Delay(1000);
		set_chassis_speed(0,0,0);
*****************************************************************************************************/
	cmd_action_group_run(0x00,1);
	tell_openmv_to_loosen2();
	delay_ms(1500);
	set_chassis_speed(50,0,0);
	delay_ms(500);
	imu_calibration();
	delay_ms(500);
	set_chassis_speed(-50,0,0);
	delay_ms(1050);
	set_imu_status(&attitude,true);
	set_chassis_speed(0,0,0);
	delay_ms(500);
	move_by_encoder(2,5000);
	while(1)
	{
		set_chassis_speed(0,80,0);
		if((HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 0&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 0))break;
	}
	set_chassis_speed(0,80,0);
	HAL_Delay(1000);
	hit_bar_red();
	move_to_bar_right_red();
}

void run_to_scores_blue(void)
{
	while(1)
		{
			set_chassis_speed(0,50,0);
			if((HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9) == 0&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_4) == 0))break;
		}
		HAL_Delay(800);
		while(1)
		{
			set_chassis_speed(0,50,0);
			if((HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9) == 1&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_4) == 1))break;
		}
		while(1)
		{
			set_chassis_speed(0,80,0);
			if((HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9) == 0&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_4) == 0))break;
		}
		set_chassis_speed(0,50,0);
		HAL_Delay(1000);
}

void imu_reset(void)
{
	set_chassis_speed(-80,0,0);
	HAL_Delay(500);
	imu_calibration();
	set_chassis_speed(0,0,0);
	HAL_Delay(200);
}

void imu_reset_blue(void)
{
	set_chassis_speed(80,0,0);
	HAL_Delay(500);
	imu_calibration();
	set_chassis_speed(0,0,0);
	HAL_Delay(200);
}

void back_home_by_speed(void)
{
/*************************************************************************************************
	set_chassis_speed(0,0,0);
		HAL_Delay(200);
		set_chassis_speed(50,0,0);
		HAL_Delay(400);
		set_chassis_speed(0,0,0);
		HAL_Delay(500);
		set_imu_status(&attitude,true);
		HAL_Delay(500);
		while(1)
		{
			set_chassis_speed(0,50,0);
			if((HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9) == 1&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_4) == 1))break;
		}
		set_chassis_speed(0,30,0);
		HAL_Delay(800);
		set_chassis_speed(0,50,0);
		HAL_Delay(500);
		set_chassis_speed(0,80,0);
		HAL_Delay(2700);
		set_chassis_speed(0,0,0);
		HAL_Delay(1000);
************************************************************************************************/
	set_chassis_speed(-50,0,0);
	delay_ms(850);
	set_imu_status(&attitude,true);
	set_chassis_speed(0,0,0);
	delay_ms(500);
	while(1)
	{
		set_chassis_speed(0,80,0);
		if((HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 1&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 1))break;
	}
	set_chassis_speed(0,80,0);
	HAL_Delay(1500);
	set_chassis_speed(0,120,0);
	HAL_Delay(1650);
	set_chassis_speed(0,0,0);
	delay_ms(300);
//	set_chassis_speed(-80,0,0);
//	delay_ms(1550);
	while(1)
	 {
		set_chassis_speed(-50,0,0);
		read_rowbar();
		read_verticalbar();
		if(count_rowbar_message()>4&&count_verticalbar_message()>4)break;
	 }
	while(1)
	{
		set_chassis_speed(-50,0,0);
		read_rowbar();
		read_verticalbar();
		if(count_rowbar_message()<3&&count_verticalbar_message()<3)break;
	}
	while(1)
	{
		set_chassis_speed(50,0,0);
		read_rowbar();
		read_verticalbar();
		if(count_rowbar_message()>4&&count_verticalbar_message()>4)break;
	}
	set_chassis_speed(30,0,0);
	HAL_Delay(950);

	set_chassis_speed(0,0,0);
	delay_ms(300);
}

void back_home_by_speed_blue(void)
{
	set_chassis_speed(0,0,0);
		HAL_Delay(200);
		set_chassis_speed(-50,0,0);
		HAL_Delay(400);
		set_chassis_speed(0,0,0);
		HAL_Delay(500);
		set_imu_status(&attitude,true);
		HAL_Delay(500);
		while(1)
		{
			set_chassis_speed(0,50,0);
			if((HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == 1&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 1))break;
		}
		set_chassis_speed(0,30,0);
		HAL_Delay(500);
		set_chassis_speed(0,50,0);
		HAL_Delay(500);
		set_chassis_speed(0,80,0);
		HAL_Delay(3200);
		set_chassis_speed(0,0,0);
		HAL_Delay(1000);
}


void get_qrcode(void)
{
		qrcode.message = 0;
		int cnt = 0;
		uint8_t last_qrcode = 0;
		uint8_t message = 0;
		set_chassis_speed(5,10,0);//��ǰ��12�ٶ��ƶ�
		while(1){
			message = qrcode.message;
			if(message == 0x31 || message == 0x32 || message == 0x33) {
				if(message != last_qrcode){
					last_qrcode = message;
					if (cnt == 2) {
						putBallOrder[2] = message - 0x30 + 0x10;
					} else if (cnt == 1) {
						putBallOrder[5] = message - 0x30 + 0x10;
					} else if (cnt == 0) {
						putBallOrder[8] = message - 0x30 + 0x10;
					}
					cnt++;
					printf("%d",(int)message);
				}
			}
			if(cnt>2){
				if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 1&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 0){
				if (cnt != 3) {
					//û����
						putBallOrder[2] = 0x11;
						putBallOrder[5] = 0x12;
						putBallOrder[8] = 0x13;
					
				}
				set_chassis_speed(0,0,0);
				break;
				}	
			}
		}
}

void run_to_champion_red(void)
{ 
	set_imu_status(&attitude,true);


/************************************************************************************************/
/*ʹ��ǰ��ĺ��⣬���������ͣ����������ľ��벻������Ϊ����Ҫ��������룬���ܿ�����İ�̫��*/
//	while(1)
//	{
//		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == 0)break;
//	}

/*************************************************************************************************/
	while(1)
	 {
		set_chassis_speed(50,0,0);
		read_rowbar();
		read_verticalbar();
		if(count_rowbar_message()>4&&count_verticalbar_message()>4)break;
	 }
	while(1)
	{
		set_chassis_speed(50,0,0);
		read_rowbar();
		read_verticalbar();
		if(count_rowbar_message()<3&&count_verticalbar_message()<3)break;
	}
	while(1)
	{
		set_chassis_speed(-50,0,0);
		read_rowbar();
		read_verticalbar();
		if(count_rowbar_message()>4&&count_verticalbar_message()>4)break;
	}
	set_chassis_speed(-30,0,0);
	HAL_Delay(850);

/******************************************����****************************************************/
/***************************��������ʹ��ǰ��İ���ײ�������****************************************/
//	while(1) 
//	{
//      set_chassis_speed(0, 80, 0);
//      if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6) == 1&&HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5) == 0) {
//          set_chassis_speed(0, 15, -50);
//        }
//        
//      if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6) == 0&&HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5) == 1) {
//          set_chassis_speed(0, 15, 50);
//        }
//      if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6) == 1&&HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5) == 1)break;
//	}
//	while(1)
//	 {
//		set_chassis_speed(50,30,0);
//		read_rowbar();
//		read_verticalbar();
//		if(count_rowbar_message()>4&&count_verticalbar_message()>4)break;
//	 }
//	while(1)
//	{
//		set_chassis_speed(50,30,0);
//		read_rowbar();
//		read_verticalbar();
//		if(count_rowbar_message()<3&&count_verticalbar_message()<3)break;
//	}
//	while(1)
//	{
//		set_chassis_speed(-50,30  ,0);
//		read_rowbar();
//		read_verticalbar();
//		if(count_rowbar_message()>4&&count_verticalbar_message()>4)break;
//	}
//	set_chassis_speed(-30,0,0);
//	HAL_Delay(850);
/*ʹ��ǰ��İ���ʱ��һֱ����һ����������Ҫ����һ�ξ����ó���ȫ�ص���*/
//	set_chassis_speed(0,0,0);
//	HAL_Delay(200);
//	set_chassis_speed(0,30,0);
//	HAL_Delay(300);
/*******************************************************************/		

/********************************************************************/
/*ʹ��ǰ��ĺ���ʱ���Ͱ�һֱ��һ�ξ��룬����Ҫ����һ�ξ����ó���ȫ�ص���*/
//	set_chassis_speed(0,0,0);
//	HAL_Delay(200);
//	set_chassis_speed(0,30,0);
//	HAL_Delay(300);
/*******************************************************************/		 
}

void run_to_champion_blue(void)
{ 
	set_imu_status(&attitude,true);


/************************************************************************************************/
/*ʹ��ǰ��ĺ��⣬���������ͣ����������ľ��벻������Ϊ����Ҫ��������룬���ܿ�����İ�̫��*/
//	while(1)
//	{
//		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == 0)break;
//	}

/*************************************************************************************************/
	while(1)
	 {
		set_chassis_speed(-50,0,0);
		read_rowbar();
		read_verticalbar();
		if(count_rowbar_message()>4&&count_verticalbar_message()>4)break;
	 }
	while(1)
	{
		set_chassis_speed(-50,0,0);
		read_rowbar();
		read_verticalbar();
		if(count_rowbar_message()<3&&count_verticalbar_message()<3)break;
	}
	while(1)
	{
		set_chassis_speed(50,0,0);
		read_rowbar();
		read_verticalbar();
		if(count_rowbar_message()>4&&count_verticalbar_message()>4)break;
	}
	set_chassis_speed(30,0,0);
	HAL_Delay(850);

/******************************************����****************************************************/
/***************************��������ʹ��ǰ��İ���ײ�������****************************************/
//	while(1) 
//	{
//      set_chassis_speed(0, 80, 0);
//      if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6) == 1&&HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5) == 0) {
//          set_chassis_speed(0, 15, -50);
//        }
//        
//      if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6) == 0&&HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5) == 1) {
//          set_chassis_speed(0, 15, 50);
//        }
//      if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6) == 1&&HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5) == 1)break;
//	}
//	while(1)
//	 {
//		set_chassis_speed(50,30,0);
//		read_rowbar();
//		read_verticalbar();
//		if(count_rowbar_message()>4&&count_verticalbar_message()>4)break;
//	 }
//	while(1)
//	{
//		set_chassis_speed(50,30,0);
//		read_rowbar();
//		read_verticalbar();
//		if(count_rowbar_message()<3&&count_verticalbar_message()<3)break;
//	}
//	while(1)
//	{
//		set_chassis_speed(-50,30  ,0);
//		read_rowbar();
//		read_verticalbar();
//		if(count_rowbar_message()>4&&count_verticalbar_message()>4)break;
//	}
//	set_chassis_speed(-30,0,0);
//	HAL_Delay(850);
/*ʹ��ǰ��İ���ʱ��һֱ����һ����������Ҫ����һ�ξ����ó���ȫ�ص���*/
//	set_chassis_speed(0,0,0);
//	HAL_Delay(200);
//	set_chassis_speed(0,30,0);
//	HAL_Delay(300);
/*******************************************************************/		

/********************************************************************/
/*ʹ��ǰ��ĺ���ʱ���Ͱ�һֱ��һ�ξ��룬����Ҫ����һ�ξ����ó���ȫ�ص���*/
//	set_chassis_speed(0,0,0);
//	HAL_Delay(200);
//	set_chassis_speed(0,30,0);
//	HAL_Delay(300);
/*******************************************************************/		 
}

//�ӽ���ƽ̨�ĵ���������������ú�������ɱ��Ϻ�ת�䣬����Ӧ�ý�ײ��+�ú��������������
void rode_of_avoid(void)
{
		leave_bar_red();
		HAL_Delay(500);
		while(1)
	{
		set_chassis_speed(0,30,0);
		read_rowbar();
		if(count_rowbar_message()>4 )break;
	}
	while(1)
	{
		set_chassis_speed(0,50,0);
		read_rowbar();
		if(count_rowbar_message()<3)break;
	}
	while(1)
	{
		set_chassis_speed(0,60,0);
		read_rowbar();
		if(count_rowbar_message()>4)break;
	}
	set_chassis_speed(0,0,0);
	HAL_Delay(500);
	set_chassis_speed(50,0,0);
	while(1)
		{
			if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == 0||HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 0)break;
		}
		HAL_Delay(800);
		set_chassis_speed(0,0,0);
		HAL_Delay(500);
		set_chassis_speed(0,35,0);
		while(1)
		{
			if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == 0)break;
		}
		set_chassis_speed(50,0,0);
		HAL_Delay(3200);
		set_chassis_speed(0, 0, 50); 
		HAL_Delay(1750);
		set_chassis_speed(0,30,0);
		HAL_Delay(1000);
}

//��·��ֻ�ж�ܣ�����ײ�壬�ڼ�⵽�ϰ�������
void rode_of_avoid_key_red(void)
{
		while(1) 
		{
				set_chassis_speed(0, 80, 0);
				if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6) == 1&&HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5) == 0) {
					set_chassis_speed(0, 15, -50);
				}
        
				if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6) == 0&&HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5) == 1) {
					set_chassis_speed(0, 15,  50);
				}
				if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6) == 1&&HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5) == 1)break;
		}
		set_chassis_speed(0,20,0);
		HAL_Delay(500);
		while(1)
		{
			set_imu_status(&attitude,false);
			set_chassis_speed(0,-30,0);
			if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1) == 1)break;
		}
		while(1)
		{
			set_chassis_speed(20,0,0);
			if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == 0&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 0)break;
		}
		HAL_Delay(1500);
		while(1) 
		{
			set_imu_status(&attitude,false);
				set_chassis_speed(0, 80, 0);
				if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6) == 1&&HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5) == 0) {
					set_chassis_speed(0, 15, -50);
				}
        
				if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6) == 0&&HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5) == 1) {
					set_chassis_speed(0, 15, 50);
				}
				if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6) == 1&&HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5) == 1)break;
		}
		set_chassis_speed(30,15,0);
		HAL_Delay(500);
		set_chassis_speed(50,15,0);
		HAL_Delay(2300);
		while(1)
		{ 
			set_chassis_speed(0,-30,0);
			if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_1) == 1)break;
		}
		set_chassis_speed(0, 0, 50); 
		HAL_Delay(1750);
}

void Catch_Steppedplatform_red()
{
	openmv.message = 0x00;
    for(int i=0;i<2;i++) {
        servogroup_Stepped_distinguish();
        
			  delay_ms(1000);
        tell_openmv_to_distinguish_Stepped();
				tell_openmv_to_distinguish_Stepped();
				tell_openmv_to_distinguish_Stepped();
				tell_openmv_to_distinguish_Stepped();
				tell_openmv_to_distinguish_Stepped();     //����openmv��е���Ѿ�̧��
        
        while(1) {
						if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 0&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 1) goto baohu_stepped;
					
            set_chassis_speed(15,20,0);
						if(SENSOR == 0) flag = 1;       //˵�������������Ѿ���������߽���
            //Get_openmv(&openmv);
            if(openmv.message == 0x01) break;
        }
				openmv.message = 0;
					if(SENSOR == 1&&flag == 0){
            height = HEIGHT_2;    
        }
        
        else if(SENSOR == 0) {
            height = HEIGHT_1;
        }   
        
        else if(SENSOR == 1&&flag == 1) {
            height = HEIGHT_3;
        }
				switch(height){
					case HEIGHT_1:
						delay_ms(200);break;
					case HEIGHT_2:
						delay_ms(320);break;
					case HEIGHT_3:
						delay_ms(450);break;
				}
				
        set_chassis_speed(0,0,0);

        switch(height){
            case HEIGHT_1:
                servogroup_catch_Steppedplatform_1();delay_ms(800);break;
            case HEIGHT_2:
                servogroup_catch_Steppedplatform_2();delay_ms(800);break;
            case HEIGHT_3:
                servogroup_catch_Steppedplatform_3();delay_ms(800);break;
        }
        tell_claw_to_catch();
				HAL_Delay(500);
        switch(height){
            case HEIGHT_1:
								cmd_action_group_speed(0x05,150);
                cmd_action_group_run(0x05,1);delay_ms(1500);break;
            case HEIGHT_2:
								cmd_action_group_speed(0x06,150);
                cmd_action_group_run(0x06,1);delay_ms(1500);break;
            case HEIGHT_3:
								cmd_action_group_speed(0x07,150);
                cmd_action_group_run(0x07,1);delay_ms(2200);break;
        }
				tell_openmv_to_loosen3();
				delay_ms(500);
				int ballid=0;
				waittime = 300;
				while(1)
				{
					if(ReadBlockData(ballID) == STATUS_OK)break;
					if (waittime == 0) break;
				}
				if(waittime == 0) continue;
				printf("nb666\n");
				ballid=(int)ballID[1]; 
				printf("%d",ballid);
				tell_claw_to_catch();
				HAL_Delay(500);
				//delay_ms(2000);
				//HAL_Delay(2000);
				//tell_claw_to_catch();
				//HAL_Delay(500);
        switch(ballid)
				{
            case 49:
								cmd_action_group_speed(0x08,175);
                cmd_action_group_run(0x08,1);
                delay_ms(1200);
								tell_openmv_to_loosen2();
								delay_ms(500);
                break;
            case 33:
								cmd_action_group_speed(0x09,175);
                cmd_action_group_run(0x09,1);
                delay_ms(1200);
								tell_openmv_to_loosen2();
								delay_ms(500);
                break;
						case 17:
								cmd_action_group_speed(0x0A,175);
                cmd_action_group_run(0x0A,1);
                delay_ms(1200);
								tell_openmv_to_loosen2();
								delay_ms(500);
                break;
						case 50:
								cmd_action_group_speed(0x0B,175);
                cmd_action_group_run(0x0B,1);
                delay_ms(1200);
								tell_openmv_to_loosen2();
								delay_ms(500);
                break;
						case 34:
								cmd_action_group_speed(0x0C,175);
                cmd_action_group_run(0x0C,1);
                delay_ms(1200);
								tell_openmv_to_loosen2();
								delay_ms(500);
                break;
						case 18:
								cmd_action_group_speed(0x0D,175);
                cmd_action_group_run(0x0D,1);
                delay_ms(1200);
								tell_openmv_to_loosen2();
								delay_ms(500);
                break;
						case 51:
								cmd_action_group_speed(0x0E,175);
                cmd_action_group_run(0x0E,1);
                delay_ms(1200);
								tell_openmv_to_loosen2();
								delay_ms(500);
                break;
						case 35:
								cmd_action_group_speed(0x0F,175);
                cmd_action_group_run(0x0F,1);
                delay_ms(1200);
								tell_openmv_to_loosen2();
								delay_ms(500);
                break;
						case 19:
								cmd_action_group_speed(0x10,100);
                cmd_action_group_run(0x10,1);
                delay_ms(1800);
								tell_openmv_to_loosen2();
								delay_ms(500);
                break;
					}
//					tell_openmv_to_loosen2();//�ɿ�צ��
//					delay_ms(1000);	//��������ֵ�bug�����ɿ�
					if(ballid == 35||ballid == 18||ballid == 50||ballid == 33)
					{
						switch(ballid)
						{
						case 35:
							cmd_action_group_speed(0x11,175);
							cmd_action_group_run(0x11,1);
              delay_ms(800);
              break;
						case 18:
							cmd_action_group_speed(0x12,175);
							cmd_action_group_run(0x12,1);
              delay_ms(800);
              break;
						case 50:
							cmd_action_group_speed(0x13,175);
							cmd_action_group_run(0x13,1);
              delay_ms(800);
              break;
						case 33:
							cmd_action_group_speed(0x14,175);
							cmd_action_group_run(0x14,1);
              delay_ms(800);
              break;
						}
					}
					if(ballid == 49||ballid == 17||ballid == 34||ballid == 51||ballid == 19)
				{
					switch(ballid)
						{
						case 49:
							cmd_action_group_speed(0x18,175);
							cmd_action_group_run(0x18,1);
              delay_ms(800);
              break;
						case 17:
							cmd_action_group_speed(0x19,175);
							cmd_action_group_run(0x19,1);
              delay_ms(800);
              break;
						case 34:
							cmd_action_group_speed(0x1A,175);
							cmd_action_group_run(0x1A,1);
              delay_ms(800);
              break;
						case 51:
							cmd_action_group_speed(0x1B,175);
							cmd_action_group_run(0x1B,1);
              delay_ms(800);
              break;
						case 19:
							cmd_action_group_speed(0x1C,175);
							cmd_action_group_run(0x1C,1);
              delay_ms(800);
              break;
						}
				}	 
				ballid = 0;
    }
	
baohu_stepped:
		/* ��ǰ��  ֱ��ƽ̨��Ե */
    while(1) {
        set_chassis_speed(-3, 50, 0);
        if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 0&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 1){
					set_chassis_speed(0, 0, 0);
					delay_ms(100);
					cmd_action_group_run(0x00,1);
					delay_ms(500);
					break;
				}
			} 
}

void Catch_Steppedplatform_blue()
{
	openmv.message = 0x00;
    for(int i=0;i<2;i++) {
        servogroup_Stepped_distinguish();
        
			  delay_ms(900);
        tell_openmv_to_distinguish_Stepped();
				tell_openmv_to_distinguish_Stepped();
				tell_openmv_to_distinguish_Stepped();
				tell_openmv_to_distinguish_Stepped();
				tell_openmv_to_distinguish_Stepped();     //����openmv��е���Ѿ�̧��
        
        while(1) {
						if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 0&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 1) goto baohu_stepped;
					
            set_chassis_speed(15,20,0);
						if(SENSOR == 0) flag = 1;       //˵�������������Ѿ���������߽���
            //Get_openmv(&openmv);
            if(openmv.message == 0x01) break;
        }
				openmv.message = 0;
					if(SENSOR == 1&&flag == 0){
            height = HEIGHT_2;    
        }
        
        else if(SENSOR == 0) {
            height = HEIGHT_1;
        }   
        
        else if(SENSOR == 1&&flag == 1) {
            height = HEIGHT_3;
        }
				switch(height){
					case HEIGHT_1:
						delay_ms(300);break;
					case HEIGHT_2:
						delay_ms(200);break;
					case HEIGHT_3:
						delay_ms(300);break;
				}
				
        set_chassis_speed(0,0,0);

        switch(height){
            case HEIGHT_1:
                servogroup_catch_Steppedplatform_5();delay_ms(800);break;
            case HEIGHT_2:
                servogroup_catch_Steppedplatform_4();delay_ms(800);break;
            case HEIGHT_3:
                servogroup_catch_Steppedplatform_6();delay_ms(800);break;
        }
        tell_claw_to_catch();
				HAL_Delay(200);
        switch(height){
            case HEIGHT_1:
								cmd_action_group_speed(0x05,150);
                cmd_action_group_run(0x05,1);delay_ms(1500);break;
            case HEIGHT_2:
								cmd_action_group_speed(0x34,150);
                cmd_action_group_run(0x34,1);delay_ms(1500);break;
            case HEIGHT_3:
								cmd_action_group_speed(0x07,150);
                cmd_action_group_run(0x07,1);delay_ms(2200);break;
        }
				tell_openmv_to_loosen3();
				delay_ms(200);
				int ballid=0;
				waittime = 300;
				while(1)
				{
					if(ReadBlockData(ballID) == STATUS_OK)break;
					if (waittime == 0) break;
				}
				if(waittime == 0) continue;
				printf("nb666\n");
				ballid=(int)ballID[1]; 
				printf("%d",ballid);
				tell_claw_to_catch();
				HAL_Delay(500);
				//delay_ms(2000);
				//HAL_Delay(2000);
				//tell_claw_to_catch();
				//HAL_Delay(500);
        switch(ballid)
				{
            case 49:
								cmd_action_group_speed(0x08,175);
                cmd_action_group_run(0x08,1);
                delay_ms(1200);
								tell_openmv_to_loosen2();
								delay_ms(300);
                break;
            case 33:
								cmd_action_group_speed(0x09,175);
                cmd_action_group_run(0x09,1);
                delay_ms(1200);
								tell_openmv_to_loosen2();
								delay_ms(300);
                break;
						case 17:
								cmd_action_group_speed(0x0A,175);
                cmd_action_group_run(0x0A,1);
                delay_ms(1200);
								tell_openmv_to_loosen2();
								delay_ms(300);
                break;
						case 50:
								cmd_action_group_speed(0x0B,175);
                cmd_action_group_run(0x0B,1);
                delay_ms(1200);
								tell_openmv_to_loosen2();
								delay_ms(300);
                break;
						case 34:
								cmd_action_group_speed(0x0C,175);
                cmd_action_group_run(0x0C,1);
                delay_ms(1200);
								tell_openmv_to_loosen2();
								delay_ms(300);
                break;
						case 18:
								cmd_action_group_speed(0x0D,175);
                cmd_action_group_run(0x0D,1);
                delay_ms(1200);
								tell_openmv_to_loosen2();
								delay_ms(300);
                break;
						case 51:
								cmd_action_group_speed(0x38,175);
                cmd_action_group_run(0x38,1);
                delay_ms(1200);
								tell_openmv_to_loosen2();
								delay_ms(300);
                break;
						case 35:
								cmd_action_group_speed(0x0F,175);
                cmd_action_group_run(0x0F,1);
                delay_ms(1200);
								tell_openmv_to_loosen2();
								delay_ms(300);
                break;
						case 19:
								cmd_action_group_speed(0x10,100);
                cmd_action_group_run(0x10,1);
                delay_ms(1800);
								tell_openmv_to_loosen2();
								delay_ms(300);
                break;
					}
//					tell_openmv_to_loosen2();//�ɿ�צ��
//					delay_ms(1000);	//��������ֵ�bug�����ɿ�
					if(ballid == 35||ballid == 18||ballid == 50||ballid == 33)
					{
						switch(ballid)
						{
						case 35:
							cmd_action_group_speed(0x11,175);
							cmd_action_group_run(0x11,1);
              delay_ms(800);
              break;
						case 18:
							cmd_action_group_speed(0x12,175);
							cmd_action_group_run(0x12,1);
              delay_ms(800);
              break;
						case 50:
							cmd_action_group_speed(0x13,175);
							cmd_action_group_run(0x13,1);
              delay_ms(800);
              break;
						case 33:
							cmd_action_group_speed(0x14,175);
							cmd_action_group_run(0x14,1);
              delay_ms(800);
              break;
						}
					}
					if(ballid == 49||ballid == 17||ballid == 34||ballid == 51||ballid == 19)
				{
					switch(ballid)
						{
						case 49:
							cmd_action_group_speed(0x18,175);
							cmd_action_group_run(0x18,1);
              delay_ms(800);
              break;
						case 17:
							cmd_action_group_speed(0x19,175);
							cmd_action_group_run(0x19,1);
              delay_ms(800);
              break;
						case 34:
							cmd_action_group_speed(0x1A,175);
							cmd_action_group_run(0x1A,1);
              delay_ms(800);
              break;
						case 51:
							cmd_action_group_speed(0x1B,175);
							cmd_action_group_run(0x1B,1);
              delay_ms(800);
              break;
						case 19:
							cmd_action_group_speed(0x1C,175);
							cmd_action_group_run(0x1C,1);
              delay_ms(800);
              break;
						}
				}	 
				ballid = 0;
    }
	
baohu_stepped:
		/* ��ǰ��  ֱ��ƽ̨��Ե */
    while(1) {
        set_chassis_speed(-3, 50, 0);
        if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 0&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 1){
					set_chassis_speed(0, 0, 0);
					delay_ms(100);
					cmd_action_group_speed(0x00,150);
					cmd_action_group_run(0x00,1);
					delay_ms(800);
					break;
				}
			} 
}


/**********************************************************************
  * ��������final_Catch_disc_red
  * ����: ����  ץȡԲ�̻�
  * ��������   
  * ����ֵ:��
***********************************************************************/
  void final_Catch_disc_red()
{
		int delay_wait_red = 2000;
    for(int i=0;i<5 ;i++){
				openmv.message = 0;
        servogroup_catch_Stripplatform();//��е��̧��
				delay_ms(800);
				delay_ms(delay_wait_red);
				if(i<4){
					delay_wait_red -= 300;
				}
        tell_openmv_to_distinguish_Strip();//����openmv��̧��
				tell_openmv_to_distinguish_Strip();
				tell_openmv_to_distinguish_Strip();
				tell_openmv_to_distinguish_Strip();
				tell_openmv_to_distinguish_Strip();
				int catch_cnt = 0;
        while(1) {
            //set_chassis_speed(0,5,0);
            //Get_openmv(&openmv);
            if(openmv.message == 0x01) break;
						if(openmv.message == 0x02 && catch_cnt == 0) {
							catch_cnt++;
							tell_openmv_to_distinguish_Strip();
							tell_openmv_to_distinguish_Strip();
						}
        }
				printf("see it\n");
				delay_ms(50);
				cmd_action_group_run(0x16,1);
				delay_ms(200);
				tell_claw_to_catch();
				delay_ms(100);

				openmv.message = 0;
        servogroup_ic_Stripplatform();//����Ӧ�ü�һ��ִ�д�Բ�̻�����ȡic����
				delay_ms(1000);
				tell_openmv_to_loosen3();
				delay_ms(500);
				int ballid = 0,ball_cnt = 0;
				waittime = 100;
				while(1)
				{
					if(ReadBlockData(ballID) == STATUS_OK)break;
					if (waittime == 0 && ball_cnt<2)
					{
						tell_claw_to_catch();
						delay_ms(100);
						cmd_action_group_run(0x31,1);
						delay_ms(500);
						tell_openmv_to_loosen3();
						delay_ms(100);
						waittime = 100;
						ball_cnt++;
					}
					if(ball_cnt >= 2)break;
				}
				ball_cnt = 0;
				if(waittime == 0) continue;
				ballid=(int)ballID[1]; 
				printf("%d",ballid);
				tell_claw_to_catch();
				delay_ms(200);

       switch(ballid)
				{
            case 49:
								cmd_action_group_speed(0x08,175);
                cmd_action_group_run(0x08,1);
                delay_ms(1200);
                break;
            case 33:
								cmd_action_group_speed(0x09,175);
                cmd_action_group_run(0x09,1);
                delay_ms(1200);
                break;
						case 17:
								cmd_action_group_speed(0x0A,175);
                cmd_action_group_run(0x0A,1);
                delay_ms(1200);
                break;
						case 50:
								cmd_action_group_speed(0x0B,175);
                cmd_action_group_run(0x0B,1);
                delay_ms(1200);
                break;
						case 34:
								cmd_action_group_speed(0x0C,175);
                cmd_action_group_run(0x0C,1);
                delay_ms(1200);
                break;
						case 18:
								cmd_action_group_speed(0x0D,175);
                cmd_action_group_run(0x0D,1);
                delay_ms(1200);
                break;
						case 51:
								cmd_action_group_speed(0x0E,175);
                cmd_action_group_run(0x0E,1);
                delay_ms(1200);
                break;
						case 35:
								cmd_action_group_speed(0x0F,175);
                cmd_action_group_run(0x0F,1);
                delay_ms(1200);
                break;
						case 19:
								cmd_action_group_speed(0x10,100);
                cmd_action_group_run(0x10,1);
                delay_ms(1800);
                break;
					}
//				if(ballid == 35||ballid == 18||ballid == 50||ballid == 33)
//				{
//					tell_openmv_to_loosen2();
//				}
//				if(ballid == 49||ballid == 17||ballid == 34||ballid == 51||ballid == 19)
//				{
//					tell_openmv_to_loosen2();
//				}	
					tell_openmv_to_loosen2();//�ɿ�צ��
					delay_ms(500);
					if(ballid == 35||ballid == 18||ballid == 50||ballid == 33)
					{
						switch(ballid)
						{
						case 35:
							cmd_action_group_speed(0x11,175);
							cmd_action_group_run(0x11,1);
              delay_ms(800);
              break;
						case 18:
							cmd_action_group_speed(0x12,175);
							cmd_action_group_run(0x12,1);
              delay_ms(800);
              break;
						case 50:
							cmd_action_group_speed(0x13,175);
							cmd_action_group_run(0x13,1);
              delay_ms(800);
              break;
						case 33:
							cmd_action_group_speed(0x14,175);
							cmd_action_group_run(0x14,1);
              delay_ms(800);
              break;
						}
					}
					if(ballid == 49||ballid == 17||ballid == 34||ballid == 51||ballid == 19)
				{
					switch(ballid)
						{
						case 49:
							cmd_action_group_speed(0x18,175);
							cmd_action_group_run(0x18,1);
              delay_ms(800);
              break;
						case 17:
							cmd_action_group_speed(0x19,175);
							cmd_action_group_run(0x19,1);
              delay_ms(800);
              break;
						case 34:
							cmd_action_group_speed(0x1A,175);
							cmd_action_group_run(0x1A,1);
              delay_ms(800);
              break;
						case 51:
							cmd_action_group_speed(0x1B,175);
							cmd_action_group_run(0x1B,1);
              delay_ms(800);
              break;
						case 19:
							cmd_action_group_speed(0x1C,175);
							cmd_action_group_run(0x1C,1);
              delay_ms(800);
              break;
						}
				}	 	
				//ballid=0;
					
    }
}

/**********************************************************************
  * ��������final_Catch_disc_red
  * ����: ����  ץȡԲ�̻�
  * ��������   
  * ����ֵ:��
***********************************************************************/
  void final_Catch_disc_blue()
{
		int delay_wait_red = 2000;
    for(int i=0;i<5 ;i++){
				openmv.message = 0;
        servogroup_catch_Stripplatform();//��е��̧��
				delay_ms(800);
				delay_ms(delay_wait_red);
				if(i<4){
					delay_wait_red -= 300;
				}
        tell_openmv_to_distinguish_Strip();//����openmv��̧��
				tell_openmv_to_distinguish_Strip();
				tell_openmv_to_distinguish_Strip();
				tell_openmv_to_distinguish_Strip();
				tell_openmv_to_distinguish_Strip();
				int catch_cnt = 0;
        while(1) {
            //set_chassis_speed(0,5,0);
            //Get_openmv(&openmv);
            if(openmv.message == 0x01) break;
						if(openmv.message == 0x02 && catch_cnt == 0) {
							catch_cnt++;
							tell_openmv_to_distinguish_Strip();
							tell_openmv_to_distinguish_Strip();
						}
        }
				printf("see it\n");
				delay_ms(80);
				cmd_action_group_run(0x37,1);
				delay_ms(200);
				tell_claw_to_catch();
				delay_ms(100);

				openmv.message = 0;
        servogroup_ic_Stripplatform();//����Ӧ�ü�һ��ִ�д�Բ�̻�����ȡic����
				delay_ms(1000);
				tell_openmv_to_loosen3();
				delay_ms(300);
				int ballid = 0,ball_cnt = 0;
				waittime = 100;
				while(1)
				{
					if(ReadBlockData(ballID) == STATUS_OK)break;
					if (waittime == 0 && ball_cnt<2)
					{
						tell_claw_to_catch();
						delay_ms(100);
						cmd_action_group_run(0x31,1);
						delay_ms(500);
						tell_openmv_to_loosen3();
						delay_ms(100);
						waittime = 100;
						ball_cnt++;
					}
					if(ball_cnt >= 2)break;
				}
				ball_cnt = 0;
				if(waittime == 0) continue;
				ballid=(int)ballID[1]; 
				printf("%d",ballid);
				tell_claw_to_catch();
				delay_ms(500);

       switch(ballid)
				{
            case 49:
								cmd_action_group_speed(0x08,175);
                cmd_action_group_run(0x08,1);
                delay_ms(1200);
                break;
            case 33:
								cmd_action_group_speed(0x09,175);
                cmd_action_group_run(0x09,1);
                delay_ms(1200);
                break;
						case 17:
								cmd_action_group_speed(0x0A,175);
                cmd_action_group_run(0x0A,1);
                delay_ms(1200);
                break;
						case 50:
								cmd_action_group_speed(0x0B,175);
                cmd_action_group_run(0x0B,1);
                delay_ms(1200);
                break;
						case 34:
								cmd_action_group_speed(0x0C,175);
                cmd_action_group_run(0x0C,1);
                delay_ms(1200);
                break;
						case 18:
								cmd_action_group_speed(0x0D,175);
                cmd_action_group_run(0x0D,1);
                delay_ms(1200);
                break;
						case 51:
								cmd_action_group_speed(0x38,175);
                cmd_action_group_run(0x38,1);
                delay_ms(1200);
                break;
						case 35:
								cmd_action_group_speed(0x0F,175);
                cmd_action_group_run(0x0F,1);
                delay_ms(1200);
                break;
						case 19:
								cmd_action_group_speed(0x10,100);
                cmd_action_group_run(0x10,1);
                delay_ms(1800);
                break;
					}
//				if(ballid == 35||ballid == 18||ballid == 50||ballid == 33)
//				{
//					tell_openmv_to_loosen2();
//				}
//				if(ballid == 49||ballid == 17||ballid == 34||ballid == 51||ballid == 19)
//				{
//					tell_openmv_to_loosen2();
//				}	
					tell_openmv_to_loosen2();//�ɿ�צ��
					delay_ms(300);
					if(ballid == 35||ballid == 18||ballid == 50||ballid == 33)
					{
						switch(ballid)
						{
						case 35:
							cmd_action_group_speed(0x11,175);
							cmd_action_group_run(0x11,1);
              delay_ms(800);
              break;
						case 18:
							cmd_action_group_speed(0x12,175);
							cmd_action_group_run(0x12,1);
              delay_ms(800);
              break;
						case 50:
							cmd_action_group_speed(0x13,175);
							cmd_action_group_run(0x13,1);
              delay_ms(800);
              break;
						case 33:
							cmd_action_group_speed(0x14,175);
							cmd_action_group_run(0x14,1);
              delay_ms(800);
              break;
						}
					}
					if(ballid == 49||ballid == 17||ballid == 34||ballid == 51||ballid == 19)
				{
					switch(ballid)
						{
						case 49:
							cmd_action_group_speed(0x18,175);
							cmd_action_group_run(0x18,1);
              delay_ms(800);
              break;
						case 17:
							cmd_action_group_speed(0x19,175);
							cmd_action_group_run(0x19,1);
              delay_ms(800);
              break;
						case 34:
							cmd_action_group_speed(0x1A,175);
							cmd_action_group_run(0x1A,1);
              delay_ms(800);
              break;
						case 51:
							cmd_action_group_speed(0x1B,175);
							cmd_action_group_run(0x1B,1);
              delay_ms(800);
              break;
						case 19:
							cmd_action_group_speed(0x1C,175);
							cmd_action_group_run(0x1C,1);
              delay_ms(800);
              break;
						}
				}	 	
				ballid=0;
					
    }
}

void get_scores_red(void)
{		
	hit_bar_red();
		while(1) 
	{
       set_chassis_speed(20, 30, 0);
       if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 1&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 0) break;
  }
	set_chassis_speed(0,0,0);
	delay_ms(300);
	cmd_action_group_run(0x1D,1);
	span_find_zero();
	delay_ms(1500);
	set_chassis_speed(15, -30, 0);
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 0)break;
		printf("%d\r\n",HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5));
	}
	set_chassis_speed(0,0,0);
	cmd_action_group_run(0x1E,1);
	delay_ms(1500);
	tell_claw_to_catch();
	delay_ms(500);
	cmd_action_group_run(0x1F,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(500);
	cmd_action_group_run(0x23,1);
	delay_ms(1500);
	span(1);
	delay_ms(500);
	cmd_action_group_run(0x1E,1);
	delay_ms(1500);
	tell_claw_to_catch();
	delay_ms(500);
	cmd_action_group_run(0x20,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(500);
	cmd_action_group_run(0x24,1);
	delay_ms(2000);
	span(2);
	delay_ms(500);
	cmd_action_group_run(0x1E,1);
	delay_ms(1500);
	tell_claw_to_catch();
	delay_ms(500);
	cmd_action_group_run(0x21,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(500);
	cmd_action_group_run(0x25,1);
	delay_ms(2000);
	cmd_action_group_run(0x1D,1);
	delay_ms(3000);
	set_chassis_speed(15,-30,0);
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 1)break;
	}
	delay_ms(100);
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 0)break;
	}
	set_chassis_speed(0,0,0);
	span(3);
	delay_ms(500);
	cmd_action_group_run(0x1E,1);
	delay_ms(1500);
	tell_claw_to_catch();
	delay_ms(500);
	cmd_action_group_run(0x1F,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(500);
	cmd_action_group_run(0x23,1);
	delay_ms(1500);
	span(4);
	delay_ms(500);
	cmd_action_group_run(0x1E,1);
	delay_ms(3000);
	tell_claw_to_catch();
	delay_ms(500);
	cmd_action_group_run(0x20,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(500);
	cmd_action_group_run(0x24,1);
	delay_ms(2000);
	span(5);
	delay_ms(500);
	cmd_action_group_run(0x1E,1);
	delay_ms(2000);
	tell_claw_to_catch();
	delay_ms(500);
	cmd_action_group_run(0x21,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(500);
	cmd_action_group_run(0x25,1);
	delay_ms(2000);
	cmd_action_group_run(0x1D,1);
	delay_ms(3000);
	set_chassis_speed(15,-30,0);
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 1)break;
	}
	delay_ms(100);
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 0)break;
	}
	set_chassis_speed(0,0,0);
	span(6);
	cmd_action_group_run(0x1E,1);
	delay_ms(1500);
	tell_claw_to_catch();
	delay_ms(500);
	cmd_action_group_run(0x1F,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(500);
	cmd_action_group_run(0x23,1);
	delay_ms(1500);
	span(7);
	delay_ms(500);
	cmd_action_group_run(0x1E,1);
	delay_ms(3000);
	tell_claw_to_catch();
	delay_ms(500);
	cmd_action_group_run(0x20,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(500);
	cmd_action_group_run(0x24,1);
	delay_ms(2000);
	span(8);
	delay_ms(500);
	cmd_action_group_run(0x1E,1);
	delay_ms(3000);
	tell_claw_to_catch();
	delay_ms(500);
	cmd_action_group_run(0x21,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(500);
	cmd_action_group_run(0x25,1);
	delay_ms(2000);
}

void get_scores_blue(void)
{		
	hit_bar_red();
		while(1) 
	{
       set_chassis_speed(20, 30, 0);
       if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 1&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 0) break;
  }
	set_chassis_speed(0,0,0);
	delay_ms(300);
	cmd_action_group_run(0x32,1);
	span_find_zero();
	delay_ms(1500);
	set_chassis_speed(15, -30, 0);
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 0)break;
		printf("%d\r\n",HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5));
	}
	set_chassis_speed(0,0,0);
	cmd_action_group_run(0x1E,1);
	delay_ms(1500);
	tell_claw_to_catch();
	delay_ms(500);
	cmd_action_group_run(0x1F,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(500);
	cmd_action_group_run(0x23,1);
	delay_ms(1500);
	span(1);
	delay_ms(500);
	cmd_action_group_run(0x1E,1);
	delay_ms(1500);
	tell_claw_to_catch();
	delay_ms(500);
	cmd_action_group_run(0x20,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(500);
	cmd_action_group_run(0x24,1);
	delay_ms(2000);
	span(2);
	delay_ms(500);
	cmd_action_group_run(0x1E,1);
	delay_ms(1500);
	tell_claw_to_catch();
	delay_ms(500);
	cmd_action_group_run(0x21,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(500);
	cmd_action_group_run(0x25,1);
	delay_ms(2000);
	cmd_action_group_run(0x32,1);
	delay_ms(3000);
	set_chassis_speed(15,-30,0);
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 1)break;
	}
	delay_ms(100);
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 0)break;
	}
	set_chassis_speed(0,0,0);
	span(3);
	delay_ms(500);
	cmd_action_group_run(0x1E,1);
	delay_ms(1500);
	tell_claw_to_catch();
	delay_ms(500);
	cmd_action_group_run(0x1F,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(500);
	cmd_action_group_run(0x23,1);
	delay_ms(1500);
	span(4);
	delay_ms(500);
	cmd_action_group_run(0x1E,1);
	delay_ms(3000);
	tell_claw_to_catch();
	delay_ms(500);
	cmd_action_group_run(0x20,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(500);
	cmd_action_group_run(0x24,1);
	delay_ms(2000);
	span(5);
	delay_ms(500);
	cmd_action_group_run(0x1E,1);
	delay_ms(2000);
	tell_claw_to_catch();
	delay_ms(500);
	cmd_action_group_run(0x21,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(500);
	cmd_action_group_run(0x25,1);
	delay_ms(2000);
	cmd_action_group_run(0x32,1);
	delay_ms(3000);
	set_chassis_speed(15,-30,0);
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 1)break;
	}
	delay_ms(100);
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 0)break;
	}
	set_chassis_speed(0,0,0);
	span(6);
	cmd_action_group_run(0x1E,1);
	delay_ms(1500);
	tell_claw_to_catch();
	delay_ms(500);
	cmd_action_group_run(0x1F,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(500);
	cmd_action_group_run(0x23,1);
	delay_ms(1500);
	span(7);
	delay_ms(500);
	cmd_action_group_run(0x1E,1);
	delay_ms(3000);
	tell_claw_to_catch();
	delay_ms(500);
	cmd_action_group_run(0x20,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(500);
	cmd_action_group_run(0x24,1);
	delay_ms(2000);
	span(8);
	delay_ms(500);
	cmd_action_group_run(0x1E,1);
	delay_ms(3000);
	tell_claw_to_catch();
	delay_ms(500);
	cmd_action_group_run(0x21,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(500);
	cmd_action_group_run(0x25,1);
	delay_ms(2000);
}

void get_scores_qrcode_red(void)
{
	hit_bar_red();
	while(1) 
	{
    set_chassis_speed(15, 30, 0);
    if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 1&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 0) break;
  }
	set_chassis_speed(0,0,0);
	cmd_action_group_run(0x1D,1);
	span_find_zero();
	delay_ms(500);
	set_chassis_speed(5, -30, 0);
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 0)break;
		printf("%d\r\n",HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5));
	}
	set_chassis_speed(0,0,0);
	cmd_action_group_speed(0x1E,300);
	cmd_action_group_run(0x1E,1);
	delay_ms(600);
	tell_claw_to_catch();
	delay_ms(200);
	cmd_action_group_speed(0x1F,100);
	cmd_action_group_run(0x1F,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(500);
	cmd_action_group_speed(0x23,175);
	cmd_action_group_run(0x23,1);
	delay_ms(800);
	span(1);
	delay_ms(500);
	cmd_action_group_speed(0x1E,300);
	cmd_action_group_run(0x1E,1);
	delay_ms(600);
	tell_claw_to_catch();
	delay_ms(200);
	cmd_action_group_speed(0x20,300);
	cmd_action_group_run(0x20,1);
	delay_ms(800);
	tell_openmv_to_loosen2();
	delay_ms(500);
	cmd_action_group_speed(0x24,175);
	cmd_action_group_run(0x24,1);
	delay_ms(1300);
	while(1)
	{
		if(putBallOrder[2] == 0x13)
		{
			span(8);
			delay_ms(500);
			cmd_action_group_speed(0x1E,300);
			cmd_action_group_run(0x1E,1);
			delay_ms(600);
			tell_claw_to_catch();
			delay_ms(500);
			cmd_action_group_speed(0x21,300);
			cmd_action_group_run(0x21,1);
				delay_ms(800);
			tell_openmv_to_loosen2();
			delay_ms(200);
			cmd_action_group_speed(0x25,175);
			cmd_action_group_run(0x25,1);
			delay_ms(800);
			break;
			}
		if(putBallOrder[2] == 0x12)
		{
				span(5);
				delay_ms(500);
				cmd_action_group_speed(0x1E,300);
				cmd_action_group_run(0x1E,1);
				delay_ms(600);
				tell_claw_to_catch();
				delay_ms(200);
				cmd_action_group_speed(0x21,300);
				cmd_action_group_run(0x21,1);
				delay_ms(800);
				tell_openmv_to_loosen2();
				delay_ms(200);
				cmd_action_group_speed(0x25,175);
				cmd_action_group_run(0x25,1);
				delay_ms(800);
				break;
		}
		if(putBallOrder[2] == 0x11)
		{
			span(2);
			delay_ms(500);
			cmd_action_group_speed(0x1E,300);
			cmd_action_group_run(0x1E,1);
			delay_ms(600);
			tell_claw_to_catch();
			delay_ms(200);
			cmd_action_group_speed(0x21,300);
			cmd_action_group_run(0x21,1);
			delay_ms(800);
			tell_openmv_to_loosen2();
			delay_ms(200);
			cmd_action_group_speed(0x25,175);
			cmd_action_group_run(0x25,1);
			delay_ms(800);
			break;
		}		
	}
	cmd_action_group_speed(0x1D,100);
	cmd_action_group_run(0x1D,1);
	delay_ms(1200);
	set_chassis_speed(5,-15,0);
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 1)break;
	}
	delay_ms(100);
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 0)break;
	}
	set_chassis_speed(0,0,0);
	span_find_flag();
	delay_ms(50);
	span(3);
	delay_ms(500);
	cmd_action_group_speed(0x1E,300);
	cmd_action_group_run(0x1E,1);
	delay_ms(600);
	tell_claw_to_catch();
	delay_ms(200);
	cmd_action_group_speed(0x1F,100);
	cmd_action_group_run(0x1F,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(200);
	cmd_action_group_speed(0x23,175);
	cmd_action_group_run(0x23,1);
	delay_ms(800);
	span(4);
	delay_ms(500);
	cmd_action_group_speed(0x1E,300);
	cmd_action_group_run(0x1E,1);
	delay_ms(600);
	tell_claw_to_catch();
	delay_ms(200);
	cmd_action_group_speed(0x20,300);
	cmd_action_group_run(0x20,1);
	delay_ms(800);
	tell_openmv_to_loosen2();
	delay_ms(200);
	cmd_action_group_speed(0x24,175);
	cmd_action_group_run(0x24,1);
	delay_ms(1300);
	while(1)
	{
		if(putBallOrder[5] == 0x13)
		{
			span(8);
			delay_ms(500);
			cmd_action_group_speed(0x1E,300);
			cmd_action_group_run(0x1E,1);
			delay_ms(600);
			tell_claw_to_catch();
			delay_ms(200);
			cmd_action_group_speed(0x21,300);
			cmd_action_group_run(0x21,1);
				delay_ms(800);
			tell_openmv_to_loosen2();
			delay_ms(200);
			cmd_action_group_speed(0x25,175);
			cmd_action_group_run(0x25,1);
			delay_ms(800);
			break;
			}
				if(putBallOrder[5] == 0x12)
		{
				span(5);
				delay_ms(500);
				cmd_action_group_speed(0x1E,300);
				cmd_action_group_run(0x1E,1);
				delay_ms(600);
				tell_claw_to_catch();
				delay_ms(200);
				cmd_action_group_speed(0x21,300);
				cmd_action_group_run(0x21,1);
				delay_ms(800);
				tell_openmv_to_loosen2();
				delay_ms(200);
				cmd_action_group_speed(0x25,175);
				cmd_action_group_run(0x25,1);
				delay_ms(800);
				break;
		}
		if(putBallOrder[5] == 0x11)
		{
			span(2);
			delay_ms(500);
			cmd_action_group_speed(0x1E,300);
			cmd_action_group_run(0x1E,1);
			delay_ms(600);
			tell_claw_to_catch();
			delay_ms(200);
			cmd_action_group_speed(0x21,300);
			cmd_action_group_run(0x21,1);
			delay_ms(800);
			tell_openmv_to_loosen2();
			delay_ms(200);
			cmd_action_group_speed(0x25,175);
			cmd_action_group_run(0x25,1);
			delay_ms(800);
			break;
		}		
	}
	cmd_action_group_speed(0x1D,100);
	cmd_action_group_run(0x1D,1);
	delay_ms(1200);
	set_chassis_speed(5,-15,0);
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 1)break;
	}
	delay_ms(100);
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 0)break;
	}
	set_chassis_speed(0,0,0);
	span_find_flag();
	delay_ms(50);
	span(6);
	cmd_action_group_speed(0x1E,300);
	cmd_action_group_run(0x1E,1);
	delay_ms(600);
	tell_claw_to_catch();
	delay_ms(200);
	cmd_action_group_speed(0x1F,100);
	cmd_action_group_run(0x1F,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(200);
	cmd_action_group_speed(0x23,175);
	cmd_action_group_run(0x23,1);
	delay_ms(800);
	span(7);
	delay_ms(500);
	cmd_action_group_speed(0x1E,300);
	cmd_action_group_run(0x1E,1);
	delay_ms(600);
	tell_claw_to_catch();
	delay_ms(200);
	cmd_action_group_speed(0x20,300);
	cmd_action_group_run(0x20,1);
	delay_ms(800);
	tell_openmv_to_loosen2();
	delay_ms(200);
	cmd_action_group_speed(0x24,175);
	cmd_action_group_run(0x24,1);
	delay_ms(1300);
	span_find_flag();
	delay_ms(50);
	while(1)
	{
		if(putBallOrder[8] == 0x13)
		{
			span(8);
			delay_ms(500);
			cmd_action_group_speed(0x1E,300);
			cmd_action_group_run(0x1E,1);
			delay_ms(600);
			tell_claw_to_catch();
			delay_ms(200);
			cmd_action_group_speed(0x21,300);
			cmd_action_group_run(0x21,1);
				delay_ms(800);
			tell_openmv_to_loosen2();
			delay_ms(200);
			cmd_action_group_speed(0x25,175);
			cmd_action_group_run(0x25,1);
			delay_ms(800);
			break;
			}
			if(putBallOrder[8] == 0x12)
		{
				span(5);
				delay_ms(500);
				cmd_action_group_speed(0x1E,300);
				cmd_action_group_run(0x1E,1);
				delay_ms(600);
				tell_claw_to_catch();
				delay_ms(200);
				cmd_action_group_speed(0x21,300);
				cmd_action_group_run(0x21,1);
				delay_ms(800);
				tell_openmv_to_loosen2();
				delay_ms(200);
				cmd_action_group_speed(0x25,175);
				cmd_action_group_run(0x25,1);
				delay_ms(800);
				break;
		}
		if(putBallOrder[8] == 0x11)
		{
			span(2);
			delay_ms(500);
			cmd_action_group_speed(0x1E,300);
			cmd_action_group_run(0x1E,1);
			delay_ms(600);
			tell_claw_to_catch();
			delay_ms(200);
			cmd_action_group_speed(0x21,300);
			cmd_action_group_run(0x21,1);
			delay_ms(800);
			tell_openmv_to_loosen2();
			delay_ms(200);
			cmd_action_group_speed(0x25,175);
			cmd_action_group_run(0x25,1);
			delay_ms(800);
			break;
		}		
	}
}

void get_scores_qrcode_blue(void)
{
	hit_bar_red();
	while(1) 
	{
    set_chassis_speed(15, 30, 0);
    if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 1&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 0) break;
  }
	set_chassis_speed(0,0,0);
	cmd_action_group_run(0x32,1);
	span_find_zero();
	delay_ms(500);
	set_chassis_speed(5, -30, 0);
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 0)break;
		printf("%d\r\n",HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5));
	}
	set_chassis_speed(0,0,0);
	cmd_action_group_speed(0x1E,300);
	cmd_action_group_run(0x1E,1);
	delay_ms(600);
	tell_claw_to_catch();
	delay_ms(200);
	cmd_action_group_speed(0x1F,100);
	cmd_action_group_run(0x1F,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(200);
	cmd_action_group_speed(0x23,175);
	cmd_action_group_run(0x23,1);
	delay_ms(800);
	span(1);
	delay_ms(500);
	cmd_action_group_speed(0x1E,300);
	cmd_action_group_run(0x1E,1);
	delay_ms(600);
	tell_claw_to_catch();
	delay_ms(200);
	cmd_action_group_speed(0x20,300);
	cmd_action_group_run(0x20,1);
	delay_ms(800);
	tell_openmv_to_loosen2();
	delay_ms(200);
	cmd_action_group_speed(0x24,175);
	cmd_action_group_run(0x24,1);
	delay_ms(800);
	while(1)
	{
		if(putBallOrder[2] == 0x13)
		{
			span(8);
			delay_ms(500);
			cmd_action_group_speed(0x1E,300);
			cmd_action_group_run(0x1E,1);
			delay_ms(600);
			tell_claw_to_catch();
			delay_ms(200);
			cmd_action_group_speed(0x21,300);
			cmd_action_group_run(0x21,1);
				delay_ms(800);
			tell_openmv_to_loosen2();
			delay_ms(200);
			cmd_action_group_speed(0x25,175);
			cmd_action_group_run(0x25,1);
			delay_ms(1000);
			break;
			}
		if(putBallOrder[2] == 0x12)
		{
				span(5);
				delay_ms(500);
				cmd_action_group_speed(0x1E,300);
				cmd_action_group_run(0x1E,1);
				delay_ms(600);
				tell_claw_to_catch();
				delay_ms(200);
				cmd_action_group_speed(0x21,300);
				cmd_action_group_run(0x21,1);
				delay_ms(800);
				tell_openmv_to_loosen2();
				delay_ms(200);
				cmd_action_group_speed(0x25,175);
				cmd_action_group_run(0x25,1);
				delay_ms(1000);
				break;
		}
		if(putBallOrder[2] == 0x11)
		{
			span(2);
			delay_ms(500);
			cmd_action_group_speed(0x1E,300);
			cmd_action_group_run(0x1E,1);
			delay_ms(600);
			tell_claw_to_catch();
			delay_ms(200);
			cmd_action_group_speed(0x21,300);
			cmd_action_group_run(0x21,1);
			delay_ms(800);
			tell_openmv_to_loosen2();
			delay_ms(200);
			cmd_action_group_speed(0x25,175);
			cmd_action_group_run(0x25,1);
			delay_ms(1000);
			break;
		}		
	}
	cmd_action_group_speed(0x26,100);
	cmd_action_group_run(0x26,1);
	delay_ms(1800);
	set_chassis_speed(5,-15,0);
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 1)break;
	}
	delay_ms(300);
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 0)break;
	}
	set_chassis_speed(0,0,0);
	span_find_flag();
	delay_ms(50);
	span(3);
	delay_ms(500);
	cmd_action_group_speed(0x1E,300);
	cmd_action_group_run(0x1E,1);
	delay_ms(600);
	tell_claw_to_catch();
	delay_ms(200);
	cmd_action_group_speed(0x1F,100);
	cmd_action_group_run(0x1F,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(200);
	cmd_action_group_speed(0x23,175);
	cmd_action_group_run(0x23,1);
	delay_ms(800);
	span(4);
	delay_ms(500);
	cmd_action_group_speed(0x1E,300);
	cmd_action_group_run(0x1E,1);
	delay_ms(600);
	tell_claw_to_catch();
	delay_ms(200);
	cmd_action_group_speed(0x20,300);
	cmd_action_group_run(0x20,1);
	delay_ms(800);
	tell_openmv_to_loosen2();
	delay_ms(200);
	cmd_action_group_speed(0x24,175);
	cmd_action_group_run(0x24,1);
	delay_ms(1000);
	while(1)
	{
		if(putBallOrder[5] == 0x13)
		{
			span(8);
			delay_ms(500);
			cmd_action_group_speed(0x1E,300);
			cmd_action_group_run(0x1E,1);
			delay_ms(600);
			tell_claw_to_catch();
			delay_ms(200);
			cmd_action_group_speed(0x21,300);
			cmd_action_group_run(0x21,1);
			delay_ms(800);
			tell_openmv_to_loosen2();
			delay_ms(200);
			cmd_action_group_speed(0x25,175);
			cmd_action_group_run(0x25,1);
			delay_ms(1000);
			break;
			}
				if(putBallOrder[5] == 0x12)
		{
				span(5);
				delay_ms(500);
				cmd_action_group_speed(0x1E,300);
				cmd_action_group_run(0x1E,1);
				delay_ms(600);
				tell_claw_to_catch();
				delay_ms(200);
				cmd_action_group_speed(0x21,300);
				cmd_action_group_run(0x21,1);
				delay_ms(800);
				tell_openmv_to_loosen2();
				delay_ms(200);
				cmd_action_group_speed(0x25,175);
				cmd_action_group_run(0x25,1);
				delay_ms(1000);
				break;
		}
		if(putBallOrder[5] == 0x11)
		{
			span(2);
			delay_ms(500);
			cmd_action_group_speed(0x1E,300);
			cmd_action_group_run(0x1E,1);
			delay_ms(600);
			tell_claw_to_catch();
			delay_ms(200);
			cmd_action_group_speed(0x21,300);
			cmd_action_group_run(0x21,1);
			delay_ms(800);
			tell_openmv_to_loosen2();
			delay_ms(200);
			cmd_action_group_speed(0x25,175);
			cmd_action_group_run(0x25,1);
			delay_ms(1000);
			break;
		}		
	}
	cmd_action_group_speed(0x26,100);
	cmd_action_group_run(0x26,1);
	delay_ms(1800);
	set_chassis_speed(5,-15,0);
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 1)break;
	}
	delay_ms(300);
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_5) == 0)break;
	}
	set_chassis_speed(0,0,0);
	span_find_flag();
	delay_ms(50);
	span(6);
	cmd_action_group_speed(0x1E,300);
	cmd_action_group_run(0x1E,1);
	delay_ms(600);
	tell_claw_to_catch();
	delay_ms(200);
	cmd_action_group_speed(0x1F,100);
	cmd_action_group_run(0x1F,1);
	delay_ms(2500);
	tell_openmv_to_loosen2();
	delay_ms(200);
	cmd_action_group_speed(0x23,175);
	cmd_action_group_run(0x23,1);
	delay_ms(800);
	span(7);
	delay_ms(500);
	cmd_action_group_speed(0x1E,300);
	cmd_action_group_run(0x1E,1);
	delay_ms(600);
	tell_claw_to_catch();
	delay_ms(200);
	cmd_action_group_speed(0x20,300);
	cmd_action_group_run(0x20,1);
	delay_ms(800);
	tell_openmv_to_loosen2();
	delay_ms(200);
	cmd_action_group_speed(0x24,175);
	cmd_action_group_run(0x24,1);
	delay_ms(1000);
	span_find_flag();
	delay_ms(50);
	while(1)
	{
		if(putBallOrder[8] == 0x13)
		{
			span(8);
			delay_ms(500);
			cmd_action_group_speed(0x1E,300);
			cmd_action_group_run(0x1E,1);
			delay_ms(600);
			tell_claw_to_catch();
			delay_ms(200);
			cmd_action_group_speed(0x21,300);
			cmd_action_group_run(0x21,1);
				delay_ms(800);
			tell_openmv_to_loosen2();
			delay_ms(200);
			cmd_action_group_speed(0x25,175);
			cmd_action_group_run(0x25,1);
			delay_ms(800);
			break;
			}
			if(putBallOrder[8] == 0x12)
		{
				span(5);
				delay_ms(500);
				cmd_action_group_speed(0x1E,300);
				cmd_action_group_run(0x1E,1);
				delay_ms(600);
				tell_claw_to_catch();
				delay_ms(200);
				cmd_action_group_speed(0x21,300);
				cmd_action_group_run(0x21,1);
				delay_ms(800);
				tell_openmv_to_loosen2();
				delay_ms(200);
				cmd_action_group_speed(0x25,175);
				cmd_action_group_run(0x25,1);
				delay_ms(800);
				break;
		}
		if(putBallOrder[8] == 0x11)
		{
			span(2);
			delay_ms(500);
			cmd_action_group_speed(0x1E,300);
			cmd_action_group_run(0x1E,1);
			delay_ms(600);
			tell_claw_to_catch();
			delay_ms(200);
			cmd_action_group_speed(0x21,300);
			cmd_action_group_run(0x21,1);
			delay_ms(800);
			tell_openmv_to_loosen2();
			delay_ms(200);
			cmd_action_group_speed(0x25,175);
			cmd_action_group_run(0x25,1);
			delay_ms(800);
			break;
		}		
	}
}


//��·�߰���ע�͵��Ĵ���Ϊ��һ��·�ߣ�û�ú��⿪�ز��
void road_of_honour_red(void)
{
	run_to_stairs_red();//�ߵ�����ƽ̨ǰ��
	set_imu_status(&attitude,false);//�ص�������׼��ײ����
	hit_bar_red();//ײ��
	move_to_bar_right_red();//�Ƶ����ұ�
	
	Catch_Steppedplatform_red();
	servogroup_Init();
	delay_ms(2000);
	set_chassis_speed(-15,-30,0);
	delay_ms(800);
	set_chassis_speed(0,0,0);
	delay_ms(100);
	set_chassis_speed(-80, 0 , 0);
	HAL_Delay(500);
	imu_calibration();//�����ߵ�ʱ�������̬
	
	leave_bar_red();//�ӽ���ƽ̨����
	set_imu_status(&attitude,true);
	delay_ms(2500);
	set_chassis_speed(-15,0,0);
	delay_ms(300);
	set_chassis_speed(0,0,0);
	delay_ms(500);
	run_to_cornucopia_red();//��Բ�̻�ȥ
	delay_ms(200);
	hit_bar_red();
	move_to_bar_right_red();
	set_chassis_speed(-15,15,0);
//	while(1)
//	{
//		if((HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9) == 0&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_4) == 0))break;
//	}
//	set_chassis_speed(0,0,0);
//	delay_ms(500);
	
//	move_to_cornucopia_center();
//	move_to_bar_right_red();
	set_chassis_speed(0,30,0);
	delay_ms(1000);
	set_chassis_speed(-15,0,0);
	final_Catch_disc_red();//Բ�̻�ץ��
	
	
	servogroup_Init();
	delay_ms(2000);
	set_chassis_speed(-80, 0 , 0);
	delay_ms(500);
	imu_calibration();//�����ߵ�ʱ�������̬
	set_imu_status(&attitude,true);
	set_chassis_speed(0,0,0);
	HAL_Delay(500);
	tell_openmv_to_loosen2();
	delay_ms(500);
	 
	leave_cornucopia_red();
	run_to_scores_red();
	get_scores_red();
	
	while(1)
	{
		set_chassis_speed(-30,-50,0);
		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 0&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 1) break; 
	}
	set_chassis_speed(0,0,0);
//	
//	back_home_by_speed();
//	HAL_Delay(500);
//	run_to_champion_red();
}

//��·�߰���ע�͵��Ĵ���Ϊ��һ��·�ߣ�û�ú��⿪�ز��
void road_of_honour_red2(void)
{
	run_to_stairs_red();//�ߵ�����ƽ̨ǰ��
	set_imu_status(&attitude,false);//�ص�������׼��ײ����
	hit_bar_red();//ײ��
	move_to_bar_right_red();//�Ƶ����ұ�
	
	Catch_Steppedplatform_red();
	servogroup_Init();
	delay_ms(2000);
	set_chassis_speed(-15,-30,0);
	delay_ms(800);
	set_chassis_speed(0,0,0);
	delay_ms(100);
	set_chassis_speed(-80, 0 , 0);
	HAL_Delay(500);
	imu_calibration();//�����ߵ�ʱ�������̬
	
	leave_bar_red();//�ӽ���ƽ̨����
	set_imu_status(&attitude,true);
	delay_ms(2500);
	set_chassis_speed(-15,0,0);
	delay_ms(300);
	set_chassis_speed(0,0,0);
	delay_ms(500);
	run_to_cornucopia_red();//��Բ�̻�ȥ
	delay_ms(200);
	hit_bar_red();
	move_to_bar_right_red();
	set_chassis_speed(-15,15,0);
//	while(1)
//	{
//		if((HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_9) == 0&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_4) == 0))break;
//	}
//	set_chassis_speed(0,0,0);
//	delay_ms(500);
	
//	move_to_cornucopia_center();
//	move_to_bar_right_red();
	set_chassis_speed(0,30,0);
	delay_ms(1000);
	set_chassis_speed(-15,0,0);
	final_Catch_disc_red();//Բ�̻�ץ��
	
	
	servogroup_Init();
	delay_ms(2000);
	set_chassis_speed(-80, 0 , 0);
	delay_ms(500);
	imu_calibration();//�����ߵ�ʱ�������̬
	set_imu_status(&attitude,true);
	set_chassis_speed(0,0,0);
	HAL_Delay(500);
	tell_openmv_to_loosen2();
	delay_ms(500);
	 
	leave_cornucopia_red();
	run_to_scores_red();
	hit_bar_red();
	move_to_bar_right_red();
	get_qrcode();
	delay_ms(500);
	get_scores_qrcode_red();
	//get_scores_red();
	
	while(1)
	{
		set_chassis_speed(-30,-50,0);
		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 0&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 1) break; 
	}
	
	back_home_by_speed();
	HAL_Delay(500);
	run_to_champion_red();
}

void road_of_honour_blue(void)
{
	run_to_stairs_blue();//�ߵ�����ƽ̨�永
	set_imu_status(&attitude,false);//�ص�������׼��ײ����
	hit_bar_blue();//ײ��
	move_to_bar_left_blue();//�Ƶ����ұ�
	
	set_chassis_speed(50, 30 , 0);
	HAL_Delay(500);
	while(1) 
	{
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == 1&&HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0)break;
   }
	set_chassis_speed(80, 0 , 0);
	HAL_Delay(500);
	imu_calibration();//�����ߵ�ʱ�������̬
	
//	set_imu_status(&attitude,true);
	leave_bar_blue();//�ӽ���ƽ̨����
	set_imu_status(&attitude,true);
	delay_ms(2500);
	run_to_cornucopia_blue();//��Բ�̻�ȥ
	delay_ms(200);
	hit_bar_blue();
	move_to_bar_left_blue();
	set_chassis_speed(0,30,0);
	delay_ms(1000);
	
	set_chassis_speed(80, 0 , 0);
	delay_ms(500);
	imu_calibration();//�����ߵ�ʱ�������̬
	set_imu_status(&attitude,true);
	set_chassis_speed(0,0,0);
	HAL_Delay(500);
	 
	leave_cornucopia_blue();
	run_to_scores_blue();
	hit_bar_red();
	
	set_chassis_speed(30, 50 , 0);
	HAL_Delay(500);
	while(1) 
	{
      if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == 1&&HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4) == 0)break;
   } 
	while(1)
	{
		set_chassis_speed(30,-50,0);
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == 0&&HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4 )== 1) break; 
	}
	
	back_home_by_speed_blue();
	HAL_Delay(500);
	run_to_champion_blue();
}

//��·��û������ǰ�󵲰壬��ѭ���嶨λ
void road_of_honour_red_two(void)
{
	road_of_honour_red();
		
		set_chassis_speed(-50,0,0);
		HAL_Delay(1000);
		imu_reset(); 
		set_imu_status(&attitude,true);
		HAL_Delay(500);
		set_chassis_speed(50,0,0);
		HAL_Delay(300);
		set_chassis_speed(0,0,0);
		HAL_Delay(500);
		
		run_to_scores_red();
		hit_bar_red();
		while(1) 
	{
       set_chassis_speed(-30, 30, 0);
       if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 1&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 0) break;
  }
		move_to_bar_right_red();
		back_home_by_speed();
		run_to_champion_red();
}

void road_of_honour_red_three(void)
{
	run_to_stairs_red();//�ߵ�����ƽ̨�永
	set_imu_status(&attitude,false);//�ص�������׼��ײ����
	hit_bar_red();//ײ��
	move_to_bar_right_red();//�Ƶ����ұ�
	
	set_chassis_speed(-50, 30 , 0);
	HAL_Delay(500);
	while(1) 
	{
		if(HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 0&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 1)break;
   }
	set_chassis_speed(-80, 0 , 0);
	HAL_Delay(500);
	imu_calibration();//�����ߵ�ʱ�������̬
	
	set_imu_status(&attitude,true);
	
	rode_of_avoid();
	move_to_cornucopia_center();
	 
	set_chassis_speed(-50,0,0);
		HAL_Delay(1000);
		imu_reset(); 
		set_imu_status(&attitude,true);
		HAL_Delay(500);
		set_chassis_speed(50,0,0);
		HAL_Delay(300);
		set_chassis_speed(0,0,0);
		HAL_Delay(500);
		
		run_to_scores_red();
		hit_bar_red();
		while(1) 
	{
       set_chassis_speed(-30, 30, 0);
       if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 1&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 0) break;
  }
		move_to_bar_right_red();
		back_home_by_speed();
		run_to_champion_red();
	
}

void rode_red_test(void)//���ֲ��Ժõ�·������������
{
//	span_init();
	run_to_stairs_red();
	hit_bar_red();
	move_to_bar_right_red();
	Catch_Steppedplatform_red();
	avoid_object_red();
	hit_bar_red();
	move_to_bar_right_red();
	set_chassis_speed(0,0,0);
	delay_ms(500);
	set_chassis_speed(20,50,0);
	delay_ms(600);
	set_chassis_speed(0,0,0);
	final_Catch_disc_red();
	run_to_scores_red();
	stack_transfer_red();
	move_to_bar_right_red();
//		while(1) 
//	{
//       set_chassis_speed(10, 30, 0);
//       if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 1&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 0) break;
//  }
		get_qrcode();
//		get_scores_red();
		get_scores_qrcode_red();
		back_home_by_speed();
}

void rode_blue_test(void)
{
	run_to_stairs_blue();
	hit_bar_blue();
	move_to_bar_left_blue();
	Catch_Steppedplatform_blue();
	hit_bar_blue();
	
	avoid_object_blue();
	hit_bar_blue();
	move_to_bar_left_blue();
	set_chassis_speed(0,0,0);
	delay_ms(500);
	set_chassis_speed(20,50,0);
	delay_ms(650);
	set_chassis_speed(0,0,0);
	final_Catch_disc_blue();
		cmd_action_group_run(0x00,1);
		delay_ms(1500);
		set_chassis_speed(50,0,0);
		delay_ms(500);
		imu_calibration();
		delay_ms(500);
		set_chassis_speed(-50,0,0);
		delay_ms(850);
		set_imu_status(&attitude,true);
		set_chassis_speed(0,0,0);
		delay_ms(500);
		move_by_encoder(2,-5000);
		while(1)
		{
			set_chassis_speed(0,-80,0);    
			if((HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 0&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 0))break;
		}
		set_chassis_speed(0,-80,0);
		HAL_Delay(1000);
		hit_bar_blue();
		move_to_bar_left_blue();
		distinguish_blue();
		distinguish_blue();
		distinguish_blue();
		distinguish_blue();
		distinguish_blue();
		stack_transfer_blue();
		hit_bar_blue();
		move_to_bar_left_blue();
		get_qrcode();
		hit_bar_blue();
		get_scores_qrcode_blue();
		
		set_chassis_speed(-50,0,0);
		delay_ms(250);
		set_chassis_speed(0,0,0);
		set_imu_status(&attitude,true);
		delay_ms(500);
		while(1)
		{
			set_chassis_speed(0,-80,0);
			if((HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 1&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 1))break;
		}
		set_chassis_speed(0,-80,0);
		HAL_Delay(1500);
		set_chassis_speed(0,-120,0);
		HAL_Delay(1650);
		set_chassis_speed(0,0,0);
		delay_ms(300);
		set_chassis_speed(-80,0,0);
		delay_ms(1800);
//		while(1)
//	 {
//		set_chassis_speed(-50,0,0);
//		read_rowbar();
//		read_verticalbar();
//		if(count_verticalbar_message()>4)break;
//	 }
//	while(1)
//	{
//		set_chassis_speed(-50,0,0);
//		read_rowbar();
//		read_verticalbar();
//		if(count_verticalbar_message()<3)break;
//	}
//	while(1)
//	{
//		set_chassis_speed(50,0,0);
//		read_rowbar();
//		read_verticalbar();
//		if(count_verticalbar_message()>3)break;
//	}
//	set_chassis_speed(30,0,0);
//	HAL_Delay(850);
		
		set_chassis_speed(0,0,0);
		delay_ms(300);
//		set_imu_status(&attitude,false);
}

void blue_or_red(void)
{
	while(1)
	{
		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 0)
		{
			red_bit = 0x01;
			break;
		}
		
		if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == 0)
		{
			blue_bit = 0x01;
			break;
		}
	}
	if(red_bit == 0x01)
	{
		distinguish_red();
		distinguish_red();
		rode_red_test();
		set_chassis_speed(0,0,0);
		delay_ms(300);
//		set_imu_status(&attitude,false);
	}
	
	if(blue_bit == 0x01)
	{
			rode_blue_test();
			set_chassis_speed(0,0,0);
			delay_ms(300);
			set_imu_status(&attitude,false);
	}
}
