#include "qrcode.h"
#include "stdio.h"


QRCODE_t qrcode ;

/* ���ݰ������Ϣ���� */
#define QRCODE_Rx_MAX_DATA_SIZE 20


unsigned char Uart2RxDataConut = 0;
uint8_t QRCODE_Rx_BUF[QRCODE_Rx_MAX_DATA_SIZE] = {0};
unsigned char Rx2Flag = 0;

/**********************************************************************
  * ��������Get_qrcode
  * ����: ��������ά�뷢������
  * ��������ά����Ϣ�ṹ��
  * ����ֵ:�� 
***********************************************************************/
uint8_t Get_qrcode(QRCODE_t *qrcode)
{
	uint8_t qrstatus;
	qrstatus = 0x00;
	if(Rx2Flag == 1)
	{
		Rx2Flag = 0;
		if(QRCODE_Rx_BUF[0] == 'H'&&QRCODE_Rx_BUF[1] == 'E'&&QRCODE_Rx_BUF[2] == 'A'&&QRCODE_Rx_BUF[3] == 'D')
			{
				if(QRCODE_Rx_BUF[5] == 'T'&&QRCODE_Rx_BUF[6] == 'A'&&QRCODE_Rx_BUF[7] == 'I'&&QRCODE_Rx_BUF[8] == 'L')
				{
					qrcode->message = QRCODE_Rx_BUF[4];        //��ά�봫�ص����ַ�����
					qrstatus = 0x01;
					printf("ok!");
				}
			}
			for(int i = 0;i < 9; i++)
			{
				QRCODE_Rx_BUF[i]=0x00;
			}
			Uart2RxDataConut = 0;
		}
	return qrstatus;
}

/**********************************************************************
  * ��������QR_trigger_1
  * ����: ���������� �����1ģʽ����������󴥷�ʶ������ʶ���ɹ�����
          ����������ʶ��ʱ���������յ��������ֹͣ�����豸ֹͣʶ����
  * ��������
  * ����ֵ:��
***********************************************************************/
void QR_trigger_1(){  
	uint8_t command[12]={'$','1','0','8','0','0','0','-','A','D','B','0'};      //���Ͷ�ά����������$108000-ADB0
    HAL_UART_Transmit(&huart7,command,12,500);
}

/**********************************************************************
  * ��������QR_trigger_2
  * ����: ��������󴥷�����ʶ����ֻ�е����͡������ֹͣ�����豸�Ż�ֹͣʶ����
  * ��������
  * ����ֵ:��
***********************************************************************/
void QR_trigger_2(){
	uint8_t command[12]={'$','1','0','8','0','0','1','-','9','E','8','0'};      //���Ͷ�ά����������$108000-ADB0
    HAL_UART_Transmit(&huart7,command,12,500);
}

/**********************************************************************
  * ��������QR_trigger_2
  * ����: ��������󴥷�����ʶ����ֻ�е����͡������ֹͣ�����豸�Ż�ֹͣʶ����
  * ��������
  * ����ֵ:��
***********************************************************************/
void QR_trigger_stop(){
	uint8_t command[12]={'$','1','0','8','0','0','3','-','F','8','E','3'};      //���Ͷ�ά����������$108000-ADB0
    HAL_UART_Transmit(&huart7,command,12,500);
}

/**********************************************************************
  * ��������QR_restart
  * ����: ������ά���豸
  * ��������
  * ����ֵ:��
***********************************************************************/
void QR_restart(){  
	uint8_t command[12]={'$','0','1','0','5','0','0','-','E','E','1','9'};      //���Ͷ�ά����������
    HAL_UART_Transmit(&huart7,command,12,500);
}

/**********************************************************************
  * ��������QR_user
  * ����: �ָ��û�Ĭ������
  * ��������
  * ����ֵ:��
***********************************************************************/
void QR_restore_default(){     
	uint8_t command[12]={'$','0','1','0','2','0','2','-','D','9','5','6'};      //�ָ��û�����
    HAL_UART_Transmit(&huart7,command,12,500);
}

void send_qrcode(QRCODE_t *qrcode)
{
	uint8_t num=0;
	num=qrcode->message;
	HAL_UART_Transmit(&huart1,&num,1,0xffff); 
}




void reciveqrcode_IRQ(void)
{
// 	QRCODE_Rx_BUF[Uart2RxDataConut]=qrcode_Rx_buffer;
//	Uart2RxDataConut++;
//	if(Uart2RxDataConut >= QRCODE_Rx_MAX_DATA_SIZE)
//	{
//		Uart2RxDataConut = 0;
//	}
//	if(Uart2RxDataConut == 0x09) 
//	{
//		Rx2Flag = 1;
//	}
//  HAL_UART_Receive_IT(&huart7,&qrcode_Rx_buffer, 1);
	printf("ok");
}
