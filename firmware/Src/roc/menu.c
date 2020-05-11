/*
 * menu.c
 *
 *  Created on: 21.03.2019
 *      Author: Johannes Berndorfer (berndoJ)
 *
 *  Main display and menu management code.
 *
 */

#include "roc/menu.h"
#include "roc/debug.h"
#include "roc/rot_encoder.h"

#include "roc/menus/menu_startup.h"
#include "roc/menus/menu_main.h"
#include "roc/menus/menu_reflow_profiles.h"
#include "roc/menus/menu_credits.h"
#include "roc/menus/menu_reflow_confirm.h"
#include "roc/menus/menu_reflow.h"

// The current unhandled rotary encoder turns.
int16_t rot_enc_turns = 0;

// The current status of the rotary encoder switch.
uint8_t rot_enc_sw = 0;

// The current menu id.
static uint8_t current_menu_id = ROC_MENU_ID_STARTUP;

/*
 * Gets called from the menu thread.
 */
void roc_menu_run_task(void)
{
	roc_menu_open(ROC_MENU_ID_STARTUP);
	while (1)
	{
		switch (current_menu_id)
		{
		case ROC_MENU_ID_STARTUP:
			roc_menu_startup_update();
			rot_enc_turns = 0;
			rot_enc_sw = 0;
			break;
		case ROC_MENU_ID_MAIN:
			roc_menu_main_update();
			break;
		case ROC_MENU_ID_REFLOW_PROFILES:
			roc_menu_reflow_profiles_update();
			break;
		case ROC_MENU_ID_REFLOW_PROFILES_SELECT:
			roc_menu_reflow_profiles_update();
			break;
		case ROC_MENU_ID_REFLOW_CONFRIM:
			roc_menu_reflow_confirm_update();
			break;
		case ROC_MENU_ID_REFLOW:
			roc_menu_reflow_update();
			rot_enc_turns = 0;
			break;
		case ROC_MENU_ID_CREDITS:
			roc_menu_credits_update();
			rot_enc_turns = 0;
			break;
		}
		osDelay(ROC_MENU_UPDATE_DELAY);
	}
}

/*
 * Opens the menu with the given menu id.
 */
void roc_menu_open(uint8_t menu_id)
{
	switch (menu_id)
	{
	case ROC_MENU_ID_STARTUP:
		roc_menu_startup_redraw();
		break;
	case ROC_MENU_ID_MAIN:
		roc_menu_main_redraw();
		break;
	case ROC_MENU_ID_REFLOW_PROFILES:
		roc_menu_reflow_profiles_set_mode(ROC_MENU_REFLOW_PROFILES_MODE_SHOW);
		roc_menu_reflow_profiles_redraw();
		break;
	case ROC_MENU_ID_REFLOW_PROFILES_SELECT:
		roc_menu_reflow_profiles_set_mode(ROC_MENU_REFLOW_PROFILES_MODE_SELECT);
		roc_menu_reflow_profiles_redraw();
		break;
	case ROC_MENU_ID_REFLOW_CONFRIM:
		roc_menu_reflow_confirm_redraw();
		break;
	case ROC_MENU_ID_REFLOW:
		roc_menu_reflow_redraw();
		break;
	case ROC_MENU_ID_CREDITS:
		roc_menu_credits_redraw();
		break;
	default:
		debug_cons_println(
				"[Menu] Error: Unknown menu ID was given to roc_menu_open function.");
		return;
	}
	current_menu_id = menu_id;
}
