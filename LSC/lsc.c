#include "lsc.h"

/**********************************************************************
  * ��������cmd_action_group_run
  * ����: ���Ͷ���������
  * ��������������   ִ�д���
  * ����ֵ:��
***********************************************************************/
void cmd_action_group_run(uint8_t action_group,uint16_t number)
{
    uint8_t command[7];
    command[0] = 0x55;
    command[1] = 0x55;
    command[2] = 0x05;
    command[3] = 0x06;
    command[4] = action_group;
    command[5] = number&0XFF;
    command[6] = (number>>8)&0XFF;
    HAL_UART_Transmit(&huart8,command,7,1000);
}

/**********************************************************************
  * ��������cmd_action_group_speed
  * ����: ���ڶ�����ִ���ٶ�
  * ��������������   ִ���ٶ�
  * ����ֵ:��
***********************************************************************/
void cmd_action_group_speed(uint8_t action_group,uint16_t speed)
{
    uint8_t command[7];
    command[0] = 0x55;
    command[1] = 0x55;
    command[2] = 0x05;
    command[3] = 0x0B;
    command[4] = action_group;
    command[5] = speed&0XFF;
    command[6] = (speed>>8)&0XFF;
    HAL_UART_Transmit(&huart8,command,7,1000);  //���Ͷ������ź�ִ���ٶ�
}

/**********************************************************************
  * ��������cmd_action_group_stop
  * ����: ����ֹͣ����
  * ��������   
  * ����ֵ:��
***********************************************************************/
void cmd_action_group_stop()
{
    uint8_t command[4];
    command[0] = 0x55;
    command[1] = 0x55;
    command[2] = 0x02;
    command[3] = 0x07;
    HAL_UART_Transmit(&huart8,command,4,1000);
}

/**********************************************************************
  * ��������servogroup_Init
  * ����: �������ʼ��
  * ��������   
  * ����ֵ:��
***********************************************************************/
void servogroup_Init()
{
    cmd_action_group_run(0x00,1);   //���Ͷ�����ָ��0x00 ִ��һ��
}

//����ƽ̨���
void servogroup_Stepped_distinguish()
{
    cmd_action_group_speed(0x01,275);     //�趨������0x01��ִ���ٶ���175
    cmd_action_group_run(0x01,1);        //ִ��һ�ζ�����0x01
}

//�ӵڶ�ƽ̨����
void servogroup_catch_Steppedplatform_2()
{
    cmd_action_group_speed(0x02,150);
    cmd_action_group_run(0x02,1);
}

void servogroup_catch_Steppedplatform_1()
{
    cmd_action_group_speed(0x03,150);
    cmd_action_group_run(0x03,1);
}

void servogroup_catch_Steppedplatform_3()
{
    cmd_action_group_speed(0x04,150);
    cmd_action_group_run(0x04,1);
}

void servogroup_catch_Steppedplatform_4()
{
    cmd_action_group_speed(0x33,150);
    cmd_action_group_run(0x33,1);
}

void servogroup_catch_Steppedplatform_5()
{
    cmd_action_group_speed(0x35,150);
    cmd_action_group_run(0x35,1);
}

void servogroup_catch_Steppedplatform_6()
{
    cmd_action_group_speed(0x36,150);
    cmd_action_group_run(0x36,1);
}

//��������Բ�̻�
void servogroup_catch_Stripplatform()
{
    cmd_action_group_speed(0x15,350);       
    cmd_action_group_run(0x15,1);         
}

//������Բ�̻�����ȡid
void servogroup_ic_Stripplatform()
{
    cmd_action_group_speed(0x17,200);       
    cmd_action_group_run(0x17,1);         
}
