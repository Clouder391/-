

/****************************************_HONSON-----------2022.8.20**************************************************************/

#include"m294.h" 
#include"usart.h"
#include"time_delay.h"


unsigned char Uart6RxBuf[UART6_RX_BUF_LEN];
unsigned char Uart6RxDataConut = 0;
unsigned char Rx6Flag = 0;
unsigned char ballID[16]={0};
extern uint8_t M294_Rx_buffer;

unsigned char ReadBlockData(unsigned char *ballID)
{
	unsigned char status;
	unsigned char i;
	unsigned char pkt[22];
	status = STATUS_ERR;
	if(Uart6RxDataConut > 0) //�жϴ����Ƿ���յ�����
	{
		if(Rx6Flag == 1)//�жϴ����Ƿ���յ�һ֡��������
		{	
			Rx6Flag = 0;
			for(i=0;i<22;i++) //�Զ������ݿ�����ݰ����ȹ̶�Ϊ22�ֽ�
			{
				pkt[i] = Uart6RxBuf[i]; //�����ڽ��������ڵ����ݸ��Ƶ�pkt������
			}
			if(pkt[21] == 0xCE)  //�ж�У����Ƿ���ȷ
			{
				if(pkt[4] == STATUS_OK)	//�ж��Ƿ���ȷ�Ķ�����
				{
					//04 16 03 20 00 22 22 22 22 22 22 22 22 22 22 22 22 22 22 22 22 CE 
					if((pkt[0] == 0x04)&&(pkt[1] == 0x16)&&(pkt[2] == 0x03)&&(pkt[3] == 0x20))//�����ݰ������ж�
					{
						for(i=0;i<16;i++)//��ȡ16�ֽ�����
						{
							ballID[i] = pkt[i+5];//������ĵ�5���ֽڿ�ʼΪ���ݣ���16�ֽ�
						}
						status = STATUS_OK;		 //�ɹ�����0
					}
				}
			}
					for(i=0;i<Uart6RxDataConut;i++)//��մ��ڽ�������
		{
			Uart6RxBuf[i] = 0x00; 
		}
		Uart6RxDataConut = 0x00;
		}
 	} 
	return status;			//����״̬
}


void recivem294_IRQ(void)
{	
	Uart6RxBuf[Uart6RxDataConut]=M294_Rx_buffer;
	Uart6RxDataConut++;
	if(Uart6RxDataConut >= UART6_RX_BUF_LEN)
	{
		Uart6RxDataConut = 0;
	}
	if(Uart6RxDataConut == 0x16)
	{
		Rx6Flag = 1;
	}
	
  HAL_UART_Receive_IT(&huart6,&M294_Rx_buffer, 1);
}


void send_ballID(uint8_t *ballID)
{
	uint8_t ballid=0;
	ballid=ballID[1];
	HAL_UART_Transmit(&huart1,&ballid,1,0xffff);
}

