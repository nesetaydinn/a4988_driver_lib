#ifndef TYPE_DEFINATIONS_H_
#define TYPE_DEFINATIONS_H_

#include "main.h"
#include "stdint.h"

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
	TIM_HandleTypeDef * htim;
	motor_ms_pins_t microstepping_pins;
	motor_pins_t dir_pin;
	motor_state_t driver_state;
}motor_pins_t;


#endif
