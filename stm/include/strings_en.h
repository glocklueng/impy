/**
 * @file    strings_en.h
 * @author  Peter Feichtinger
 * @date    06.06.2014
 * @brief   Defines user interface strings in English.
 */

#ifndef STRINGS_EN_H_
#define STRINGS_EN_H_

// Constants ------------------------------------------------------------------
#define THIS_IS_IMPY    "This is impy version "
#define BUILT_ON        " built on "

// Console strings ------------------------------------------------------------
// XXX Maybe there should be some kind of error code prefix for parsing by PC software
const char* const txtErrArgNum = "Wrong number of arguments.";
const char* const txtErrNoArgs = "No arguments expected.";
const char* const txtErrNoSubcommand = "Missing command, type 'help' for possible commands.";
const char* const txtUnknownTopic = "Unknown help topic, type 'help' for possible commands.";
const char* const txtUnknownCommand = "Unknown command.";
const char* const txtUnknownSubcommand = "Unknown subcommand.";
const char* const txtNotImplemented = "Not yet implemented.";
const char* const txtUnknownOption = "Unknown option: ";
const char* const txtOnlyOneArg = "Only one of the options can be used at a time.";
const char* const txtOops = "An unknown error occurred, panic.";
// board get, board set
const char* const txtInvalidValue = "Invalid value for this argument: ";
const char* const txtSetOnlyWhenIdle = "This value cannot be set while a sweep is running: ";
const char* const txtEffectiveNextSweep = "Autorange setting will take effect on the next sweep.";
const char* const txtSetOnlyWhenAutorangeDisabled = "This value can only be set when autoranging is disabled: ";
const char* const txtGetOnlyWhenAutorangeDisabled = "This value can only be read when autoranging is disabled.";
// board status
const char* const txtAdStatusUnknown = "Unknown AD5933 driver status, something went wrong.";
const char* const txtAdStatusSweep = "Impedance measurement is running, points measured: ";
const char* const txtAdStatusTemp = "Temperature measurement is running.";
const char* const txtAdStatusIdle = "No measurement is running.";
const char* const txtAdStatusFinishImpedance = "Impedance measurement finished, points measured: ";
const char* const txtAdStatusCalibrate = "Calibration measurement is running.";
const char* const txtAutorangeStatus = "Autoranging is ";
const char* const txtLastInterrupted = "The last measurement was interrupted.";
const char* const txtValidData = "Measurement data can be read.";
const char* const txtNoData = "No measurement data is present.";
const char* const txtValidGain = "Calibration finished, measurement can be started.";
const char* const txtNoGain = "Calibration needed before measurement can be started.";
// board info
const char* const txtAdStatus = "AD5933 driver status: ";
const char* const txtAdStatusMeasureImpedance = "Impedance measurement is running.";
const char* const txtPortsAvailable = "Ports available for measurements: ";
const char* const txtAttenuationsAvailable = "Possible voltage attenuation factors: ";
const char* const txtFeedbackResistorValues = "Feedback resistor values: ";
const char* const txtCalibrationValues = "Calibration resistor values: ";
const char* const txtEthernet = "Ethernet";
const char* const txtUSB = "USB";
const char* const txtSRAM = "SRAM";
const char* const txtFlash = "Flash";
const char* const txtEEPROM = "EEPROM";
const char* const txtNotInstalled = " not installed.";
const char* const txtNoMemory = "\r\nNo external memory installed.";
const char* const txtFrequencyRange = "Possible frequency range in Hz: ";
const char* const txtMaxNumIncrements = "Maximum number of frequency increments: ";
const char* const txtInstalledSize = " installed, size in bytes: ";
const char* const txtEthernetInstalledMacAddr = "Ethernet installed, MAC address: ";
// board measure
const char* const txtBoardBusy = "Another measurement is currently running.";
const char* const txtImpedance = "Impedance (polar): ";
// board read
const char* const txtNoReadWhileBusy = "Data can only be read after the measurement is finished.";
const char* const txtOutOfMemory = "Not enough memory to send all data, try binary format or use fewer points.";
const char* const txtNotCalibrated = "Calibration not performed.";
const char* const txtNoRawData = "No raw data is present (raw data is not retained when autoranging is enabled).";
// board calibrate
const char* const txtWrongCalibValue = "Unknown resistor value, see 'board info' for possible values.";
// board temp
const char* const txtTempFail = "Temperature measurement failed.";
// setup
const char* const txtWrongFlag = "Invalid flag, 'on' or 'off' expected.";
const char* const txtWrongTau = "Invalid time constant, needs to be a number in the range 0 to 1000";
const char* const txtWrongNumber = "Invalid number.";
const char* const txtWrongMac = "Invalid MAC address.";
const char* const txtUnknownConfig = "Unknown configuration command.";

// Words ----------------------------------------------------------------------
const char* const txtEnabled = "enabled";
const char* const txtDisabled = "disabled";
const char* const txtOn = "on";
const char* const txtOff = "off";
const char* const txtOf = " of ";
const char* const txtOK = "OK";

// ----------------------------------------------------------------------------

#endif /* STRINGS_EN_H_ */
