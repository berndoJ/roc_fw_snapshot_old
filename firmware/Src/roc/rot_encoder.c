/*
 * rot_encoder.c
 *
 *  Created on: 21.03.2019
 *      Author: Johannes
 */

#include "roc/rot_encoder.h"
#include "roc/menu.h"
#include "stm32f0xx_hal.h"

#define ENCODER_DIR_CONST 0x00

static uint8_t a_toggled = 0;
static uint8_t b_toggled = 0;

void HAL_GPIO_EXTI_Callback(uint16_t gpio_pin)
{
	if (gpio_pin == GPIO_PIN_8)
	{
		// Switch
		rot_enc_sw = 1;
	}
	else if (gpio_pin == GPIO_PIN_5)
	{
		// A
		if (b_toggled)
		{
			b_toggled = 0;
			if (ENCODER_DIR_CONST)
				rot_enc_turns++;
			else
				rot_enc_turns--;
		}
		else
		{
			a_toggled = 1;
		}
	}
	else if (gpio_pin == GPIO_PIN_4)
	{
		// B
		if (a_toggled)
		{
			a_toggled = 0;
			if (!ENCODER_DIR_CONST)
				rot_enc_turns++;
			else
				rot_enc_turns--;
		}
		else
		{
			b_toggled = 1;
		}
	}
}
