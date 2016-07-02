/*  TeensyLCDShield.h
    Version 0.01 0831/2014
    by Jim Mayhugh
*/
#ifndef TLCD_H
#define TLCD_H

// The shield uses the I2C SCL and SDA pins. 
// You can connect other I2C sensors to the I2C bus and share
// the I2C bus.

// I2C Channel 1 - Teensy3.x
Teensy_RGBLCDShield LCD00 = Teensy_RGBLCDShield(0);
Teensy_RGBLCDShield LCD01 = Teensy_RGBLCDShield(1);
Teensy_RGBLCDShield LCD02 = Teensy_RGBLCDShield(2);
Teensy_RGBLCDShield LCD03 = Teensy_RGBLCDShield(3);
Teensy_RGBLCDShield LCD04 = Teensy_RGBLCDShield(4);
Teensy_RGBLCDShield LCD05 = Teensy_RGBLCDShield(5);
Teensy_RGBLCDShield LCD06 = Teensy_RGBLCDShield(6);
Teensy_RGBLCDShield LCD07 = Teensy_RGBLCDShield(7);

Teensy_RGBLCDShield *lcd[] = { &LCD00, &LCD01, &LCD02, &LCD03, &LCD04, &LCD05, &LCD06, &LCD07 };

// I2C Channel 2 - Teensy3.1 and Teensy3.2 only
Teensy_RGBLCDShield1 LCD10 = Teensy_RGBLCDShield1(0);
Teensy_RGBLCDShield1 LCD11 = Teensy_RGBLCDShield1(1);
Teensy_RGBLCDShield1 LCD12 = Teensy_RGBLCDShield1(2);
Teensy_RGBLCDShield1 LCD13 = Teensy_RGBLCDShield1(3);
Teensy_RGBLCDShield1 LCD14 = Teensy_RGBLCDShield1(4);
Teensy_RGBLCDShield1 LCD15 = Teensy_RGBLCDShield1(5);
Teensy_RGBLCDShield1 LCD16 = Teensy_RGBLCDShield1(6);
Teensy_RGBLCDShield1 LCD17 = Teensy_RGBLCDShield1(7);

Teensy_RGBLCDShield1 *lcd1[] = { &LCD10, &LCD11, &LCD12, &LCD13, &LCD14, &LCD15, &LCD16, &LCD17 };


// These #defines make it easy to set the backlight color
#define BL_RED 0x1
#define BL_YELLOW 0x3
#define BL_GREEN 0x2
#define BL_TEAL 0x6
#define BL_BLUE 0x4
#define BL_VIOLET 0x5
#define BL_WHITE 0x7

uint8_t const lcdChars = 20;
uint8_t const lcdRows  = 4;
uint8_t const numLCDs  = 8;

char lcdStr[lcdChars + 1];
char lcdStrBuf[lcdChars + 1];

// End LCD Stuff
#endif
