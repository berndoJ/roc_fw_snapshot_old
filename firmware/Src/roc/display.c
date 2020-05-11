/*
 * display.c
 *
 *  Created on: 16.03.2019
 *      Author: Johannes Berndorfer (berndoJ)
 */

#include "roc/display.h"
#include "roc/u8g_arm.h"
#include "stm32f0xx_hal.h"
#include "cmsis_os.h"
#include "roc/debug.h"

SPI_HandleTypeDef* display_spi_handle;

GPIO_TypeDef* display_cs_port;
uint16_t display_cs_pin;

GPIO_TypeDef* display_dc_port;
uint16_t display_dc_pin;

GPIO_TypeDef* display_rst_port;
uint16_t display_rst_pin;

GPIO_TypeDef* display_spi_sck_port;
uint16_t display_spi_sck_pin;

GPIO_TypeDef* display_spi_mosi_port;
uint16_t display_spi_mosi_pin;

u8g2_t u8g2;

// This function is run directly after HAL init, so no os-calls are valid.
void display_init(SPI_HandleTypeDef* hspi, GPIO_TypeDef* cs_port,
		uint16_t cs_pin, GPIO_TypeDef* rst_port, uint16_t rst_pin,
		GPIO_TypeDef* dc_port, uint16_t dc_pin, GPIO_TypeDef* spi_sck_port,
		uint16_t spi_sck_pin, GPIO_TypeDef* spi_mosi_port,
		uint16_t spi_mosi_pin)
{
	display_spi_handle = hspi;
	display_cs_port = cs_port;
	display_cs_pin = cs_pin;
	display_dc_port = dc_port;
	display_dc_pin = dc_pin;
	display_spi_sck_port = spi_sck_port;
	display_spi_sck_pin = spi_sck_pin;
	display_spi_mosi_port = spi_mosi_port;
	display_spi_mosi_pin = spi_mosi_pin;
	display_rst_port = rst_port;
	display_rst_pin = rst_pin;

	u8g2_Setup_st7920_s_128x64_2(&u8g2, U8G2_R0, u8g_hw_port_byte_cb,
			u8g_hw_port_gpio_delay_cb);
	u8g2_InitDisplay(&u8g2);
	u8g2_SetPowerSave(&u8g2, 0);
}

/*
 * Draws a triangle menu item selector (4x7 pixels) to the given x and y coordinates. The x and y coordinates reference the bottom left of the selector.
 */
void display_util_draw_selector(u8g2_t* u8g2, uint8_t x, uint8_t y)
{
	u8g2_DrawLine(u8g2, x, y, x, y - 6);
	u8g2_DrawLine(u8g2, x + 1, y - 1, x + 1, y - 5);
	u8g2_DrawLine(u8g2, x + 2, y - 2, x + 2, y - 4);
	u8g2_DrawPixel(u8g2, x + 3, y - 3);
}
