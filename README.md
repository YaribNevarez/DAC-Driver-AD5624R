# Digital to analogue converter (AD5624R)

This class performs as a software interface of the digital to analogue converter (the class name is the same as the hardware device AD5624R). This driver implements the SPI communication with the hardware. The class is defined in AD5624R.h.
The SPI initialization is done by the following function.

```C
inline static void AD5624R_init_spi(void)
{
    while (!GET_POXI_SPI_TRANSMISSION_DONE);
    SET_POXI_SPI_SLAVE_SELECT(POXI_SPI_DAC_CS);
    SET_POXI_SPI_DATA_LENGTH(POXI_SPI_DATA_LENGTH_24_BITS);
    SET_POXI_SPI_BAUD_RATE_DIVIDER(AD5624R_SPI_BAUD_RATE);
    SET_POXI_SPI_CLOCK_POLARITY(1);
    SET_POXI_SPI_CLOCK_PHASE(0);
}
```

It can be seen in the function that the SPI protocol setup, CPOL = 1, CPHA = 0, 24 bits. For more details regarding this implementation, it can be inferred from the code.

The following code initialize the DAC device.
```C
static AD5624R * Poxi_DAC = AD5624R_instance();
Poxi_DAC->reset();
Poxi_DAC->LDAC_setup(0);
Poxi_DAC->power_mode(NORMAL_OPERATION, 0xF);
Poxi_DAC->internal_reference(REFERENCE_ON);
```

The following type enum indicates the power modes of the DAC, these are used as the first parameter of the power_mode function.

```C
typedef enum
{
    NORMAL_OPERATION       = 0,
    POWER_DOWN_1K_GND      = 1,
    POWER_DOWN_100K_GND    = 2,
    POWER_DOWN_THREE_STATE = 3,
} AD5624R_POWER_MODE;
```

The following code writes a value in channel A (it can be seen the options in the header file to write a value to another channel).

```C
Poxi_DAC->write_input_register(DAC_A, value);
Poxi_DAC->update_DAC_register(DAC_A);

The following code turns off the DAC device. The second parameter corresponds bitwise to the four DAC channels.

```C
Poxi_DAC->power_mode(POWER_DOWN_THREE_STATE, 0xF);
```

Best regards,

-Yarib Nevárez
