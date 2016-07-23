/********************

TeensyEsp8266 setupEsp8266.ino

Version 0.0.1
Last Modified 03/06/2016
By Jim Mayhugh


Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

This software uses multiple libraries that are subject to additional
licenses as defined by the author of that software. It is the user's
and developer's responsibility to determine and adhere to any additional
requirements that may arise.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


*********************/

IPAddress strToAddr(char *addrStr)
{
  IPAddress addr;
  char * p;

  addr[0] = atoi(addrStr);
  if(setDebug & esp8266Debug)
  {
    myDebug[debugPort]->print("addr[0] = ");
    myDebug[debugPort]->println(addr[0]);
  }
  p = strchr(addrStr, '.');
  addr[1] = atoi(p+1);
  if(setDebug & esp8266Debug)
  {
    myDebug[debugPort]->print("addr[1] = ");
    myDebug[debugPort]->println(addr[1]);
  }
  p = strchr(p+1, '.');
  addr[2] = atoi(p+1);
  if(setDebug & esp8266Debug)
  {
    myDebug[debugPort]->print("addr[2] = ");
    myDebug[debugPort]->println(addr[2]);
  }
  p = strchr(p+1, '.');
  addr[3] = atoi(p+1);
  if(setDebug & esp8266Debug)
  {
    myDebug[debugPort]->print("addr[3] = ");
    myDebug[debugPort]->println(addr[3]);
  }
  return addr;
}

void readParameters(void)
{
  myDebug[debugPort]->print("readParameters():");
  I2CEEPROM_readAnything(eeSsidStr, ssidStr, I2C0x50);    // get SSID string
  I2CEEPROM_readAnything(eePassStr, passStr, I2C0x50);    // get password string
  I2CEEPROM_readAnything(eeIpStr, ipStr, I2C0x50);        // get Static IP Address string
  I2CEEPROM_readAnything(eeGwStr, gwStr, I2C0x50);        // get Static Gateway Address string
  I2CEEPROM_readAnything(eeSnStr, snStr, I2C0x50);        // get Static Subnet string
  I2CEEPROM_readAnything(eeUpStr, upStr, I2C0x50);        // get UDP Port string
  I2CEEPROM_readAnything(eeDhcpStr, dhcpStr, I2C0x50);    // get UDP Port string
  I2CEEPROM_readAnything(eeEipStr, eipStr, I2C0x50);      // get Ethernet IP Address string
  I2CEEPROM_readAnything(eeEipStr, i2cIPResult, I2C0x50);
  myDebug[debugPort]->println("Finished");
}

void saveParameters(void)
{
  myDebug[debugPort]->print("saveParameters():");
  I2CEEPROM_writeAnything(eeSsidStr, ssidStr, I2C0x50);       // set SSID string
  I2CEEPROM_writeAnything(eePassStr, passStr, I2C0x50);       // set password string
  I2CEEPROM_writeAnything(eeIpStr, ipStr, I2C0x50);           // set Static IP Address string
  I2CEEPROM_writeAnything(eeGwStr, gwStr, I2C0x50);           // set Static Gateway Address string
  I2CEEPROM_writeAnything(eeSnStr, snStr, I2C0x50);           // set Static Subnet string
  I2CEEPROM_writeAnything(eeUpStr, upStr, I2C0x50);           // set UDP Port string
  I2CEEPROM_writeAnything(eeDhcpStr, dhcpStr, I2C0x50);       // set use DHCP string
  I2CEEPROM_writeAnything(eeEipStr, eipStr, I2C0x50);         // set Ethernet IP Address string
  I2CEEPROM_writeAnything(I2CEEPROMipAddr, eipStr, I2C0x50);  // set Ethernet IP Address string
  myDebug[debugPort]->println("Finished");
}

