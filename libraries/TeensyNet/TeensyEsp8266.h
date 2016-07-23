/*  TeensyEsp8266.h
    Version 0.01 03/04/2016
    by Jim Mayhugh
*/
#ifndef TESP_H
#define TESP_H

// ESP8266 Stuff

const uint16_t eeSsidStr = I2CEEPROMesp8266Addr;
const uint16_t eePassStr = eeSsidStr + 0x0020;
const uint16_t eeIpStr   = eePassStr + 0x0020;
const uint16_t eeGwStr   = eeIpStr   + 0x0020;
const uint16_t eeSnStr   = eeGwStr   + 0x0020;
const uint16_t eeUpStr   = eeSnStr   + 0x0020;
const uint16_t eeEipStr  = eeUpStr   + 0x0020;
const uint16_t eeDhcpStr = eeEipStr  + 0x0020;

const uint16_t BUFFER_SIZE = 512;
const uint32_t esp8266baudRate = 921600;

const uint8_t CHPD   = 14;
const uint8_t GPIO2  = 15;
const uint8_t ESPRST = 16;
const uint8_t GPIO0  = 17;
const uint8_t spCnt  = 32;
const uint8_t ipCnt  = 18;
const uint8_t upCnt  = 7;
 
char buffer[BUFFER_SIZE];

char ssidStr[spCnt]  = "";
char passStr[spCnt]  = "";
char ipStr[ipCnt]    = "";
char gwStr[ipCnt]    = "";
char snStr[ipCnt]    = "";
char upStr[upCnt]    = "";
char eipStr[ipCnt]   = "";
char dhcpStr[upCnt]  = "";
char wifiStr[spCnt]  = "";
char wifiPort[upCnt] = "";
char wifiBJ[spCnt]   = "";

uint8_t esp8266z = 0;
uint8_t esp8266c = 0;

bool serialUdpReady = false;
bool useSerial = false;

char serialPacketBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,

#endif
