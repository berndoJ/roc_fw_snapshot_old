/*
 * menu_reflow_profiles.h
 *
 *  Created on: 21.03.2019
 *      Author: Johannes
 */

#ifndef INC_ROC_MENUS_MENU_REFLOW_PROFILES_H_
#define INC_ROC_MENUS_MENU_REFLOW_PROFILES_H_

#include "sys/_stdint.h"

#define ROC_MENU_REFLOW_PROFILES_MODE_SHOW 0x00 // Show mode: Only show all profiles.
#define ROC_MENU_REFLOW_PROFILES_MODE_SELECT 0x01 // Select mode: Select a profile for reflow.

void roc_menu_reflow_profiles_update(void);
void roc_menu_reflow_profiles_redraw(void);

void roc_menu_reflow_profiles_set_mode(uint8_t mode);

#endif /* INC_ROC_MENUS_MENU_REFLOW_PROFILES_H_ */
