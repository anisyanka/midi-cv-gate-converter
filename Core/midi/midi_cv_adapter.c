#include "midi_cv_adapter.h"
#include "mcp48x2.h"
#include "main.h"

#include <stddef.h>

extern SPI_HandleTypeDef hspi1;

static void dac1_nss_set(void)
{
	HAL_GPIO_WritePin(SPI1_NSS1_GPIO_Port, SPI1_NSS1_Pin, GPIO_PIN_SET);
}

static void dac2_nss_set(void)
{
	HAL_GPIO_WritePin(SPI1_NSS2_GPIO_Port, SPI1_NSS2_Pin, GPIO_PIN_SET);
}

static void dac1_nss_reset(void)
{
	HAL_GPIO_WritePin(SPI1_NSS1_GPIO_Port, SPI1_NSS1_Pin, GPIO_PIN_RESET);
}

static void dac2_nss_reset(void)
{
	HAL_GPIO_WritePin(SPI1_NSS2_GPIO_Port, SPI1_NSS2_Pin, GPIO_PIN_RESET);
}

static void ldac_set(void)
{
	HAL_GPIO_WritePin(SPI1_LDAC_GPIO_Port, SPI1_LDAC_Pin, GPIO_PIN_SET);
}

static void ldac_reset(void)
{
	HAL_GPIO_WritePin(SPI1_LDAC_GPIO_Port, SPI1_LDAC_Pin, GPIO_PIN_RESET);
}

static void delay_us(uint32_t us)
{
	(void)us;

	HAL_Delay(2);
}

static mcp48x2_ret_t spi_write_packet(uint16_t data)
{
	HAL_StatusTypeDef ret = HAL_OK;
	uint8_t temp[2] = { 0 };

	temp[0] = (uint8_t)(data >> 8);
	temp[1] = (uint8_t)(data);

	ret = HAL_SPI_Transmit(&hspi1, temp, 2, 100);
	if (ret != HAL_OK)
	{
		return MCP48X2_FAIL;
	}

	return MCP48X2_OK;
}

/* DAC for CV1 and CV2 */
static mcp48x2_device_t dac1_dev = { 0 };

/* DAC for CV3 and CV4 */
static mcp48x2_device_t dac2_dev = { 0 };

/* LL funcs for CV1 and CV2 signals */
static mcp48x2_ll_t dac1_ll = 
{
	.nss_set = dac1_nss_set,
	.nss_reset = dac1_nss_reset,
	.ldac_set = ldac_set,
	.ldac_reset = ldac_reset,
	.delay_us = delay_us,
	.spi_write_packet = spi_write_packet,
};

/* LL funcs for CV3 and CV4 signals */
static mcp48x2_ll_t dac2_ll = 
{
	.nss_set = dac2_nss_set,
	.nss_reset = dac2_nss_reset,
	.ldac_set = ldac_set,
	.ldac_reset = ldac_reset,
	.delay_us = delay_us,
	.spi_write_packet = spi_write_packet,
};

void midi_cv_init(void)
{
	/* Pass low level functions to the DAC library */
	mcp48x2_default_init(&dac1_dev, &dac1_ll);
	mcp48x2_default_init(&dac2_dev, &dac2_ll);

	mcp48x2_set_channel_gain(&dac1_dev, MCP48X2_DAC_CH_A, MCP48X2_GAIN_1X);
	mcp48x2_set_channel_gain(&dac1_dev, MCP48X2_DAC_CH_B, MCP48X2_GAIN_1X);

	mcp48x2_set_channel_gain(&dac2_dev, MCP48X2_DAC_CH_A, MCP48X2_GAIN_1X);
	mcp48x2_set_channel_gain(&dac2_dev, MCP48X2_DAC_CH_B, MCP48X2_GAIN_1X);
}

void midi_cv1_set(uint16_t value)
{
	mcp48x2_set_channel_value(&dac1_dev, MCP48X2_DAC_CH_A, value);
}

void midi_cv2_set(uint16_t value)
{
	mcp48x2_set_channel_value(&dac1_dev, MCP48X2_DAC_CH_B, value);
}

void midi_cv3_set(uint16_t value)
{
	mcp48x2_set_channel_value(&dac2_dev, MCP48X2_DAC_CH_A, value);
}

void midi_cv4_set(uint16_t value)
{
	mcp48x2_set_channel_value(&dac2_dev, MCP48X2_DAC_CH_B, value);
}
