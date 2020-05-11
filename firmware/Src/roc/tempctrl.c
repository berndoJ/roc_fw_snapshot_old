/*
 * tempctrl.c
 *
 *  Created on: 23.03.2019
 *      Author: Johannes
 */

#include "roc/tempctrl.h"
#include "roc/ssr.h"
#include "roc/tc.h"
#include "roc/menus/menu_reflow.h"
#include "roc/debug.h"

#define ROC_TEMPCTRL_LOWER_PADDING_TEMP 10
#define ROC_TEMPCTRL_UPPER_PADDING_TEMP 5

#define ROC_TEMPCTRL_HEATER_OFF 0x00
#define ROC_TEMPCTRL_HEATER_ON 0x01
#define ROC_TEMPCTRL_HEATER_PULSE 0x02

static uint8_t ctrl_active = 0;

static uint16_t current_avg_temp = 0;
static uint16_t current_goal_temp = 0;

static uint8_t heater_mode = ROC_TEMPCTRL_HEATER_OFF;

/*
 * Updates the temperature control
 */
void tempctrl_update(tc_info_t t1, tc_info_t t2, uint16_t set_temp)
{
	/*if (t1.fault == 1 && t2.fault == 1)
	{
		ctrl_active = 0;
	}
	else if (t1.fault == 1)
	{
		current_avg_temp = (uint16_t)t2.temp;
		current_goal_temp = set_temp;
	}
	else if (t2.fault == 1)
	{
		current_avg_temp = (uint16_t)t1.temp;
		current_goal_temp = set_temp;
	}
	else
	{
		current_avg_temp = (uint16_t)((t1.temp + t2.temp) / 2);
		current_goal_temp = set_temp;
	}*/
	current_avg_temp = (uint16_t) t1.temp;
	current_goal_temp = set_temp;
}

/*
 * Ticks the temperature control (This updates the heater)
 */
void tempctrl_tick(void)
{
	if (current_avg_temp < current_goal_temp - ROC_TEMPCTRL_LOWER_PADDING_TEMP)
	{
		heater_mode = ROC_TEMPCTRL_HEATER_ON;
	}
	else if (current_avg_temp > current_goal_temp + ROC_TEMPCTRL_UPPER_PADDING_TEMP)
	{
		heater_mode = ROC_TEMPCTRL_HEATER_OFF;
	}
	else
	{
		heater_mode = ROC_TEMPCTRL_HEATER_PULSE;
	}
}

/*
 * SSR-control tick function. Should be called every 2.5s
 */
void tempctrl_ssr_tick(void)
{
	if (ctrl_active == 1)
	{
		uint8_t ssr_state_before = ssr_get_state();
		switch (heater_mode)
		{
		case ROC_TEMPCTRL_HEATER_OFF:
			if (ssr_state_before == 1)
			{
				ssr_disable();
			}
			break;
		case ROC_TEMPCTRL_HEATER_ON:
			if (ssr_state_before == 0)
			{
				ssr_enable();
			}
			break;
		case ROC_TEMPCTRL_HEATER_PULSE:
			ssr_toggle();
			break;
		}
		if (ssr_state_before != ssr_get_state())
		{
			roc_menu_reflow_update_heater_status(ssr_get_state());
		}
	}
}

/*
 * Enables the temperature control
 */
void tempctrl_enable(void)
{
	ctrl_active = 1;
}

/*
 * Disables the temperature control
 */
void tempctrl_disable(void)
{
	ctrl_active = 0;
}
