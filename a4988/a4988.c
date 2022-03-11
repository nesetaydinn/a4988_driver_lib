#include "a4988.h"

a4988_t a4988DrvInit(TIM_HandleTypeDef * htim, motor_pins_t * dir_pin, uint32_t tim_channel){
	a4988_t tmp;
	tmp.dir_pin = dir_pin;
	tmp.htim_channel = tim_channel;
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};
	TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};
	uint16_t f_psc = 0, f_arr = 255;
	uint32_t f_apb1 = HAL_RCC_GetPCLK1Freq();
	uint32_t f_apb2 = HAL_RCC_GetPCLK2Freq();
	if ((htim->Instance == (TIM_TypeDef *)(STM32_TIM_1)) || (htim->Instance == (TIM_TypeDef *)(STM32_TIM_8))  ||
		(htim->Instance == (TIM_TypeDef *)(STM32_TIM_9)) || (htim->Instance == (TIM_TypeDef *)(STM32_TIM_10)) || 
		(htim->Instance == (TIM_TypeDef *)(STM32_TIM_11)))
		f_psc = (f_apb2 / (1000 * (f_arr + 1))) - 1;
	else 
		f_psc = (f_apb1 / (1000 * (f_arr + 1))) - 1;

	htim->Init.Prescaler = f_psc;
	htim->Init.CounterMode = TIM_COUNTERMODE_UP;
	htim->Init.Period = f_arr;
	htim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim->Init.RepetitionCounter = 0;
	htim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(htim) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(htim, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Init(htim) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(htim, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if (HAL_TIM_PWM_ConfigChannel(htim, &sConfigOC, tmp.htim_channel) != HAL_OK)
	{
		Error_Handler();
	}
	sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
	sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
	sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
	sBreakDeadTimeConfig.DeadTime = 0;
	sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
	sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
	sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
	if (HAL_TIMEx_ConfigBreakDeadTime(htim, &sBreakDeadTimeConfig) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_TIM_MspPostInit(htim);
	tmp.htim = htim;
	tmp.pins_check.is_set_dir_pin = true;
	tmp.pins_check.is_set_enable_pin = false;
	tmp.pins_check.is_set_ms_pins = false;
	tmp.step_count = 0;

	return tmp;
}

void a4988DrvSetMicrosteppingPins(a4988_t * drv, motor_ms_pins_t * microstepping_pins){
	drv->microstepping_pins = microstepping_pins;
	drv->pins_check.is_set_ms_pins = true;
}

void a4988DrvSetEnablePin(a4988_t * drv, motor_pins_t * enable_pin){
	drv->enable_pin = enable_pin;
	drv->pins_check.is_set_enable_pin = true;

}

void a4988DrvSetNewResolution(a4988_t * drv, uint8_t resolition_val){
	if(drv->pins_check.is_set_ms_pins){
		for (uint8_t c = 0; c < 0x03; c++)
			HAL_GPIO_WritePin(drv->microstepping_pins->step_pins[c].port, drv->microstepping_pins->step_pins[c].pin, ((resolition_val >> c) & 0x01));
	}
}

void a4988DrvSetMotorState(a4988_t * drv, bool state){
	HAL_GPIO_WritePin(drv->enable_pin->port, drv->enable_pin->pin, state);
}
uint32_t g1, g2;
uint32_t count_ms = 0;
bool test_b;
void a4988DrvSetStepAndDirection(a4988_t * drv, uint32_t step, bool direction){
	HAL_GPIO_WritePin(drv->dir_pin->port, drv->dir_pin->pin, direction);
	drv->step_req = step;
	if(0 != step){
		HAL_TIM_PWM_Start(drv->htim, drv->htim_channel);
		while ((drv->step_count < drv->step_req) && drv->is_pwm_work){
			drv->step_count++;
			HAL_Delay(1);
		}
		HAL_TIM_PWM_Stop(drv->htim, drv->htim_channel);
		drv->step_req = 0;
		drv->step_count = 0;
		drv->htim->Instance->CCR1 = test_b;
	}
}

void a4988DrvSetPwmPulseWidth(a4988_t * drv, uint8_t pulse_width){
	drv->pwm_width = pulse_width;
	
	if(STM32_TIM_CHANNEL_ALL == (drv->htim_channel & STM32_TIM_CHANNEL_ALL)){
		drv->htim->Instance->CCR1 = drv->pwm_width;
		drv->htim->Instance->CCR2 = drv->pwm_width;
		drv->htim->Instance->CCR3 = drv->pwm_width;
		drv->htim->Instance->CCR4 = drv->pwm_width;
	}else{
		if(STM32_TIM_CHANNEL_1 == (drv->htim_channel & STM32_TIM_CHANNEL_1))
			drv->htim->Instance->CCR1 = drv->pwm_width;
		if(STM32_TIM_CHANNEL_2 == (drv->htim_channel & STM32_TIM_CHANNEL_2))
			drv->htim->Instance->CCR2 = drv->pwm_width;
		if(STM32_TIM_CHANNEL_3 == (drv->htim_channel & STM32_TIM_CHANNEL_3))
			drv->htim->Instance->CCR3 = drv->pwm_width;
		if(STM32_TIM_CHANNEL_4 == (drv->htim_channel & STM32_TIM_CHANNEL_4))
			drv->htim->Instance->CCR4 = drv->pwm_width;
	}

}
