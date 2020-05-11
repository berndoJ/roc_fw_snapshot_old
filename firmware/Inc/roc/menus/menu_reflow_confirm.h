/*
 * menu_reflow_confirm.h
 *
 *  Created on: 22.03.2019
 *      Author: Johannes
 */

#ifndef INC_ROC_MENUS_MENU_REFLOW_CONFIRM_H_
#define INC_ROC_MENUS_MENU_REFLOW_CONFIRM_H_

#include "sys/_stdint.h"

void roc_menu_reflow_confirm_update(void);
void roc_menu_reflow_confirm_redraw(void);
void roc_menu_reflow_confirm_set_profile(uint8_t* reflow_profile);

#endif /* INC_ROC_MENUS_MENU_REFLOW_CONFIRM_H_ */
