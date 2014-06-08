/**
 * @file    strings_en.h
 * @author  Peter
 * @date    06.06.2014
 * @brief   Defines user interface strings in English.
 */

#ifndef STRINGS_EN_H_
#define STRINGS_EN_H_

// Console strings ------------------------------------------------------------
// XXX Maybe there should be some kind of error code prefix for parsing by PC software
const char *txtErrArgNum = "Wrong number of arguments.";
const char *txtErrNoSubcommand = "Missing command, type 'help' for possible commands.";
const char *txtUnknownTopic = "Unknown help topic, type 'help' for possible commands.";
const char *txtUnknownCommand = "Unknown command.";
const char *txtUnknownSubcommand = "Unknown subcommand.";
const char *txtNotImplemented = "Not yet implemented.";
const char *txtUnknownOption = "Unknown option.";
const char *txtInvalidValue = "Invalid value for this argument: ";
const char *txtSetOnlyWhenIdle = "This value cannot be set while a sweep is running: ";
const char *txtEffectiveNextSweep = "Autorange setting will take effect on the next sweep.";
const char *txtSetOnlyWhenAutorangeDisabled = "This value can only be set when autoranging is disabled: ";
const char *txtGetOnlyWhenAutorangeDisabled = "This value can only be read when autoranging is disabled.";

// Words ----------------------------------------------------------------------
const char *txtEnabled = "enabled";
const char *txtDisabled = "disabled";
const char *txtOn = "on";
const char *txtOff = "off";

// ----------------------------------------------------------------------------

#endif /* STRINGS_EN_H_ */
