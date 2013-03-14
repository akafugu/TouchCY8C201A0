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

#include <Wire.h>
#include "TouchCY8C201A0.h"

TouchCY8::TouchCY8(uint8_t addr)
: m_addr(addr)
{
  
}
  
// Low level commands
bool TouchCY8::writeRegister(uint8_t reg)
{
  Wire.beginTransmission(m_addr);
  Wire.write(reg);
  return Wire.endTransmission();
}

bool TouchCY8::writeCommand(uint8_t reg, uint8_t command)
{
  Wire.beginTransmission(m_addr);
  Wire.write(reg);
  Wire.write(command);
  return Wire.endTransmission();
}

bool TouchCY8::writeCommandSequence(uint8_t reg, uint8_t* commands, uint8_t n)
{
  Wire.beginTransmission(m_addr);
  Wire.write(reg);

  for(uint8_t i = 0; i < n; i++) {
    Wire.write(*(commands++));
  }

  return Wire.endTransmission();
}

uint8_t TouchCY8::receiveDataByte()
{
  uint8_t ret = 0xFF;
  
  Wire.requestFrom(m_addr, (uint8_t)1);
  delay(10);

  if(Wire.available())
    ret = Wire.read();

  return ret;
}

void TouchCY8::receiveData(uint8_t* buffer, uint8_t n)
{
  Wire.requestFrom(m_addr, n);
  delay(10);

  uint8_t i = 0;

  while (Wire.available()) {
    buffer[i] = Wire.read();
    i++;
  }
}

uint8_t TouchCY8::getDeviceId()
{
  writeRegister(DEVICE_ID);
  uint8_t ret = receiveDataByte();
  return ret;
}

uint8_t TouchCY8::getDeviceStatus()
{
  writeRegister(DEVICE_STATUS);
  uint8_t ret = receiveDataByte();
  return ret;
}


void TouchCY8::changeI2CAddress(uint8_t old_addr, uint8_t new_addr)
{
  uint8_t unlock[3] = {0x3C, 0xA5, 0x69};
  uint8_t   lock[3] = {0x96, 0x5A, 0xC3};

  // unlock
  writeCommandSequence(I2C_DEV_LOCK, &unlock[0], 3);
  // change address
  writeCommand(0x7C, (0b10000000|new_addr));
  // lock
  writeCommandSequence(I2C_DEV_LOCK, &lock[0], 3);
}

void TouchCY8::enterSetupMode()
{
  writeCommand(COMMAND_REG, 0x08); // enter setup mode
}

void TouchCY8::enterNormalMode()
{
  writeCommand(COMMAND_REG, 0x07); // enter normal mode  
}

void TouchCY8::restoreFactoryDefault()
{
  writeCommand(COMMAND_REG, 0x02); // restore factory defaults
}

void TouchCY8::softwareReset()
{
  writeCommand(COMMAND_REG, 0x08); // enter setup mode
  writeCommand(COMMAND_REG, 0x06); // software reset
}

void TouchCY8::saveToFlash()
{
  writeCommand(COMMAND_REG, 0x01); // save to flash
}

void TouchCY8::setupGPIO(bool gpio0, bool gpio1)
{
  writeCommand(GPIO_ENABLE0, gpio0);
  writeCommand(GPIO_ENABLE1, gpio1);
}

void TouchCY8::setupCapSense(bool cs0, bool cs1)
{
  writeCommand(CS_ENABLE0, cs0);
  writeCommand(CS_ENABLE1, cs1); 
}

uint8_t TouchCY8::readStatus(uint8_t port)
{
  if (port == 0)
    writeRegister(CS_READ_STATUS0);
  else
    writeRegister(CS_READ_STATUS1);
    
  return receiveDataByte();
}