void resetESP8266(void)
{
  // Reset The ESP-01
  myDebug[debugPort]->println("Resetting ESP-01");  
  digitalWrite(ESPRST, LOW);
  delay(500);
  digitalWrite(ESPRST, HIGH);
  if(read_till_eol(500)) myDebug[debugPort]->println(buffer);
  myDebug[debugPort]->println("++ready++");  
  read_till_eol(500);
}

bool read_till_eol(uint32_t timeout)
{
  uint32_t t;
  // wait for at most timeout milliseconds

  t = millis();
  uint16_t i;

  for(i = 0; i < BUFFER_SIZE; i++) buffer[i] = 0xFF;
  i = 0;

  while(millis() < t+timeout)
  {
    if(Serial1.available())
    {
      buffer[i] = Serial1.read();
      if((buffer[i] == 0x0D || buffer[i] == 0x0A))
      {
        while(i < BUFFER_SIZE)
        {
          buffer[i] = 0x00;
          i++;
        }
        return true;
      }else{
        i++;
      }
    }
  }
  return false;
}

void showSetup(void)
{
  myDebug[debugPort]->print("ssid = ");
  myDebug[debugPort]->print(ssidStr);
  myDebug[debugPort]->println(";");
  myDebug[debugPort]->print("pass = ");
  myDebug[debugPort]->print(passStr);
  myDebug[debugPort]->println(";");
  myDebug[debugPort]->print("dhcp = ");
  myDebug[debugPort]->print(dhcpStr);
  myDebug[debugPort]->println(";");
  if( (dhcpStr[0] == 'n') || (dhcpStr[0] == 'N') )
  {
    myDebug[debugPort]->print("Ethernet ip = ");
    myDebug[debugPort]->println(eipStr);
    myDebug[debugPort]->print("WiFi ip = ");
    myDebug[debugPort]->print(ipStr);
    myDebug[debugPort]->println(";");
    myDebug[debugPort]->print("gw = ");
    myDebug[debugPort]->print(gwStr);
    myDebug[debugPort]->println(";");
    myDebug[debugPort]->print("sn = ");
    myDebug[debugPort]->print(snStr);
    myDebug[debugPort]->println(";");
  }
  myDebug[debugPort]->print("udp = ");
  myDebug[debugPort]->print(upStr);
  myDebug[debugPort]->println(";");
}

void setupWiFi(void)
{
//  send SSID
//  showSetup();
  myDebug[debugPort]->print("Sending SSID:");
  Serial1.print("s");
  Serial1.println(ssidStr);

  read_till_eol(4000) ? myDebug[debugPort]->println(buffer) : myDebug[debugPort]->println("FAILED");
  delay(100);
  while(Serial1.available()) Serial1.read();

  // send password
  myDebug[debugPort]->print("Sending password:");
  Serial1.print("p");
  Serial1.println(passStr);

  read_till_eol(4000) ? myDebug[debugPort]->println(buffer) : myDebug[debugPort]->println("FAILED");
  delay(100);
  while(Serial1.available()) Serial1.read();

  if(dhcpStr[0] == 'N' || dhcpStr[0] == 'n')
  {
    // send staticIP
    myDebug[debugPort]->print("Sending staticIP:");
    Serial1.print("i");
    Serial1.println(ipStr);

    read_till_eol(4000) ? myDebug[debugPort]->println(buffer) : myDebug[debugPort]->println("FAILED");
    delay(100);
    while(Serial1.available()) Serial1.read();

    // send gateway address
    myDebug[debugPort]->print("Sending gateway:");
    Serial1.print("g");
    Serial1.println(gwStr);

    read_till_eol(4000) ? myDebug[debugPort]->println(buffer) : myDebug[debugPort]->println("FAILED");
    delay(100);
    while(Serial1.available()) Serial1.read();

    // send subnet address
    myDebug[debugPort]->print("Sending subnet:");
    Serial1.print("n");
    Serial1.println(snStr);

    read_till_eol(4000) ? myDebug[debugPort]->println(buffer) : myDebug[debugPort]->println("FAILED");
    delay(100);
    while(Serial1.available()) Serial1.read();
  }

  // send udpPort
  myDebug[debugPort]->print("Sending udpPort:");
  Serial1.print("u");
  Serial1.println(upStr);

  read_till_eol(4000) ? myDebug[debugPort]->println(buffer) : myDebug[debugPort]->println("FAILED");
  delay(100);
  while(Serial1.available()) Serial1.read();

  bool retry = true;
  // start WiFi
  do
  {
    myDebug[debugPort]->print("Starting Wifi:");
    Serial1.println("c");
    if(read_till_eol(10000))
    {
      myDebug[debugPort]->println(buffer);
      retry = false;
    }else{
      myDebug[debugPort]->println("FAILED");
      softReset();
    }
    delay(100);
    while(Serial1.available()) Serial1.read();
  }while(retry == true);

  char *pch = strtok(buffer, ";");
  strcpy(wifiBJ, pch);
  myDebug[debugPort]->print("wifiBJ = ");
  myDebug[debugPort]->println(wifiBJ);
  pch = strtok(NULL, ";");
  strcpy(wifiPort, pch);
  myDebug[debugPort]->print("wifiPort = ");
  myDebug[debugPort]->println(wifiPort);
  pch = strtok(NULL, ";");
  strcpy(wifiStr, pch);
  myDebug[debugPort]->print("wifiStr = ");
  myDebug[debugPort]->println(wifiStr);

  delay(100);
  while(Serial1.available()) Serial1.read();
  myDebug[debugPort]->println("Sending begin loop()");
  Serial1.println("b");
}

