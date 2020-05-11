/*
 * menu_reflow.c
 *
 *  Created on: 22.03.2019
 *      Author: Johannes
 */

#include "roc/menus/menu_reflow.h"
#include "roc/display.h"
#include "roc/menu.h"
#include "roc/reflow_profiles.h"
#include "roc/tc.h"
#include "roc/ssr.h"
#include "roc/tempctrl.h"
#include "roc/debug.h"

#define ROC_TEMPCTRL_TEMP_COOLDOWN 25

#define ROC_MENU_REFLOW_HW_UPDATE_MS 500

static uint8_t* selected_reflow_profile = 0;

static uint16_t hw_update_ticks = 0;
static uint16_t time_update_ticks = 0;

static tc_info_t temp_1_info;
static tc_info_t temp_2_info;
static uint16_t set_temp = 0;

static uint8_t heater_enabled = 0;

static uint8_t timer_started = 0;
static uint16_t time_since_start = 0;
static uint16_t time_total = 0;

static void roc_menu_reflow_update_hw(void);
static void roc_menu_reflow_update_time(void);

/*
 * Update function of this menu.
 */
void roc_menu_reflow_update(void)
{
	if (rot_enc_sw != 0)
	{
		tempctrl_disable();
		timer_started = 0;
		time_since_start = 0;
		hw_update_ticks = 0;
		roc_menu_open(ROC_MENU_ID_MAIN);
		rot_enc_sw = 0;
	}

	time_update_ticks++;
	if (time_update_ticks >= (1000 / ROC_MENU_UPDATE_DELAY))
	{
		// Every 1000ms
		roc_menu_reflow_update_time();
		time_update_ticks = 0;
	}

	hw_update_ticks++;
	if (hw_update_ticks >= (ROC_MENU_REFLOW_HW_UPDATE_MS / ROC_MENU_UPDATE_DELAY))
	{
		// Every 500ms
		roc_menu_reflow_update_hw();
		hw_update_ticks = 0;
	}
}

/*
 * Redraw function of this menu.
 */
void roc_menu_reflow_redraw(void)
{
	u8g2_FirstPage(&u8g2);
	do
	{
		u8g2_SetFont(&u8g2, u8g2_font_6x10_tf);
		u8g2_DrawStr(&u8g2, 1, 8, "Reflow");
		u8g2_DrawLine(&u8g2, 0, 10, 127, 10);

		// Cancel button
		u8g2_DrawStr(&u8g2, 91, 62, "Cancel");
		display_util_draw_selector(&u8g2, 86, 61);

		// Graph °C/div
		char graph_div_buf[16];
		sprintf(graph_div_buf, "%d°C/div", 25);
		u8g2_DrawStr(&u8g2, 1, 62, graph_div_buf);

		// Graph axis
		u8g2_DrawLine(&u8g2, 1, 12, 1, 52);
		u8g2_DrawLine(&u8g2, 1, 52, 63, 52);

		// Time
		char time_buf[16];
		sprintf(time_buf, "%ds/%ds", time_since_start, time_total);
		u8g2_DrawStr(&u8g2, 65, 20, time_buf);

		// Temp 1
		char temp1_buf[16];
		if (temp_1_info.tc_not_connected)
			sprintf(temp1_buf, "T1: N.C.");
		/*else if (temp_1_info.fault)
			sprintf(temp1_buf, "T1: SHORT");*/
		else
			sprintf(temp1_buf, "T1: %d°C", (uint16_t) temp_1_info.temp);
		u8g2_DrawStr(&u8g2, 65, 30, temp1_buf);

		// Temp 2
		char temp2_buf[16];
		if (temp_2_info.tc_not_connected)
			sprintf(temp2_buf, "T2: N.C.");
		/*else if (temp_2_info.fault)
			sprintf(temp2_buf, "T2: SHORT");*/
		else
			sprintf(temp2_buf, "T2: %d°C", (uint16_t) temp_2_info.temp);
		u8g2_DrawStr(&u8g2, 65, 40, temp2_buf);

		// Temp target
		char temp_target_buf[16];
		sprintf(temp_target_buf, "S: %d°C", set_temp);
		u8g2_DrawStr(&u8g2, 65, 50, temp_target_buf);

		// Heater indicator
		if (heater_enabled == 1)
		{
			u8g2_DrawStr(&u8g2, 59, 62, "H");
		}
	} while (u8g2_NextPage(&u8g2));
}

/*
 * Setter for the reflow profile.
 */
void roc_menu_reflow_set_profile(uint8_t* reflow_profile)
{
	selected_reflow_profile = reflow_profile;
}

/*
 * Starts the timer and the whole reflow process.
 */
void roc_menu_reflow_start(void)
{
	timer_started = 1;

	// Update the profile's total time
	time_total = reflow_profiles_get_total_time(selected_reflow_profile) + reflow_profiles_get_profile_cooldown_time(selected_reflow_profile);

	roc_menu_reflow_update_hw();

	tempctrl_enable();
}

/*
 * Updates the heater status.
 */
void roc_menu_reflow_update_heater_status(uint8_t status)
{
	heater_enabled = status;
}

/*
 * Updates all necessary hw info and updates the lcd afterwards.
 */
static void roc_menu_reflow_update_hw(void)
{
	// Update temps.
	temp_1_info = tc_read_temp(TC_ID_0);
	temp_2_info = tc_read_temp(TC_ID_1);

	// Evaluate the set temperature
	for (uint8_t i = 0;i < reflow_profiles_get_profile_sample_count(selected_reflow_profile); i++)
	{
		uint16_t sample_time = reflow_profiles_get_time(selected_reflow_profile,i);
		if (time_since_start <= sample_time)
		{
			set_temp = reflow_profiles_get_temp(selected_reflow_profile, i);
			break;
		}
		if (i == reflow_profiles_get_profile_sample_count(selected_reflow_profile) - 1)
		{
			// No more data-point has been found
			set_temp = ROC_TEMPCTRL_TEMP_COOLDOWN; // Cooldown temperature
		}
	}

	// Update tempctrl
	tempctrl_update(temp_1_info, temp_2_info, set_temp);

	roc_menu_reflow_redraw();
}

/*
 * Updates the time of the reflow menu (adds one second => This method should be called every 1000ms)
 */
static void roc_menu_reflow_update_time(void)
{
	// Update time.
	if (timer_started)
		time_since_start++;
}
