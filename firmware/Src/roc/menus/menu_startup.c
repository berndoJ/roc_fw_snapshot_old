/*
 * menu_startup.c
 *
 *  Created on: 21.03.2019
 *      Author: Johannes
 */

#include "roc/menus/menu_startup.h"
#include "roc/display.h"
#include "roc/menu.h"
#include "cmsis_os.h"

/*
 * Update function of this menu.
 */
void roc_menu_startup_update(void)
{
	osDelay(ROC_MENU_STARTUP_DELAY);
	roc_menu_open(ROC_MENU_ID_MAIN);
}

/*
 * Redraw function of this menu.
 */
void roc_menu_startup_redraw(void)
{
	u8g2_FirstPage(&u8g2);
	do
	{
		u8g2_SetFont(&u8g2, u8g2_font_tenfatguys_tf);
		u8g2_DrawStr(&u8g2, 47, 21, "ROC");
		u8g2_SetFont(&u8g2, u8g2_font_6x10_tf);
		u8g2_DrawStr(&u8g2, 1, 62, "Johannes Berndorfer");
		u8g2_DrawStr(&u8g2, 1, 54, "2019");
	} while (u8g2_NextPage(&u8g2));
}
