#ifndef ENUM_DEFINATIONS_H_
#define ENUM_DEFINATIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

typedef enum{
	FULL_STEP      = 0x00,
	HALF_STEP		     ,
	QUARTER_STEP	     ,
	EIGHTH_STEP		     ,
	SIXTEENTH_STEP = 0x07
}microstep_resolition;

typedef enum{
	CW      = 0x00,
	CCW
}motor_direction;

typedef enum{
	STM32_TIM_1 = 0x40012c00,
	STM32_TIM_2 = 0x40000000,
	STM32_TIM_3 = 0x40000400,
	STM32_TIM_4 = 0x40000800,
	STM32_TIM_5 = 0x40000c00,
	STM32_TIM_6 = 0x40001000,
	STM32_TIM_7 = 0x40001400,
	STM32_TIM_8 = 0x40013400,
	STM32_TIM_9 = 0x40014c00,
	STM32_TIM_10 = 0x40015000,
	STM32_TIM_11 = 0x40015400,
	STM32_TIM_12 = 0x40001800,
	STM32_TIM_13 = 0x40001c00,
	STM32_TIM_14 = 0x40002000,
}stm32_timers;


typedef enum{
	STM32_TIM_CHANNEL_1   = 0x00000000U,
	STM32_TIM_CHANNEL_2   = 0x00000004U,
	STM32_TIM_CHANNEL_3   = 0x00000008U,
	STM32_TIM_CHANNEL_4   = 0x0000000CU,
	STM32_TIM_CHANNEL_ALL = 0x0000003CU
}stm32_timer_channels;

#ifdef __cplusplus
}
#endif

#endif
