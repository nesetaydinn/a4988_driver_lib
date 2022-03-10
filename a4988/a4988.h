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
 * @param tim_channel Timer channel value
 * @return a4988_t Step motor driver object
 * */
a4988_t a4988DrvInit(TIM_HandleTypeDef * htim, motor_pins_t * dir_pin, uint32_t tim_channel);

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

/* @brief Set new resolution value
 * @param drv a4988_t object
 * @param resolition_val Step motor resolution value
 * @return
 * */
void a4988DrvSetNewResolution(a4988_t * drv, uint8_t resolition_val);

/* @brief Set motor state enable or disable
 * @param drv a4988_t object
 * @param state Step motor driver enable or disable state
 * @return
 * */
void a4988DrvSetMotorState(a4988_t * drv, bool state);

/* @brief Set motor speed and direction
 * @param drv a4988_t object
 * @param step Set motor step
 * @param direction Step motor direction
 * @return
 * */
void a4988DrvSetStepAndDirection(a4988_t * drv, uint32_t step, bool direction);

/* @brief Set pwm pulse width
 * @param drv a4988_t object
 * @param pulse_width Pwm pulse width
 * @return
 * */
void a4988DrvSetPwmPulseWidth(a4988_t * drv, uint8_t pulse_width);

#ifdef __cplusplus
}
#endif

#endif
