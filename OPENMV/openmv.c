#include "openmv.h"
#include "time_delay.h"

#define HeadByte1  0x2C      //��������֡֡ͷ1
#define HeadByte2  0x12      //��������֡֡ͷ2
#define CmdByte    0x01      //��������֡����֡
#define StatusByte 0x02      //��������֡״̬֡
#define EndByte    0x5B      //��������֡֡β

/* ����openmv��Ϣ�ṹ�� */
OPENMV_t openmv;


uint8_t OPENMV_Rx_BUF[OPENMV_Rx_MAX_DATA_SIZE] = {0};





/**********************************************************************
  * ��������Get_openmv
  * ����: ������openmv���ص�״̬
  * ������openmv��Ϣ�ṹ��
  * ����ֵ:��
***********************************************************************/
void Get_openmv(OPENMV_t *openmv)
{
	
        if((OPENMV_Rx_BUF[0] == HeadByte1) && 
            (OPENMV_Rx_BUF[1] == HeadByte2) && 
             (OPENMV_Rx_BUF[2] == StatusByte) &&
              (OPENMV_Rx_BUF[4] == EndByte)) {
                openmv->message = OPENMV_Rx_BUF[3];
        }
}

/**********************************************************************
  * ��������tell_openmv_to_distinguish_Strip
  * ����: ����openmv ��е���Ѿ����� ���Կ�ʼʶ������ƽ̨
  * ��������
  * ����ֵ:��
***********************************************************************/
void tell_openmv_to_distinguish_Strip()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x01;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,1000);
}

/**********************************************************************
  * ��������tell_openmv_to_loosen
  * ����: ����openmv ��е���Ѿ����� �����ɿ�צ��
  * ��������
  * ����ֵ:��
***********************************************************************/
void tell_openmv_to_loosen()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x02;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,200);
}

/**********************************************************************
  * ��������tell_openmv_to_loosen
  * ����: ����openmv ��е���Ѿ����� �����ɿ�צ��
  * ��������
  * ����ֵ:��
***********************************************************************/
void tell_openmv_to_loosen2()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x09;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,200);
}

/**********************************************************************
  * ��������tell_openmv_to_loosen
  * ����: ����openmv ��е���Ѿ����� �����ɿ�צ��
  * ��������
  * ����ֵ:��
***********************************************************************/
void tell_openmv_to_loosen3()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x0A;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,200);
}

/**********************************************************************
  * ��������tell_openmv_to_distinguish_Stepped
  * ����: ����openmv ��е���Ѿ����� ���Կ�ʼʶ�����ƽ̨
  * ��������
  * ����ֵ:��
***********************************************************************/
  void tell_openmv_to_distinguish_Stepped()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x03;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,1000);
}

/**********************************************************************
  * ��������tell_claw_to_catch()
  * ����: ��е�����½�������ƽ̨��Ӧ�߶� ����צ�ӿ���ץȡ
  * ��������
  * ����ֵ:��
***********************************************************************/
void tell_claw_to_catch()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x04;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,1000);
	  delay_ms(100);
}

/**********************************************************************
  * ��������distinguish_red
  * ����: ��֪צ�� ʶ�����
  * ��������
  * ����ֵ:��
***********************************************************************/
void distinguish_red()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x05;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,1000);
}

/**********************************************************************
  * ��������distinguish_blue
  * ����: ��֪צ�� ʶ������
  * ��������
  * ����ֵ:��
***********************************************************************/
void distinguish_blue()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x06;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,1000);
}

/**********************************************************************
  * ��������tell_openmv_to_transfer
  * ����: ��֪openmv  ��ʼ�����ʶ��
  * ��������
  * ����ֵ:��
***********************************************************************/
void tell_openmv_to_transfer()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x07;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,1000);
}

/**********************************************************************
  * ��������tell_openmv_to_catch_stake()
  * ����: ��֪openmv  ��ʼ��׮��ʶ��
  * ��������
  * ����ֵ:��
***********************************************************************/
void tell_openmv_to_catch_stake()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x08;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,1000);
}

/**********************************************************************
  * ��������tell_openmv_to_transfer_blue()
  * ����: ��֪openmv  ��ʼ���볡�����ʶ��
  * ��������
  * ����ֵ:��
***********************************************************************/
void tell_openmv_to_transfer_blue()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x09;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,1000);
}

/**********************************************************************
  * ��������tell_openmv_to_transfer_red()
  * ����: ��֪openmv  ��ʼ��볡�����ʶ��
  * ��������
  * ����ֵ:��
***********************************************************************/
void tell_openmv_to_transfer_red()
{
    uint8_t command[5];
    command[0] = 0x2C;
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x00;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,1000);
}

void tell_openmv_to_catch_red_disc()
{
    uint8_t command[5];
    command[0] = 0x2C; 
    command[1] = 0x12;
    command[2] = 0x01;
    command[3] = 0x0A;
    command[4] = 0x5B;
    HAL_UART_Transmit(&huart3,command,5,1000); 
}







