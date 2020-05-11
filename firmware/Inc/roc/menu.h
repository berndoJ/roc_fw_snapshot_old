/*
 * menu.h
 *
 *  Created on: 21.03.2019
 *      Author: Johannes Berndorfer (berndoJ)
 */

#ifndef INC_ROC_MENU_H_
#define INC_ROC_MENU_H_

#include "sys/_stdint.h"

#define ROC_MENU_UPDATE_DELAY 5 // Delay between updates of the menu in milliseconds.

#define ROC_MENU_ID_STARTUP 0x00 // Startup screen
#define ROC_MENU_ID_MAIN 0x01 // Main menu
#define ROC_MENU_ID_REFLOW_PROFILES 0x02 // Reflow profiles menu
#define ROC_MENU_ID_REFLOW_PROFILES_SELECT 0x03 // Reflow profiles menu - selection mode for reflow process.
#define ROC_MENU_ID_REFLOW_CONFRIM 0x04 // Reflow process confirmation menu
#define ROC_MENU_ID_REFLOW 0x05 // Reflow menu
#define ROC_MENU_ID_CREDITS 0x06 // Credits menu

int16_t rot_enc_turns;
uint8_t rot_enc_sw;

void roc_menu_run_task(void);
void roc_menu_open(uint8_t menu_id);

#endif /* INC_ROC_MENU_H_ */
