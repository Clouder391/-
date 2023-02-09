#include "snow.h"

/* 定义周转舵机的结构体数据类型 */
Steering_t turnover_steering;

/**********************************************************************
 * @Name    Steering_Init
 * @declaration : 初始化周转舵机
 * @param   turnover_steering 周转舵机结构体
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void Steering_Init(Steering_t *turnover_steering){
	turnover_steering->htim= &htim8;
	turnover_steering->channel = TIM_CHANNEL_3;
	turnover_steering->Pulse=0;
	HAL_TIM_PWM_Start(turnover_steering->htim,turnover_steering->channel);
}

/**********************************************************************
 * @Name    Set_Steering_clockwise
 * @declaration : 设定周转舵机顺时针转动
 * @param   turnover_steering 周转舵机结构体
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void Set_Steering_clockwise(Steering_t *turnover_steering){
	turnover_steering->Pulse=1850;
	__HAL_TIM_SET_COMPARE(turnover_steering->htim,turnover_steering->channel,turnover_steering->Pulse);
}

/**********************************************************************
 * @Name    Set_Steering_anticlockwise
 * @declaration : 设定周转舵机逆时针转动
 * @param   turnover_steering 周转舵机结构体
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void Set_Steering_anticlockwise(Steering_t *turnover_steering){
	turnover_steering->Pulse=1150;
	__HAL_TIM_SET_COMPARE(turnover_steering->htim,turnover_steering->channel,turnover_steering->Pulse);
}

/**********************************************************************
 * @Name    Set_Steering_stop
 * @declaration : 设定周转舵机停止
 * @param   turnover_steering 周转舵机结构体
 * @retval   : 无
 * @author  hoson_stars
 ***********************************************************************/
void Set_Steering_stop(Steering_t *turnover_steering){
	turnover_steering->Pulse=1500;
	__HAL_TIM_SET_COMPARE(turnover_steering->htim,turnover_steering->channel,turnover_steering->Pulse);
}




