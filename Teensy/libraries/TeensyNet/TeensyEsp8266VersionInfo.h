/*  TeensyEsp8266VersionInfo.h
    Version 0.0.1 03/06/2016
    by Jim Mayhugh
*/
#ifndef TEVI_H
#define TEVI_H

#define __ESP8266__

#if __MK20DX128__
const char* teensyType = "Teensy3.0 ";
const char* versionStrName   = "TeensyESP8266 3.0";
#elif __MK20DX256__
const char* teensyType = "Teensy3.x ";
const char* versionStrName   = "TeensyESP8266 3.1";
#else
const char* teensyType = "UNKNOWN ";
#endif

const char* versionStrNumber = "V-0.0.2";
const char* versionStrDate   = "04/20/2016";

const uint8_t boardVersion = 18; // board versions below 18 use reverse logic for LEDs and test points
const uint8_t ledON  = 0x00;
const uint8_t ledOFF = 0xFF;

/* Version History
V-0.0.1 - Initial Release
*/
#endif
