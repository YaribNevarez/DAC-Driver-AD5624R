/*
 * ad5624r.c
 *
 *  Created on: 6 de dic. de 2016
 *      Author: Yarib
 */

#include "ad5624r.h"

#include "poxi.h"


#define AD5624R_CMD_WRITE_INPUT_REGISTER            0x00
#define AD5624R_CMD_UPDATE_DAC_REGISTER             0x01
#define AD5624R_CMD_WRITE_INPUT_REGISTER_UDATE_ALL  0x02
#define AD5624R_CMD_WRITEAND_UPDATE_DAC_CHANEL      0x03
#define AD5624R_CMD_POWER_DOWN_DAC                  0x04
#define AD5624R_CMD_RESET                           0x05
#define AD5624R_CMD_LDAC_REGISTER_SETUP             0x06
#define AD5624R_CMD_INTERNAL_REFERENCE_SETUP        0x07

#define AD5624R_SPI_BAUD_RATE                       0x10


#define AD5624R_SPI_FRAME(command, address, data) (((0x0007 & ((int)command)) << 19) \
				      							 | ((0x0007 & ((int)address)) << 16) \
						    					 | ((0x0FFF & ((int)   data)) << 0))

static void AD5624R_write_input_register(AD5624R_DAC_ADDRESS address, uint16_t data);
static void AD5624R_update_DAC_register(AD5624R_DAC_ADDRESS address);
static void AD5624R_write_input_register_update_all(AD5624R_DAC_ADDRESS address, uint16_t data);
static void AD5624R_write_update_DAC_channel(AD5624R_DAC_ADDRESS address, uint16_t data);
static void AD5624R_power_mode(AD5624R_POWER_MODE mode, uint8_t channels);
static void AD5624R_reset(void);
static void AD5624R_LDAC_setup(uint8_t channels);
static void AD5624R_internal_reference(AD5624R_INTERNAL_REFERENCE reference);

static AD5624R AD5624R_obj = { AD5624R_write_input_register,
                               AD5624R_update_DAC_register,
                               AD5624R_write_input_register_update_all,
                               AD5624R_write_update_DAC_channel,
                               AD5624R_power_mode,
                               AD5624R_reset,
                               AD5624R_LDAC_setup,
                               AD5624R_internal_reference };

AD5624R * AD5624R_instance(void)
{
	return & AD5624R_obj;
}

inline static void AD5624R_init_spi(void)
{
	while (!GET_POXI_SPI_TRANSMISSION_DONE);
	SET_POXI_SPI_SLAVE_SELECT(POXI_SPI_DAC_CS);
	SET_POXI_SPI_DATA_LENGTH(POXI_SPI_DATA_LENGTH_24_BITS);
	SET_POXI_SPI_BAUD_RATE_DIVIDER(AD5624R_SPI_BAUD_RATE);
	SET_POXI_SPI_CLOCK_POLARITY(1);
	SET_POXI_SPI_CLOCK_PHASE(0);
}

static void AD5624R_write_input_register(AD5624R_DAC_ADDRESS address, uint16_t data)
{
	AD5624R_init_spi();
	POXI_SPI_DATA = AD5624R_SPI_FRAME(AD5624R_CMD_WRITE_INPUT_REGISTER,
									  address,
									  data);
}

static void AD5624R_update_DAC_register(AD5624R_DAC_ADDRESS address)
{
	AD5624R_init_spi();
	POXI_SPI_DATA = AD5624R_SPI_FRAME(AD5624R_CMD_UPDATE_DAC_REGISTER,
									  address,
									  0);
}

static void AD5624R_write_input_register_update_all(AD5624R_DAC_ADDRESS address, uint16_t data)
{
	AD5624R_init_spi();
	POXI_SPI_DATA = AD5624R_SPI_FRAME(AD5624R_CMD_WRITE_INPUT_REGISTER_UDATE_ALL,
									  address,
									  data);
}

static void AD5624R_write_update_DAC_channel(AD5624R_DAC_ADDRESS address, uint16_t data)
{
	AD5624R_init_spi();
	POXI_SPI_DATA = AD5624R_SPI_FRAME(AD5624R_CMD_WRITEAND_UPDATE_DAC_CHANEL,
									  address,
									  data);
}

static void AD5624R_power_mode(AD5624R_POWER_MODE mode, uint8_t channels)
{
	AD5624R_init_spi();
	POXI_SPI_DATA = AD5624R_SPI_FRAME(AD5624R_CMD_POWER_DOWN_DAC,
									  0,
									  (mode<<4) | (0x0F & channels));
}

static void AD5624R_reset(void)
{
	AD5624R_init_spi();
	POXI_SPI_DATA = AD5624R_SPI_FRAME(AD5624R_CMD_RESET,0,1);
}

static void AD5624R_LDAC_setup(uint8_t channels)
{
	AD5624R_init_spi();
	POXI_SPI_DATA = AD5624R_SPI_FRAME(AD5624R_CMD_LDAC_REGISTER_SETUP,
									  0,
									  0x0F & channels);
}

static void AD5624R_internal_reference(AD5624R_INTERNAL_REFERENCE reference)
{
	AD5624R_init_spi();
	POXI_SPI_DATA = AD5624R_SPI_FRAME(AD5624R_CMD_INTERNAL_REFERENCE_SETUP,
									  0, reference);
}
