/*
 * tc.c
 *
 *  Created on: 22.03.2019
 *      Author: Johannes Berndorfer (berndoJ)
 *
 *  HAL (Hardware Abstraction Layer) for the MAX31855 chip(s).
 *  Hard coded lower HAL-layer for the ROC-Board.
 *
 */

#include "roc/tc.h"
#include "stm32f0xx_hal.h"
#include "roc/debug.h"
#include "roc/display.h"

SPI_HandleTypeDef* hspi;

void tc_init(SPI_HandleTypeDef* spi_handle)
{
	hspi = spi_handle;
}

tc_info_t tc_read_temp(uint8_t id)
{
	uint8_t buf[4];
	tc_info_t tc_info;

	switch (id)
	{
	case TC_ID_0:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
		break;
	case TC_ID_1:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
		break;
	default:
		return tc_info;
	}

	HAL_GPIO_WritePin(display_cs_port, display_cs_pin, 0);

	HAL_SPI_Receive(hspi, buf, 4, 10);

	switch (id)
	{
	case TC_ID_0:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
		break;
	case TC_ID_1:
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
		break;
	}

	uint8_t sign = buf[0] >> 7;
	uint8_t temp_msb = (buf[0] & 0x7f) >> 4;
	uint8_t temp_lsb = ((buf[0] & 0xf) << 4) + ((buf[1] & 0xf0) >> 4);
	uint8_t temp_comma = (buf[1] & 0xc) >> 2;

	int16_t temp = (((uint16_t)temp_msb) << 8) + temp_lsb;

	if (sign == 0x01)
	{
		temp |= 0xf8;
	}

	tc_info.temp = (float) temp;
	tc_info.temp += (temp_comma * 0.25F);

	tc_info.fault = buf[1] & 0x1;

	tc_info.tc_not_connected = buf[3] & 0x1;

	return tc_info;
}
