/*
 * ad5624r.h
 *
 *  Created on: 6 de dic. de 2016
 *      Author: Yarib Nevárez
 */

#ifndef SRC_POXI_HARDWARE_AD5624R_H_
#define SRC_POXI_HARDWARE_AD5624R_H_
#include "xil_types.h"


typedef enum
{
	DAC_A = 0,
	DAC_B = 1,
	DAC_C = 2,
	DAC_D = 3,
	DAC_ALL = 7,
} AD5624R_DAC_ADDRESS;

typedef enum
{
	NORMAL_OPERATION       = 0,
	POWER_DOWN_1K_GND      = 1,
	POWER_DOWN_100K_GND    = 2,
	POWER_DOWN_THREE_STATE = 3,
} AD5624R_POWER_MODE;

typedef enum
{
	REFERENCE_OFF = 0,
	REFERENCE_ON  = 1
} AD5624R_INTERNAL_REFERENCE;

typedef struct
{
    void (*write_input_register)           (AD5624R_DAC_ADDRESS address, uint16_t data);
    void (*update_DAC_register)            (AD5624R_DAC_ADDRESS address);
    void (*write_input_register_update_all)(AD5624R_DAC_ADDRESS address, uint16_t data);
    void (*write_update_DAC_channel)       (AD5624R_DAC_ADDRESS address, uint16_t data);
    void (*power_mode)        (AD5624R_POWER_MODE mode, uint8_t channels);
    void (*reset)             (void);
    void (*LDAC_setup)        (uint8_t channels);
    void (*internal_reference)(AD5624R_INTERNAL_REFERENCE reference);
} AD5624R;

// Singleton instance
AD5624R * AD5624R_instance(void);

#endif /* SRC_POXI_HARDWARE_AD5624R_H_ */