void clearParameters(void)
{
  for(uint8_t esp8266z = 0; esp8266z < spCnt; esp8266z++) // clear ssid and passwd string
  {
    ssidStr[esp8266z] = 0xFF;
    passStr[esp8266z] = 0xFF;
    if(esp8266z < ipCnt)
    {
      ipStr[esp8266z] = 0xFF;
      gwStr[esp8266z] = 0xFF;
      snStr[esp8266z] = 0xFF;
    }
    if(esp8266z < upCnt) upStr[esp8266z] = 0xFF;
  }
}
/*
void getParameters(void)
{
  bool parametersReady = false;
  char delim[] = ";"; 
//  char *result = NULL;
    
  // request autoconnect
  myDebug[debugPort]->print("Requesting Autoconnect:");

  for(uint8_t x = 0; x < numLCDs; x++)
  {
    lcd[x]->clear();
    lcd[x]->home();
    lcd[x]->print(F("Starting Autoconnect"));
    lcd1[x]->clear();
    lcd1[x]->home();
    lcd1[x]->print(F("Starting Autoconnect"));
  }

  Serial1.print("a");
  Serial1.println(upStr);

  while(parametersReady == false)
  {
    if(Serial1.available())
    {
      serialPacketBuffer[esp8266c] = Serial1.read();
      if(setDebug & esp8266Debug) myDebug[debugPort]->print(serialPacketBuffer[esp8266c]);
      if((serialPacketBuffer[esp8266c] == 0x0D || serialPacketBuffer[esp8266c] == 0x0A || serialPacketBuffer[esp8266c] == 0x00))
      {
        serialPacketBuffer[esp8266c] = 0x00;
        if(setDebug & esp8266Debug)
        {
          myDebug[debugPort]->println();
          myDebug[debugPort]->println("ready to process serialUDP");
        }
        parametersReady = true;
      }else{
        esp8266c++;
      }
    }
  }
//  result = strtok( serialPacketBuffer, delim );

  char *ssidStrPtr = strtok( serialPacketBuffer, delim );
  strcpy(ssidStr, ssidStrPtr);
  char *passStrPtr = strtok( NULL, delim );
  strcpy(passStr, passStrPtr);
  char *ipStrPtr   = strtok( NULL, delim );
  strcpy(ipStr, ipStrPtr);
  char *gwStrPtr   = strtok( NULL, delim );
  strcpy(gwStr, gwStrPtr);
  char *snStrPtr   = strtok( NULL, delim );
  strcpy(snStr, snStrPtr);
  char *upStrPtr   = strtok( NULL, delim );
  strcpy(upStr, upStrPtr);
  char *eipStrPtr  = strtok( NULL, delim );
  strcpy(eipStr, eipStrPtr);
  ip = strToAddr(eipStr);
  myDebug[debugPort]->print("EthernetIP:");
  myDebug[debugPort]->println(ip);
  for(uint8_t l = 0; l < 4; l++)
  {
    i2cIPResult[l] = ip[l];
  }
  I2CEEPROM_writeAnything(I2CEEPROMipAddr, i2cIPResult, I2C0x50);
  myDebug[debugPort]->println("Autoconnet Result:");
  showSetup();
  saveParameters();
  lcd[7]->setCursor(0, 3);
  lcd[7]->print(F("Autoconnect Complete"));
}
*/

