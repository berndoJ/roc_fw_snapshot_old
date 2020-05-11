/*
 * tc.h
 *
 *  Created on: 22.03.2019
 *      Author: Johannes
 */

#ifndef INC_ROC_TC_H_
#define INC_ROC_TC_H_

#define TC_ID_0 0x00
#define TC_ID_1 0x01

#include "stm32f0xx_hal.h"

typedef struct tc_info
{
	float temp;
	uint8_t fault;
	uint8_t tc_not_connected;
} tc_info_t;

void tc_init(SPI_HandleTypeDef* spi_handle);
tc_info_t tc_read_temp(uint8_t id);

#endif /* INC_ROC_TC_H_ */
