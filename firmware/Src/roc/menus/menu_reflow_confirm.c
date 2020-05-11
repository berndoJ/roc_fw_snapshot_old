/*
 * menu_reflow_confirm.c
 *
 *  Created on: 22.03.2019
 *      Author: Johannes
 */

#include "roc/menus/menu_reflow_confirm.h"
#include "roc/menus/menu_reflow.h"
#include "roc/reflow_profiles.h"
#include "roc/display.h"
#include "roc/menu.h"

static uint8_t* selected_reflow_profile = 0;

static uint8_t selected_item_index = 0;
static uint8_t menu_item_count = 2;

/*
 * Update function of this menu.
 */
void roc_menu_reflow_confirm_update(void)
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
		roc_menu_reflow_confirm_redraw();
	}
	if (rot_enc_sw != 0)
	{
		switch (selected_item_index)
		{
		case 0:
			roc_menu_reflow_set_profile(selected_reflow_profile);
			roc_menu_reflow_start();
			roc_menu_open(ROC_MENU_ID_REFLOW);
			break;
		case 1:
			roc_menu_open(ROC_MENU_ID_MAIN);
			break;
		}
		rot_enc_sw = 0;
	}
}

/*
 * Redraw function of this menu.
 */
void roc_menu_reflow_confirm_redraw(void)
{
	u8g2_FirstPage(&u8g2);
	do
	{
		u8g2_SetFont(&u8g2, u8g2_font_6x10_tf);
		u8g2_DrawStr(&u8g2, 1, 8, "Confirm Reflow");
		u8g2_DrawLine(&u8g2, 0, 10, 127, 10);

		// Profile
		char profile_name_buf[17];
		reflow_profiles_get_profile_name(selected_reflow_profile, profile_name_buf);
		u8g2_DrawStr(&u8g2, 1, 20, "Selected Profile:");
		u8g2_DrawStr(&u8g2, 5, 30, profile_name_buf);

		// Cancel button
		u8g2_DrawStr(&u8g2, 6, 62, "Cancel");
		// Cancel selector
		if (selected_item_index == 1)
		{
			display_util_draw_selector(&u8g2, 1, 61);
		}

		// Next button
		u8g2_DrawStr(&u8g2, 96, 62, "Start");
		// Next selector
		if (selected_item_index == 0)
		{
			display_util_draw_selector(&u8g2, 91, 61);
		}
	} while (u8g2_NextPage(&u8g2));
}

/*
 * Setter for the reflow profile.
 */
void roc_menu_reflow_confirm_set_profile(uint8_t* reflow_profile)
{
	selected_reflow_profile = reflow_profile;
}
