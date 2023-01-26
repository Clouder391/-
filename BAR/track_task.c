#include "track_task.h"

pid_data_t track_pid_data;

/* ѭ��pid���Ʋ��� */
pid_paramer_t track_pid_paramer = {
    .integrate_max = 5,
    .kp = 2.5,
    .ki = 0,
    .kd = 0.1,
    .control_output_limit = 40
};

/* ����ѭ��ƫ��ֵ����Ȩ��*/
float row_weight[9] = {0,-4,-3,-2,-1,1,2,3,4};   //��ƫ�����  ��ƫ�����
float vertical_weight[9] = {0,-4,-3,-2,-1,1,2,3,4};    //��ƫ�����  ��ƫ�����
												
/**********************************************************************
  * ��������set_track_status
  * ����: �����Ƿ���ѭ��
  * ������track_pid_data�ṹ��   ״̬
  * ����ֵ:��
***********************************************************************/
void set_track_status(TRACKINGBOARD_t *trackboard,bool status)
{
    trackboard->status = status;
}

/**********************************************************************
  * ��������track_pid_data_init
  * ����: ��ʼ��ѭ��pid����
  * ������track_pid_data�ṹ��
  * ����ֵ:��
***********************************************************************/
void track_pid_data_init(pid_data_t *track_pid_data)
{
    track_pid_data->expect = 0;
    track_pid_data->feedback = 0;

    track_pid_data->err = 0;
    track_pid_data->last_err = 0;
    track_pid_data->last2_err=0;
    track_pid_data->integrate = 0;
    track_pid_data->delta = 0;
    track_pid_data->dis_err = 0;

    track_pid_data->control_output = 0;

    track_pid_data->short_circuit_flag = 0;
    track_pid_data->err_callback = NULL;
    track_pid_data->pri_data = NULL;
}

/**********************************************************************
  * ��������calculate_diviation
  * ����: ����ѭ�����ƫ��ֵ
  * ��������ƽ��Ϣ����   ����Ȩ��
  * ����ֵ:ƫ��·��ֵ
***********************************************************************/
int calculate_diviation(TRACKINGBOARD_t *trackboard,float weight[])
{
    int div = 0;
    for(int i=1;i<=8;i++){
        div += trackboard->ttl_msg[i] * weight[i];
    }
    return div;
}

/**********************************************************************
  * ��������track_pid()
  * ����: ѭ��pid
  * ��������
  * ����ֵ:��
***********************************************************************/
int track_pid(TRACKINGBOARD_t *trackboard,float weight[])
{
    if(trackboard->status == true) {
        track_pid_data.expect = 0;
        track_pid_data.feedback = calculate_diviation(trackboard,weight);        
        return pid_positional(&track_pid_data, &track_pid_paramer);    
    }
    else return 0;
}

