#include<move_task.h> 
#include<main,h>

/**********************************************************************
  * ��������hit_baffle_red
  * ����: ײ������
  * ��������
  * ����ֵ:��
***********************************************************************/
void hit_baffle_red()
{
 	 while(1) 
	  {
      set_chassis_speed(-50, 0, 0);
      if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14) == 1&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 0) {
          set_chassis_speed(-15, 0, -10);
        }
        
      if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14) == 0&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 1) {
          set_chassis_speed(-15, 0, 10);
        }
      if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14) == 1&&HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 1)break;
	  }
     while(1) 
	 {
       set_chassis_speed(-50, -30, 0);
       if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 0&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 1) break;
     }	
}

/**********************************************************************
  * ��������runto_stile
  * ��  ��:������ȥ 
  * ��  ��:��
  * ����ֵ:��
***********************************************************************/
void runto_stile_red()
{
	 set_chassis_speed(-20,0,0);
	 HAL_Delay(500);
	 set_chassis_speed(-50,0,0);
	 HAL_Delay(1800);
	 set_chassis_speed(0,100,0);
	 HAL_Delay(3500);//�ߵ�����ƽ̨ǰ��
}
