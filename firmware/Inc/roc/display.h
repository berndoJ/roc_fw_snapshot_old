/*
 * display.h
 *
 *  Created on: 16.03.2019
 *      Author: Johannes Berndorfer (berndoJ)
 */

#ifndef INC_ROC_DISPLAY_H_
#define INC_ROC_DISPLAY_H_

#include "stm32f0xx_hal.h"
#include "roc/u8g_arm.h"

#define DISPLAY_MIN_UPDATE_DELAY_MS 250

u8g2_t u8g2;

GPIO_TypeDef* display_cs_port;
uint16_t display_cs_pin;

void display_init(SPI_HandleTypeDef* hspi, GPIO_TypeDef* cs_port,
		uint16_t cs_pin, GPIO_TypeDef* rst_port, uint16_t rst_pin,
		GPIO_TypeDef* dc_port, uint16_t dc_pin,
		GPIO_TypeDef* spi_sck_port, uint16_t spi_sck_pin,
		GPIO_TypeDef* spi_mosi_port, uint16_t spi_mosi_pin);

void display_util_draw_selector(u8g2_t* u8g2, uint8_t x, uint8_t y);

#endif /* INC_ROC_DISPLAY_H_ */
