/**
 * @file    ad5933.h
 * @author  Peter Feichtinger
 * @date    14.04.2014
 * @brief   This file contains register definitions and control function prototypes for the AD5933 driver.
 */

#ifndef AD5933_H_
#define AD5933_H_

// Includes -------------------------------------------------------------------
#include <stdint.h>
#include "stm32f4xx_hal.h"

// Exported type definitions --------------------------------------------------
typedef enum
{
    AD_UNINIT = 0,          //!< Driver has not been initialized
    AD_IDLE,                //!< Driver has been initialized and is ready to start a measurement
    AD_FINISH,              //!< Driver has finished with a measurement
    AD_CALIBRATE,           //!< Driver is doing a calibration measurement
    AD_MEASURE_TEMP,        //!< Driver is doing a temperature measurement
    AD_MEASURE_IMPEDANCE    //!< Driver is doing an impedance measurement
} AD5933_Status;

typedef enum
{
    AD_OK = 0,      //!< Indicates success
    AD_BUSY,        //!< Indicates that the driver is currently busy doing a measurement
    AD_ERROR        //!< Indicates an error condition
} AD5933_Error;

typedef struct
{
    uint32_t Start_Freq;        //!< Start frequency for the sweep in Hz
    uint32_t Freq_Increment;    //!< Frequency increment for the sweep in Hz
    uint16_t Num_Increments;    //!< Number of frequency points for the sweep
    uint16_t Settling_Cycles;   //!< Number of settling cycles before a measurement
} AD5933_Sweep;

typedef struct
{
    uint32_t Frequency;     //!< Frequency of the data point
    int16_t  Real;          //!< Scaled real part of the impedance
    int16_t  Imag;          //!< Scaled imaginary part of the impedance
} AD5933_ImpedanceData;

typedef struct
{
    uint32_t impedance;     //!< Impedance used for the gain factor calibration
    uint32_t freq1;         //!< Frequency of the first calibration point
    int16_t  real1;         //!< Real part for the first calibration point
    int16_t  imag1;         //!< Imaginary part for the first calibration point
    uint32_t freq2;         //!< Frequency of the second calibration point
    int16_t  real2;         //!< Real part for the second calibration point
    int16_t  imag2;         //!< Imaginary part for the second calibration point
    uint8_t  is_2point;     //!< Whether this is single or two point calibration data
} AD5933_GainFactorData;

typedef struct
{
    float   freq1;          //!< Frequency of the first calibration point
    float   offset;         //!< Calculated gain factor at first frequency
    float   slope;          //!< Calculated gain factor slope for a two point calibration
    uint8_t is_2point;      //!< Whether this is single or two point gain factor data
} AD5933_GainFactor;

// Macros ---------------------------------------------------------------------

#define LOBYTE(x)  ((uint8_t)(x & 0x00FF))
#define HIBYTE(x)  ((uint8_t)((x & 0xFF00) >> 8))

// Constants ------------------------------------------------------------------

/**
 * I2C Address of the AD5933, cannot be changed
 */
#define AD5933_ADDR                         0x0D

/**
 * Timeout in ms for I2C communication
 */
#define AD5933_I2C_TIMEOUT                  0x200

/**
 * Internal clock frequency of the AD5933 (16.776MHz)
 */
#define AD5933_CLK_FREQ                     0xFFFB40

/*****************************************************************************
 *                              REGISTER MAPPING                             *
 *****************************************************************************/

/**
 * Control Register High Byte (16-bit)
 * Read/Write
 * Default value: 0xA0 (Power down)
 * 
 *  + D15:D12   Control function, see {@link AD5933_FUNCTION}
 *  + D11       Not used
 *  + D10:D9    Output voltage range setting, see {@link AD5933_VOLTAGE}
 *  + D8        PGA gain setting, see {@link AD5933_GAIN}
 */
#define AD5933_CTRL_H_ADDR                  0x80

/**
 * Control Register Low Byte (16-bit)
 * Read/Write
 * Default value: 0x00
 * 
 *  + D7:D5     Reserved, set to 0
 *  + D4        Reset
 *  + D3        Clock source setting, see {@link AD5933_CLOCK}
 *  + D2:D0     Reserved, set to 0
 */
#define AD5933_CTRL_L_ADDR                  0x81

/**
 * Start Frequency Register High Byte (24-bit unsigned)
 * Read/Write
 * Default value: none
 */
#define AD5933_START_FREQ_H_ADDR            0x82

/**
 * Start Frequency Register Mid Byte (24-bit unsigned)
 * Read/Write
 * Default value: none
 */