void setParameters(void)
{
  clearParameters();
  esp8266z = 0;

  while(myDebug[debugPort]->available()) myDebug[debugPort]->read();

  myDebug[debugPort]->print("Enter SSID:");
  while(1)
  {
    while(myDebug[debugPort]->available())
    {
      ssidStr[esp8266z] = myDebug[debugPort]->read();
      if( (ssidStr[esp8266z] == 0x0A) || (ssidStr[esp8266z] == 0x0D) || (ssidStr[esp8266z] == 0x00) )
      {
        ssidStr[esp8266z] = 0x00;
        break;
      }
      esp8266z++;
      if(esp8266z >= spCnt)
      {
        ssidStr[esp8266z] = 0x00;
        break;
      }
    }
    if(ssidStr[esp8266z] == 0x00)
      break;
  }
  myDebug[debugPort]->println(ssidStr);

  esp8266z = 0;
  myDebug[debugPort]->print("Enter PASSWD:");
  while(1)
  {
    while(myDebug[debugPort]->available())
    {
      passStr[esp8266z] = myDebug[debugPort]->read();
      if( (passStr[esp8266z] == 0x0A) || (passStr[esp8266z] == 0x0D) || (passStr[esp8266z] == 0x00) )
      {
        passStr[esp8266z] = 0x00;
        break;
      }
      esp8266z++;
      if(esp8266z >= spCnt)
      {
        passStr[esp8266z] = 0x00;
        break;
      }
    }
    if(passStr[esp8266z] == 0x00)
      break;
  }
  myDebug[debugPort]->println(passStr);


  delay(100);
  while(myDebug[debugPort]->available())
    myDebug[debugPort]->read(); // flush the buffer

  esp8266z = 0;
  
  myDebug[debugPort]->print("Use DHCP:");
  while(1)
  {
    while(myDebug[debugPort]->available())
    {
      dhcpStr[esp8266z] = myDebug[debugPort]->read();
      if( (dhcpStr[esp8266z] == 0x0A) || (dhcpStr[esp8266z] == 0x0D) || (dhcpStr[esp8266z] == 0x00) )
      {
        dhcpStr[esp8266z] = 0x00;
        break;
      }
      esp8266z++;
      if(esp8266z >= spCnt)
      {
        dhcpStr[esp8266z] = 0x00;
        break;
      }
    }
    if(dhcpStr[esp8266z] == 0x00)
      break;
  }
  myDebug[debugPort]->println(dhcpStr);
  
  esp8266z = 0;
  
  if(dhcpStr[0] == 'N' || dhcpStr[0] == 'n')
  {
    myDebug[debugPort]->print("Enter WiFi Static IP:");
    while(1)
    {
      while(myDebug[debugPort]->available())
      {
        ipStr[esp8266z] = myDebug[debugPort]->read();
        if( (ipStr[esp8266z] == 0x0A) || (ipStr[esp8266z] == 0x0D) || (ipStr[esp8266z] == 0x00) )
        {
          ipStr[esp8266z] = 0x00;
          break;
        }
        esp8266z++;
        if(esp8266z >= ipCnt)
        {
          ipStr[esp8266z] = 0x00;
          break;
        } 
      }
      if(ipStr[esp8266z] == 0x00)
        break;
    }
    myDebug[debugPort]->println(ipStr); 

    esp8266z = 0;
    
    myDebug[debugPort]->print("Enter Wired Static IP:");
    while(1)
    {
      while(myDebug[debugPort]->available())
      {
        eipStr[esp8266z] = myDebug[debugPort]->read();
        if( (eipStr[esp8266z] == 0x0A) || (eipStr[esp8266z] == 0x0D) || (eipStr[esp8266z] == 0x00) )
        {
          eipStr[esp8266z] = 0x00;
          break;
        }
        esp8266z++;
        if(esp8266z >= ipCnt)
        {
          eipStr[esp8266z] = 0x00;
          break;
        } 
      }
      if(eipStr[esp8266z] == 0x00)
        break;
    }
    ip = strToAddr(eipStr);
    for(uint y = 0; y < 4; y++) i2cIPResult[y] = ip[y];
    myDebug[debugPort]->println(ip); 
    esp8266z = 0;
    
    while(myDebug[debugPort]->available())
      myDebug[debugPort]->read(); // flush the buffer
      
    myDebug[debugPort]->print("Enter Static Gateway:");
    while(1)
    {
      while(myDebug[debugPort]->available())
      {
        gwStr[esp8266z] = myDebug[debugPort]->read();
        if( (gwStr[esp8266z] == 0x0A) || (gwStr[esp8266z] == 0x0D) || (gwStr[esp8266z] == 0x00) )
        {
          gwStr[esp8266z] = 0x00;
          break;
        }
        esp8266z++;
        if(esp8266z >= ipCnt)
        {
          myDebug[debugPort]->println("String Too Long");
          gwStr[esp8266z] = 0x00;
          break;
        } 
      }
      if(gwStr[esp8266z] == 0x00)
      {
        break;
      }
    }
    myDebug[debugPort]->println(gwStr); 

    esp8266z = 0;
    
    while(myDebug[debugPort]->available())
      myDebug[debugPort]->read(); // flush the buffer
      
    myDebug[debugPort]->print("Enter Static subnet:");
    while(1)
    {
      while(myDebug[debugPort]->available())
      {
        snStr[esp8266z] = myDebug[debugPort]->read();
        if( (snStr[esp8266z] == 0x0A) || (snStr[esp8266z] == 0x0D) || (snStr[esp8266z] == 0x00) )
        {
          snStr[esp8266z] = 0x00;
          break;
        }
        esp8266z++;
        if(esp8266z >= ipCnt)
        {
          snStr[esp8266z] = 0x00;
          break;
        } 
      }
      if(snStr[esp8266z] == 0x00)
        break;
    }
    myDebug[debugPort]->println(snStr); 
  }

  while(myDebug[debugPort]->available())
    myDebug[debugPort]->read(); // flush the buffer

  esp8266z = 0;
  
  myDebug[debugPort]->print("Enter UDP Port:");

  while(1)
  {
    while(myDebug[debugPort]->available())
    {
      upStr[esp8266z] = myDebug[debugPort]->read();
      if( (upStr[esp8266z] == 0x0A) || (upStr[esp8266z] == 0x0D) || (upStr[esp8266z] == 0x00) )
      {
        upStr[esp8266z] = 0x00;
        break;
      }
      esp8266z++;
      if(esp8266z >= upCnt)
      {
        upStr[esp8266z] = 0x00;
        break;
      }
    }
    if(upStr[esp8266z] == 0x00)
      break;
  }
  myDebug[debugPort]->println(upStr);
  saveParameters();
  readParameters();
  showSetup();
}

