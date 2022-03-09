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
	SIXTEENTH_STEP = 0x08
}microstep_resolition;

typedef enum{
	CW      = 0x00,
	CCW
}motor_direction;

#ifdef __cplusplus
}
#endif

#endif
