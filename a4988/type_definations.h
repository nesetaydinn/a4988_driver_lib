#ifndef TYPE_DEFINATIONS_H_
#define TYPE_DEFINATIONS_H_

#include "main.h"

typedef struct{
	GPIO_TypeDef * port;
	uint16_t pin;
}motor_pins;

#endif
