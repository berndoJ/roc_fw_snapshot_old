/*
 * menu_reflow_profiles.c
 *
 *  Created on: 21.03.2019
 *      Author: Johannes
 */

#include "roc/menus/menu_reflow_profiles.h"
#include "roc/menus/menu_reflow_confirm.h"
#include "roc/menu.h"
#include "roc/display.h"
#include "roc/reflow_profiles.h"

static uint8_t selected_item_index = 0;
static uint8_t menu_item_count = 2;

static uint8_t selected_profile_id = 0;
static uint8_t* selected_profile = 0;
static uint8_t profile_count = 1;
static uint8_t scroll_item_0 = 0;

static uint8_t menu_mode = ROC_MENU_REFLOW_PROFILES_MODE_SHOW;

/*
 * Update function of this menu.
 */
void roc_menu_reflow_profiles_update(void)
{
	if (!scroll_item_0)
	{
		if (rot_enc_turns != 0)
		{
			int16_t new_index = selected_item_index;
			if (rot_enc_turns > 0)
				new_index++;
			else if (rot_enc_turns < 0)
				new_index--;
			while (new_index < 0)
				new_index = new_index + menu_item_count;
			while (new_index >= menu_item_count)
				new_index = new_index - menu_item_count;
			selected_item_index = new_index;
			rot_enc_turns = 0;
			roc_menu_reflow_profiles_redraw();
		}
		if (rot_enc_sw != 0)
		{
			switch (selected_item_index)
			{
			case 0:
				scroll_item_0 = 1;
				roc_menu_reflow_profiles_redraw();
				break;
			case 1:
				if (menu_mode == ROC_MENU_REFLOW_PROFILES_MODE_SHOW)
					roc_menu_open(ROC_MENU_ID_MAIN);
				else if (menu_mode == ROC_MENU_REFLOW_PROFILES_MODE_SELECT)
				{
					roc_menu_reflow_confirm_set_profile(selected_profile);
					roc_menu_open(ROC_MENU_ID_REFLOW_CONFRIM);
				}
				break;
			case 2:
				roc_menu_open(ROC_MENU_ID_MAIN);
				break;
			}
			rot_enc_sw = 0;
		}
	}
	else
	{
		profile_count = reflow_profiles_get_count();
		if (rot_enc_turns != 0)
		{
			int16_t new_id = selected_profile_id;
			if (rot_enc_turns > 0)
				new_id++;
			else if (rot_enc_turns < 0)
				new_id--;
			while (new_id < 0)
				new_id = new_id + profile_count;
			while (new_id >= profile_count)
				new_id = new_id - profile_count;
			selected_profile_id = new_id;
			selected_profile = reflow_profiles_get_profile(selected_profile_id);
			rot_enc_turns = 0;
			roc_menu_reflow_profiles_redraw();
		}
		if (rot_enc_sw != 0)
		{
			scroll_item_0 = 0;
			roc_menu_reflow_profiles_redraw();
			rot_enc_sw = 0;
		}
	}
}

/*
 * Redraw function of this menu.
 */
void roc_menu_reflow_profiles_redraw(void)
{
	u8g2_FirstPage(&u8g2);
	do
	{
		u8g2_SetFont(&u8g2, u8g2_font_6x10_tf);
		if (menu_mode == ROC_MENU_REFLOW_PROFILES_MODE_SHOW)
			u8g2_DrawStr(&u8g2, 1, 8, "Reflow Profiles");
		else if (menu_mode == ROC_MENU_REFLOW_PROFILES_MODE_SELECT)
			u8g2_DrawStr(&u8g2, 1, 8, "Select Reflow Profile");
		u8g2_DrawLine(&u8g2, 0, 10, 127, 10);

		// Profile name
		selected_profile = reflow_profiles_get_profile(selected_profile_id);
		char profile_name_buf[17];
		reflow_profiles_get_profile_name(selected_profile, profile_name_buf);
		if (!scroll_item_0)
		{
			u8g2_DrawStr(&u8g2, 6, 20, profile_name_buf);
		}
		else
		{
			u8g2_DrawBox(&u8g2, 5, 12, (selected_profile[0] * 6) + 1, 9);
			u8g2_SetDrawColor(&u8g2, 0);
			u8g2_DrawStr(&u8g2, 6, 20, profile_name_buf);
			u8g2_SetDrawColor(&u8g2, 1);
		}
		// Profile selector
		if (selected_item_index == 0)
		{
			display_util_draw_selector(&u8g2, 1, 19);
		}

		// Graph axis
		u8g2_DrawLine(&u8g2, 1, 25, 1, 62);
		u8g2_DrawLine(&u8g2, 1, 62, 63, 62);

		// Graph
		uint16_t total_time = reflow_profiles_get_total_time(selected_profile);
		uint16_t max_temp = reflow_profiles_get_max_temp(selected_profile);
		uint8_t cooldown_time = reflow_profiles_get_profile_cooldown_time(selected_profile);
		uint8_t prev_x = 1;
		uint8_t prev_y = 1;

		for (uint8_t i = 0; i < reflow_profiles_get_profile_sample_count(selected_profile); i++)
		{
			uint8_t x = (uint8_t)(((float)62 / (total_time + cooldown_time)) * reflow_profiles_get_time(selected_profile, i));
			uint8_t y = (uint8_t)(((float)37 / max_temp) * reflow_profiles_get_temp(selected_profile, i));
			u8g2_DrawLine(&u8g2, 1 + prev_x, 63 - prev_y, 1 + x, 63 - y);
			prev_x = x;
			prev_y = y;
		}

		u8g2_DrawLine(&u8g2, 1 + prev_x, 63 - prev_y, 62, 62);

		// Time
		char total_time_buf[16];
		sprintf(total_time_buf, "%ds", total_time);
		u8g2_DrawStr(&u8g2, 65, 32, total_time_buf);
		// Max Temp
		char max_temp_buf[16];
		sprintf(max_temp_buf, "%d°C max.", max_temp);
		u8g2_DrawStr(&u8g2, 65, 40, max_temp_buf);
		// Cool Time
		char cooldown_buf[16];
		sprintf(cooldown_buf, "%ds cool", cooldown_time);
		u8g2_DrawStr(&u8g2, 65, 48, cooldown_buf);

		// Back button
		u8g2_DrawStr(&u8g2, 102, 62, "Back");
		// Back selector
		if ((selected_item_index == 1 && menu_mode == ROC_MENU_REFLOW_PROFILES_MODE_SHOW) || (selected_item_index == 2 && menu_mode == ROC_MENU_REFLOW_PROFILES_MODE_SELECT))
		{
			display_util_draw_selector(&u8g2, 97, 61);
		}

		// Next button
		if (menu_mode == ROC_MENU_REFLOW_PROFILES_MODE_SELECT)
		{
			u8g2_DrawStr(&u8g2, 72, 62, "Next");
			if (selected_item_index == 1)
			{
				display_util_draw_selector(&u8g2, 67, 61);
			}
		}
	} while (u8g2_NextPage(&u8g2));
}

/*
 * Selects the mode of this menu.
 */
void roc_menu_reflow_profiles_set_mode(uint8_t mode)
{
	menu_mode = mode;
	selected_item_index = 0;
	selected_profile_id = 0;
	switch (mode)
	{
	case ROC_MENU_REFLOW_PROFILES_MODE_SHOW:
		menu_item_count = 2;
		break;
	case ROC_MENU_REFLOW_PROFILES_MODE_SELECT:
		menu_item_count = 3;
		break;
	}
}
