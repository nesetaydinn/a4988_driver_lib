#ifndef A4988_H_
#define A4988_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "main.h"
#include "stdbool.h"

#include "type_definations.h"
#include "enum_definations.h"

/* @brief Create a a4988_t object
 * @param htim Pwm timer channel
 * @param dir_pin Direction pin
 * @return a4988_t Step motor driver object
 * */
a4988_t a4988DrvInit(TIM_HandleTypeDef * htim, motor_pins_t * dir_pin);

/* @brief Set microstepping pins to a a4988_t object
 * @param drv a4988_t object
 * @param microstepping_pins Microstepping pins object
 * @return
 * */
void a4988DrvSetMicrosteppingPins(a4988_t * drv, motor_ms_pins_t * microstepping_pins);

/* @brief Set enable pin to a a4988_t object
 * @param drv a4988_t object
 * @param enable_pin Motor enable pin
 * @return
 * */
void a4988DrvSetEnablePin(a4988_t * drv, motor_pins_t * enable_pin);

#ifdef __cplusplus
}
#endif

#endif
