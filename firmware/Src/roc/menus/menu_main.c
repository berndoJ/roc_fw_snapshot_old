/*
 * menu_main.c
 *
 *  Created on: 21.03.2019
 *      Author: Johannes
 */

#include "roc/menus/menu_main.h"
#include "roc/display.h"
#include "roc/menu.h"
#include "roc/debug.h"

#include "stdlib.h"

#define MENU_BEGIN_Y 13

static uint8_t selected_item_index = 0;

static const uint8_t menu_item_count = 3;
static const char* menu_items[] = { "Reflow", "Reflow Profiles", "Credits" };

/*
 * Update function of this menu.
 */
void roc_menu_main_update(void)
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
		roc_menu_main_redraw();
	}
	if (rot_enc_sw != 0)
	{
		switch (selected_item_index)
		{
		case 0:
			roc_menu_open(ROC_MENU_ID_REFLOW_PROFILES_SELECT);
			break;
		case 1:
			roc_menu_open(ROC_MENU_ID_REFLOW_PROFILES);
			break;
		case 2:
			roc_menu_open(ROC_MENU_ID_CREDITS);
			break;
		}
		rot_enc_sw = 0;
	}
}

/*
 * Redraw function of this menu.
 */
void roc_menu_main_redraw(void)
{
	u8g2_FirstPage(&u8g2);
	do
	{
		u8g2_SetFont(&u8g2, u8g2_font_6x10_tf);
		u8g2_DrawStr(&u8g2, 1, 8, "ROC Main Menu");
		u8g2_DrawLine(&u8g2, 0, 10, 127, 10);
		for (uint8_t draw_index = 0; draw_index < menu_item_count; draw_index++)
		{
			u8g2_DrawStr(&u8g2, 6, MENU_BEGIN_Y + 7 + (8 * draw_index), menu_items[draw_index]);
			if (draw_index == selected_item_index)
			{
				display_util_draw_selector(&u8g2, 1, MENU_BEGIN_Y + 6 + (8 * draw_index));
			}
		}
	} while (u8g2_NextPage(&u8g2));
}
