#ifndef __TRACKBOARD_H__
#define __TRACKBOARD_H__

#include "usart.h"
#include <stdbool.h>

/* ѭ����id��Ϣ */
typedef enum {      
    ROW_BAR,
    VERTICAL_BAR,
} bar_id_t;

/* ѭ��������Ϣ */
typedef struct {
  UART_HandleTypeDef *huart;//û�� 
  int16_t div;
  bar_id_t id;//�������� 
  bool ttl_msg[9];//����ô��ԭ��д��ת���������� 
  bool status;
} TRACKINGBOARD_t;

extern TRACKINGBOARD_t row_bar;
extern TRACKINGBOARD_t vertical_bar;

void receive_trackboard_Init(TRACKINGBOARD_t *trackboard);//��ʼ��dma��û�� 
void receive_trackboard_IRQ(TRACKINGBOARD_t *trackboard);//dma�ж�û�� 
void Get_trackboard(TRACKINGBOARD_t *trackboard);//���� 
#endif
