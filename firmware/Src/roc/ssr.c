/*
 * ssr.c
 *
 *  Created on: 16.03.2019
 *      Author: Johannes
 */

#include "roc/ssr.h"
#include "stm32f0xx_hal.h"

static uint8_t ssr_state = 0;

static void update_GPIO(void);

/*
 * Toggles the SSR
 */
void ssr_toggle(void)
{
	ssr_state = !ssr_state;
	update_GPIO();
}

/*
 * Enables the SSR
 */
void ssr_enable(void)
{
	ssr_state = 1;
	update_GPIO();
}

/*
 * Disables the SSR
 */
void ssr_disable(void)
{
	ssr_state = 0;
	update_GPIO();
}

/*
 * Gets the current SSR state
 */
uint8_t ssr_get_state(void)
{
	return ssr_state;
}

/*
 * Updates the GPIO
 */
static void update_GPIO(void)
{
	HAL_GPIO_WritePin(SSR_GPIO_PORT, SSR_GPIO_PIN, ssr_state);
}