#define AD5933_START_FREQ_M_ADDR            0x83

/**
 * Start Frequency Register Low Byte (24-bit unsigned)
 * Read/Write
 * Default value: none
 */
#define AD5933_START_FREQ_L_ADDR            0x84

/**
 * Frequency Increment Register High Byte (24-bit unsigned)
 * Read/Write
 * Default value: none
 */
#define AD5933_FREQ_INCR_H_ADDR             0x85

/**
 * Frequency Increment Register Mid Byte (24-bit unsigned)
 * Read/Write
 * Default value: none
 */
#define AD5933_FREQ_INCR_M_ADDR             0x86

/**
 * Frequency Increment Register Low Byte (24-bit unsigned)
 * Read/Write
 * Default value: none
 */
#define AD5933_FREQ_INCR_L_ADDR             0x87

/**
 * Number of Increments Register High Byte (9-bit unsigned)
 * Read/Write
 * Default value: none
 * 
 *  + D16:D9    Don't care
 *  + D8        MSB of value
 */
#define AD5933_NUM_INCR_H_ADDR              0x88

/**
 * Number of Increments Register Low Byte (9-bit unsigned)
 * Read/Write
 * Default value: none
 * 
 *  + D7:D0     LSB of value
 */
#define AD5933_NUM_INCR_L_ADDR              0x89

/**
 * Number of Settling Time Cycles Register High Byte (2+9-bit unsigned)
 * Read/Write
 * Default value: none
 * 
 *  + D15:D11   Don't care
 *  + D10:D9    Settling time multiplier, see {@link AD5933_SETTL_MULT}
 *  + D8        MSB of settling time cycles
 */
#define AD5933_SETTL_H_ADDR                 0x8A

/**
 * Number of Settling Time Cycles Register Low Byte (2+9-bit unsigned)
 * Read/Write
 * Default value: none
 * 
 *  + D7:D0     LSB of settling time cycles
 */
#define AD5933_SETTL_L_ADDR                 0x8B

/**
 * Status Register
 * Read only
 * Default value: 0x00
 * 
 *  + D7:D3     Reserved
 *  + D2        Frequency sweep complete
 *  + D1        Valid real/imaginary data
 *  + D0        Valid temperature measurement
 * 
 * See also {@link AD5933_STATUS}
 */
#define AD5933_STATUS_ADDR                  0x8F

/**
 * Temperature Data Register High Byte (14-bit signed)
 * Read only
 * Default value: none
 * 
 *  + D15:D14   Don't care
 *  + D13       Sign bit
 *  + D12:D8    MSB of temperature value
 */
#define AD5933_TEMP_H_ADDR                  0x92

/**
 * Temperature Data Register Low Byte (14-bit signed)
 * Read only
 * Default value: none
 * 
 *  + D7:D0     LSB of temperature value
 */
#define AD5933_TEMP_L_ADDR                  0x93

/**
 * Real Data Register High Byte (16-bit signed)
 * Read only
 * Default value: none
 */
#define AD5933_REAL_H_ADDR                  0x94

/**
 * Real Data Register Low Byte (16-bit signed)
 * Read only
 * Default value: none
 */
#define AD5933_REAL_L_ADDR                  0x95

/**
 * Imaginary Data Register High Byte (16-bit signed)
 * Read only
 * Default value: none
 */
#define AD5933_IMAG_H_ADDR                  0x96

/**
 * Imaginary Data Register Low Byte (16-bit signed)
 * Read only
 * Default value: none
 */
#define AD5933_IMAG_L_ADDR                  0x97

/*****************************************************************************
 *                              REGISTER VALUES                              *
 *****************************************************************************/

/**
 * @defgroup AD5933_FUNCTION Control Register Function Values
 * 
 * Control functions (Control register D15:D12)
 * @{
 */
// 
#define AD5933_FUNCTION_INIT_FREQ           ((uint16_t)0x01 << 12)  //!< Initialize with start frequency
#define AD5933_FUNCTION_START_SWEEP         ((uint16_t)0x02 << 12)  //!< Start frequency sweep
#define AD5933_FUNCTION_INCREMENT_FREQ      ((uint16_t)0x03 << 12)  //!< Increment frequency
#define AD5933_FUNCTION_REPEAT_FREQ         ((uint16_t)0x04 << 12)  //!< Repeat frequency
#define AD5933_FUNCTION_MEASURE_TEMP        ((uint16_t)0x09 << 12)  //!< Measure temperature
#define AD5933_FUNCTION_POWER_DOWN          ((uint16_t)0x0A << 12)  //!< Power-down mode
#define AD5933_FUNCTION_STANDBY             ((uint16_t)0x0B << 12)  //!< Standby mode
/** @} */

