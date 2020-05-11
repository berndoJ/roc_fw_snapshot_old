/*
 * tempctrl.h
 *
 *  Created on: 23.03.2019
 *      Author: Johannes
 */

#ifndef INC_ROC_TEMPCTRL_H_
#define INC_ROC_TEMPCTRL_H_

#include "roc/tc.h"
#include "sys/_stdint.h"

void tempctrl_update(tc_info_t t1, tc_info_t t2, uint16_t set_temp);
void tempctrl_tick(void);
void tempctrl_ssr_tick(void);
void tempctrl_enable(void);
void tempctrl_disable(void);

#endif /* INC_ROC_TEMPCTRL_H_ */
