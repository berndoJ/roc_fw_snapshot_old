/*
 * menu_reflow.h
 *
 *  Created on: 22.03.2019
 *      Author: Johannes
 */

#ifndef INC_ROC_MENUS_MENU_REFLOW_H_
#define INC_ROC_MENUS_MENU_REFLOW_H_

#include "sys/_stdint.h"

void roc_menu_reflow_update(void);
void roc_menu_reflow_redraw(void);
void roc_menu_reflow_set_profile(uint8_t* reflow_profile);
void roc_menu_reflow_start(void);
void roc_menu_reflow_update_heater_status(uint8_t status);

#endif /* INC_ROC_MENUS_MENU_REFLOW_H_ */
