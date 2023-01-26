#include "usmart.h"
#include "usmart_str.h"
#include "main.h"
////////////////////////////�û�������///////////////////////////////////////////////
//������Ҫ�������õ��ĺ�����������ͷ�ļ�(�û��Լ����) 
#include "wheel_config.h"
#include "wheel_pwm.h"
#include "wheel.h"
#include "wheel_task.h"
#include "turn_task.h"
#include "lsc.h"
								 
extern void led_set(u8 sta);
extern void test_fun(void(*ledset)(u8),u8 sta);										  
//�������б��ʼ��(�û��Լ����)
//�û�ֱ������������Ҫִ�еĺ�����������Ҵ�
struct _m_usmart_nametab usmart_nametab[]=
{
#if USMART_USE_WRFUNS==1 	//���ʹ���˶�д����
	(void*)read_addr,"u32 read_addr(u32 addr)",
	(void*)write_addr,"void write_addr(u32 addr,u32 val)",	 
#endif		   
	
    (void*)set_motor1val,"void set_motor1val(uint16_t val)",
	  (void*)set_motor_speed,"void set_motor_speed(uint_16 num, int32_t speed)",
		(void*)set_chassis_speed,"void set_chassis_speed (float x, float y, float w)",
		(void*)set_motor,"void set_motor(uint16_t speed)",
		(void*)move_by_encoder,"void move_by_encoder(int  direct, int val)",
//		(void*)set_motor1_pid,"void set_motor1_pid(uint16_t num,float p,float i,float d)",
		(void*)span,"void span(int store_id)",
		(void*)servogroup_Init,"void servogroup_Init(void)",
};						  
///////////////////////////////////END///////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
//�������ƹ�������ʼ��
//�õ������ܿغ���������
//�õ�����������
struct _m_usmart_dev usmart_dev=
{
	usmart_nametab,
	usmart_init,
	usmart_cmd_rec,
	usmart_exe,
	usmart_scan,
	sizeof(usmart_nametab)/sizeof(struct _m_usmart_nametab),//��������
	0,	  	//��������
	0,	 	//����ID
	1,		//������ʾ����,0,10����;1,16����
	0,		//��������.bitx:,0,����;1,�ַ���	    
	0,	  	//ÿ�������ĳ����ݴ��,��ҪMAX_PARM��0��ʼ��
	0,		//�����Ĳ���,��ҪPARM_LEN��0��ʼ��
};   



















