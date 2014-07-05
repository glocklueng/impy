/**
 * @file    eeprom.c
 * @author  Peter Feichtinger
 * @date    16.04.2014
 * @brief   This file contains functions to manage the EEPROM chip.
 */

// Includes -------------------------------------------------------------------
#include <assert.h>
#include "eeprom.h"

// Check structure sizes, in case the compiler aligns something we don't want it to
_Static_assert(sizeof(EEPROM_ConfigurationBuffer) == EEPROM_CONFIG_SIZE, "Bad EEPROM_ConfigurationBuffer definition");
_Static_assert(sizeof(EEPROM_SettingsBuffer) == EEPROM_SETTINGS_SIZE, "Bad EEPROM_SettingsBuffer definition");

// Private function prototypes ------------------------------------------------


// Private variables ----------------------------------------------------------
static volatile EEPROM_Status status = EE_UNINIT;
static I2C_HandleTypeDef *i2cHandle = NULL;
static uint8_t e2_state;


// Private functions ----------------------------------------------------------



// Exported functions ---------------------------------------------------------

/**
 * Gets the current driver status.
 */
EEPROM_Status GetStatus(void)
{
    return status;
}

/**
 * Initializes the driver with the specified I2C handle for communication and E2 bit state.
 * 
 * @param i2c Pointer to an I2C handle structure that is to be used for communication with the EEPROM
 * @param e2_set Indicates the state of the E2 pin of the device
 * @return {@link AD5933_Error} code
 */
EEPROM_Error EE_Init(I2C_HandleTypeDef *i2c, uint8_t e2_set)
{
    assert_param(i2c != NULL);
    
    i2cHandle = i2c;
    e2_state = (e2_set ? EEPROM_M24C08_ADDR_E2 : 0);
    return EE_OK;
}

/**
 * Resets the driver to initialization state.
 * 
 * @return {@code EE_ERROR} if the driver has not been initialized, {@code EE_OK} otherwise
 */
EEPROM_Error EE_Reset(void)
{
    if(status == EE_UNINIT)
    {
        return EE_ERROR;
    }
    
    status = EE_IDLE;
    return EE_OK;
}

// ----------------------------------------------------------------------------
