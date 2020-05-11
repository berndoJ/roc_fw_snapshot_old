/*
 * ssr.h
 *
 *  Created on: 16.03.2019
 *      Author: Johannes
 */

#ifndef INC_ROC_SSR_H_
#define INC_ROC_SSR_H_

#include "sys/_stdint.h"

#define SSR_GPIO_PORT GPIOA
#define SSR_GPIO_PIN GPIO_PIN_4

void ssr_toggle(void);
void ssr_enable(void);
void ssr_disable(void);
uint8_t ssr_get_state(void);

#endif /* INC_ROC_SSR_H_ */
