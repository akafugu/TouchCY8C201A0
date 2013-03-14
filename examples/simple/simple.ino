/*
 * TouchCY8C201A0 - Library for CY8C201A0 CapSense Controller
 * (C) 2013 Akafugu Corporation
 *
 * This program is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 */

// documentation:
// http://www.cypress.com/?docID=41921
// 

#include <Wire.h>
#include <TouchCY8C201A0.h>

TouchCY8 touch;

void setup()
{
#ifdef __AVR_ATmega32U4__
  while (!Serial) {}
#endif

  Wire.begin();
  Serial.begin(9600);

  Serial.print("Device id = ");
  Serial.println(touch.getDeviceId(), HEX);

  Serial.print("Device status = ");
  Serial.println(touch.getDeviceStatus(), HEX);

  // Device setup
  touch.enterSetupMode();
  touch.restoreFactoryDefault();

  // I/O port setup
  delay(150);
  touch.setupGPIO(false, false); // disable both GPIO ports
  touch.setupCapSense(0b00011111, 0b00011111); // enable capsense for GP0[0:4] and GP1[0:4]

  touch.writeCommand(CS_NOISE_TH, 0x03);  // noise threshold
  touch.writeCommand(CS_BL_UPD_TH, 0x0F); // bucket
  
  touch.writeCommand(0x1C,0x80);
  touch.writeCommand(0x1D,0x01);

  touch.writeCommand(CS_FINGER_TH_00, 0x32);
  touch.writeCommand(CS_FINGER_TH_01, 0x32);
  touch.writeCommand(CS_FINGER_TH_02, 0x32);
  touch.writeCommand(CS_FINGER_TH_03, 0x32);
  touch.writeCommand(CS_FINGER_TH_04, 0x32);
  touch.writeCommand(CS_FINGER_TH_10, 0x32);
  touch.writeCommand(CS_FINGER_TH_11, 0x32);

  touch.saveToFlash();
  delay(120);
  touch.softwareReset();
  delay(50);
  touch.enterNormalMode();
  delay(100);
}

void loop()
{
  Serial.print("Port 0: ");
  Serial.println(touch.readStatus(0), BIN);

  Serial.print("Port 1: ");
  Serial.println(touch.readStatus(1), BIN);
  
  delay(250);
}
