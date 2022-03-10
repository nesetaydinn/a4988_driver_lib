#ifndef TYPE_DEFINATIONS_H_
#define TYPE_DEFINATIONS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "stdint.h"
#include "stdbool.h"

#include "enum_definations.h"


typedef uint8_t motor_speed_t;

typedef struct{
	GPIO_TypeDef * port;
	uint16_t pin;
}motor_pins_t;

typedef struct{
	motor_pins_t step_pins[0x03];
}motor_ms_pins_t;

typedef struct{
	microstep_resolition microstepping_state;
	motor_direction direction_state;
	motor_speed_t motor_speed;
}motor_state_t;

typedef struct{
	uint8_t is_set_ms_pins:1;
	uint8_t is_set_dir_pin:1;
	uint8_t is_set_enable_pin:1;
}pin_manager_t;

typedef struct{
	TIM_HandleTypeDef * htim;
	uint32_t htim_channel;
	int32_t step_count;
	int32_t step_req;
	motor_ms_pins_t * microstepping_pins;
	motor_pins_t * dir_pin;
	motor_state_t driver_state;
	motor_pins_t * enable_pin;
	pin_manager_t pins_check;
	bool is_pwm_work;
	uint8_t pwm_width;
}a4988_t;

#ifdef __cplusplus
}
#endif

#endif
