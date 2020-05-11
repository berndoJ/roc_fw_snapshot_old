/*
 * menu_credits.c
 *
 *  Created on: 21.03.2019
 *      Author: Johannes
 */

#include "roc/menus/menu_credits.h"
#include "roc/display.h"
#include "roc/menu.h"

/*
 * Update function of this menu.
 */
void roc_menu_credits_update(void)
{
	if (rot_enc_sw != 0)
	{
		roc_menu_open(ROC_MENU_ID_MAIN);
		rot_enc_sw = 0;
	}
}

/*
 * Redraw function of this menu.
 */
void roc_menu_credits_redraw(void)
{
	u8g2_FirstPage(&u8g2);
	do
	{
		u8g2_SetFont(&u8g2, u8g2_font_tenfatguys_tf);
		u8g2_DrawStr(&u8g2, 1, 11, "ROC");
		u8g2_SetFont(&u8g2, u8g2_font_6x10_tf);
		u8g2_DrawStr(&u8g2, 1, 21, "Reflow Oven");
		u8g2_DrawStr(&u8g2, 1, 31, "Controller by");
		u8g2_DrawStr(&u8g2, 1, 41, "Johannes Berndorfer");
		u8g2_DrawStr(&u8g2, 1, 51, "Copyright (c) 2019");

		u8g2_DrawStr(&u8g2, 102, 62, "Back");
		display_util_draw_selector(&u8g2, 97, 61);
	} while (u8g2_NextPage(&u8g2));
}