/**
 * @defgroup AD5933_VOLTAGE Control Register Voltage Range Values
 * 
 * Output voltage range (Control register D10:D9)
 * @{
 */
#define AD5933_VOLTAGE_2                    ((uint16_t)0x00 << 9)   //!< Range 1: 2V p-p
#define AD5933_VOLTAGE_1                    ((uint16_t)0x03 << 9)   //!< Range 2: 1V p-p
#define AD5933_VOLTAGE_0_4                  ((uint16_t)0x02 << 9)   //!< Range 3: 400mV p-p
#define AD5933_VOLTAGE_0_2                  ((uint16_t)0x01 << 9)   //!< Range 4: 200mV p-p
/** @} */

/**
 * @defgroup AD5933_GAIN Control Register PGA Gain Settings
 * 
 * PGA gain setting (Control register D8)
 * @{
 */
#define AD5933_GAIN_1                       ((uint16_t)0x01 << 8)   //!< PGA gain x1
#define AD5933_GAIN_5                       ((uint16_t)0x00 << 8)   //!< PGA gain x5
/** @} */

/**
 * @defgroup AD5933_CLOCK Control Register Clock Source Settings
 * 
 * Clock source (Control register D3)
 * @{
 */
#define AD5933_CLOCK_INTERNAL               ((uint16_t)0x00 << 3)   //!< Internal system clock (~16.667MHz)
#define AD5933_CLOCK_EXTERNAL               ((uint16_t)0x01 << 3)   //!< External system clock
/** @} */

/**
 * @defgroup AD5933_SETTL_MULT Settling Time Register Multiplier Values
 * 
 * Settling time multiplier (Settling time register D10:D9)
 * @{
 */
#define AD5933_SETTL_MULT_1                 ((uint16_t)0x00 << 9)   //!< Settling time multiplier of 1
#define AD5933_SETTL_MULT_2                 ((uint16_t)0x01 << 9)   //!< Settling time multiplier of 2
#define AD5933_SETTL_MULT_4                 ((uint16_t)0x03 << 9)   //!< Settling time multiplier of 4
/** @} */

/**
 * @defgroup AD5933_CTRL Control Register Flags
 * @{
 */
#define AD5933_CTRL_RESET                   ((uint16_t)0x01 << 4)   //!< Reset bit (Control register D4)
/** @} */

/**
 * @defgroup AD5933_STATUS Status Register Bits
 * 
 * Status register bitmasks
 * @{
 */
#define AD5933_STATUS_VALID_TEMP            ((uint8_t)0x01)     //!< Valid temperature measurement status bit
#define AD5933_STATUS_VALID_IMPEDANCE       ((uint8_t)0x02)     //!< Valid real/imaginary data status bit
#define AD5933_STATUS_SWEEP_COMPLETE        ((uint8_t)0x04)     //!< Frequency sweep complete status bit
/** @} */

/*****************************************************************************
 *                           REGISTER VALUE RANGES                           *
 *****************************************************************************/

/**
 * Maximum number of settling time cycles (Settling time register D8:D0)
 */
#define AD5933_MAX_SETTL                    ((uint16_t)0x1FF)

/**
 * Maximum number of frequency increments (Number of increments register D8:D0)
 */
#define AD5933_MAX_NUM_INCREMENTS           ((uint16_t)0x1FF)

/**
 * Minimum value of the frequency (Start frequency register) with internal clock
 */
#define AD5933_MIN_FREQ                     ((uint32_t)0xFA04)

/**
 * Maximum value of the frequency (Start frequency register + steps) with internal clock
 */
#define AD5933_MAX_FREQ                     ((uint32_t)0x30D4E7)

// Exported functions ---------------------------------------------------------

AD5933_Status AD5933_GetStatus(void);
AD5933_Error AD5933_Init(I2C_HandleTypeDef *i2c);
AD5933_Error AD5933_Reset(void);
AD5933_Error AD5933_MeasureImpedance(AD5933_Sweep *sweep);
AD5933_Error AD5933_MeasureTemperature(void);
AD5933_Error AD5933_Calibrate(AD5933_GainFactorData *data);
void AD5933_TIM_PeriodElapsedCallback(void);

void AD5933_CalculateGainFactor(AD5933_GainFactorData *data, AD5933_GainFactor *gf);
float AD5933_GetMagnitude(AD5933_ImpedanceData *data, AD5933_GainFactor *gain);

// ----------------------------------------------------------------------------

#endif /* AD5933_H_ */
