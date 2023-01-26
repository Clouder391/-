#include "wheel_task.h"
#include "usart.h"

extern double motor_target[5];
//extern int val_track_front;
//extern int val_track_back;

/* �����ĸ��������pid���������� */
pid_data_t motor1_pid_data;
pid_data_t motor2_pid_data;
pid_data_t motor3_pid_data;
pid_data_t motor4_pid_data;

/* ���1�����pid���Ʋ��� */
pid_paramer_t motor1_pid_paramer = {
    .integrate_max = 7000,
    .kp = 78,
    .ki = 3.5,
    .kd = 1.8,
    .control_output_limit = 9000
};

/* ���2�����pid���Ʋ��� */
pid_paramer_t motor2_pid_paramer = {
    .integrate_max = 7000,
    .kp = 78,
    .ki = 3.5,
    .kd = 1.8,
    .control_output_limit = 9000
};

/* ���3�����pid���Ʋ��� */
pid_paramer_t motor3_pid_paramer = {
    .integrate_max = 7000,
    .kp = 78,
    .ki = 3.5,
    .kd = 1.8,
    .control_output_limit = 9000
};

/* ���4�����pid���Ʋ��� */
pid_paramer_t motor4_pid_paramer = {
    .integrate_max = 7000,
    .kp = 78,
    .ki = 3.5,
    .kd = 1.8,
    .control_output_limit = 9000
};


/**********************************************************************************************************
*�� �� ��: set_motor1_pid
*����˵��: ������usmart�ϵ���pid����
*��    ��: ������ p i d
*�� �� ֵ: ��
*��    ע: ���յ���ʱ��������pid��������ֱ�۵ı��ֳ�����������
**********************************************************************************************************/

//void set_motor1_pid(uint16_t num,float p,float i,float d)
//{
//	pid_paramer_t* motor_pid_paramer;
//	if(num == 1)
//			motor_pid_paramer = &motor1_pid_paramer;
//		else if(num == 2)
//			motor_pid_paramer = &motor1_pid_paramer;
//		else if(num == 3)
//			motor_pid_paramer = &motor1_pid_paramer;
//		else 
//			motor_pid_paramer = &motor1_pid_paramer;
//		
//		motor_pid_paramer->kp = p;
//		motor_pid_paramer->ki = i;
//		motor_pid_paramer->kd = d;
//		
//		
//}

/**********************************************************************
  * ��������motor_pid_data_init
  * ����: ��ʼ�����pid����
  * ������motor_pid_data�ṹ��
  * ����ֵ:��
***********************************************************************/
void motor_pid_data_init(pid_data_t *motor_pid_data)
{
    motor_pid_data->expect = 0;
    motor_pid_data->feedback = 0;

    motor_pid_data->err = 0;
    motor_pid_data->last_err = 0;
    motor_pid_data->last2_err=0;
    motor_pid_data->integrate = 0;
    motor_pid_data->delta = 0;
    motor_pid_data->dis_err = 0;

    motor_pid_data->control_output = 0;

    motor_pid_data->short_circuit_flag = 0;
    motor_pid_data->err_callback = NULL;
    motor_pid_data->pri_data = NULL;
}

/**********************************************************************************************************
*�� �� ��: read_freq
*����˵��: ��ȡmotor�ṹ���е�freq������
*��    ��: motor�ṹ��ĵ�ַ 
*�� �� ֵ: ���ת��Ƶ�ʣ���Ӧ�ٶȣ�
**********************************************************************************************************/
int32_t read_freq(motor_t *motor)
{   double temp = motor->freq;
    motor->freq = 0;
	return temp;
}


/**********************************************************************************************************
*�� �� ��: motor_pid
*����˵��: ���pid
*��    ��: �� 
*�� �� ֵ: ��
**********************************************************************************************************/
void motor_pid()
{
   /*����������Ŀ��ֵ*/
   motor1_pid_data.expect = motor_target[1] ;//+ val_track_front + val_track_back;
   motor2_pid_data.expect = motor_target[2] ;//+ val_track_front + val_track_back;
   motor3_pid_data.expect = motor_target[3] ;//+ val_track_front + val_track_back;
   motor4_pid_data.expect = motor_target[4] ;//+ val_track_front + val_track_back;
  
   /*��ȡ��ǰ���ת��*/
   motor1_pid_data.feedback = read_freq(&motor1);
   motor2_pid_data.feedback = read_freq(&motor2);
   motor3_pid_data.feedback = read_freq(&motor3);
   motor4_pid_data.feedback = read_freq(&motor4);
  
	/*����pid���� �������ֵע����ͨ��*/
//   set_motor_speed(4, pid_incremental(&motor4_pid_data,&motor4_pid_paramer));
//   set_motor_speed(1, pid_incremental(&motor1_pid_data,&motor1_pid_paramer));
//   set_motor_speed(2, pid_incremental(&motor2_pid_data,&motor2_pid_paramer));
//   set_motor_speed(3, pid_incremental(&motor3_pid_data,&motor3_pid_paramer));
		set_motor_speed(&motor1, pid_incremental(&motor1_pid_data,&motor1_pid_paramer));
   set_motor_speed(&motor2, pid_incremental(&motor2_pid_data,&motor2_pid_paramer));
   set_motor_speed(&motor3, pid_incremental(&motor3_pid_data,&motor3_pid_paramer));
   set_motor_speed(&motor4, pid_incremental(&motor4_pid_data,&motor4_pid_paramer));
   
   printf("%f , %f\n",motor2_pid_data.expect ,motor2_pid_data.feedback );
   // printf("%f,%f,%f,%f,%f,%f\n",motor1_pid_data.feedback,motor2_pid_data.feedback,motor3_pid_data.feedback,motor4_pid_data.feedback,motor1_pid_data.expect,motor3_pid_data.expect); 
}




