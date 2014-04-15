/**
 * @file    ad5933.c
 * @author  Peter Feichtinger
 * @date    15.04.2014
 * @brief   This file contains functions to manage the AD5933 Impedance Converter Network Analyzer chip.
 */

// Includes -------------------------------------------------------------------
#include <math.h>
#include "ad5933.h"

// Exported functions ---------------------------------------------------------

/**
 * Calculates gain factor values from measurement data. The data can be one or two point calibration measurements.
 * 
 * @param data The measurement data to calculate the gain factor from
 * @param gf Pointer to a gain factor structure to be populated
 */
void AD5933_CalculateGainFactor(AD5933_GainFactorData *data, AD5933_GainFactor *gf)
{
    // Gain factor is calculated by 1/(Magnitude * Impedance), with Magnitude being sqrt(Real^2 + Imag^2)
    float magnitude = hypotf(data->real1, data->imag1);
    float gain2;

    gf->is_2point = data->is_2point;
    gf->freq1 = data->freq1;
    gf->offset = 1.0f / (magnitude * (float)data->impedance);
    
    if(data->is_2point)
    {
        magnitude = hypotf(data->real2, data->imag2);
        gain2 = 1.0f / (magnitude * (float)data->impedance);
        
        gf->slope = (gain2 - gf->offset) / (float)(data->freq2 - data->freq1);
    }
}

/**
 * Calculates the actual impedance magnitude from a measurement data point.
 * 
 * @param data The measurement point to calculate the magnitude from
 * @param gain Gain factor structure to use
 * @return
 */
float AD5933_GetMagnitude(AD5933_Impedance *data, AD5933_GainFactor *gain)
{
    // Actual impedance is calculated by 1/(Magnitude * Gain Factor), with Magnitude being sqrt(Real^2 + Imag^2)
    float magnitude = hypotf(data->Real, data->Imag);
    float gain_2point = gain->offset;
    
    if(gain->is_2point)
    {
        gain_2point += gain->slope * (data->Frequency - gain->freq1);
    }
    
    return 1.0f / (gain_2point * magnitude);
}

// ----------------------------------------------------------------------------