/*
 * TouchCY8C201A0 - Library for CY8C201A0 CapSense Controller
 * Simple demo: Count to 9999
 * (C) 2011 Akafugu Corporation
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
 
#include <stdint.h>

#define CY8C201A0_SLAVE_ADDR 0x0

enum CY8_RegisterMap
{
  INPUT_PORT0  = 0x00,
  INPUT_PORT1  = 0x01,
  STATUS_PORT0 = 0x02,
  STATUS_PORT1 = 0x03,
  OUTPUT_PORT0 = 0x04,
  OUTPUT_PORT1 = 0x05,
  CS_ENABLE0 = 0x06,
  CS_ENABLE1 = 0x07,
  GPIO_ENABLE0 = 0x08,
  GPIO_ENABLE1 = 0x09,
  // 0x08~17
  // 0x1c-
    
  CS_NOISE_TH = 0x4E,
  CS_BL_UPD_TH = 0x4F,

  CS_SCAN_POS_00 = 0x57,
  CS_SCAN_POS_01 = 0x58,
  CS_SCAN_POS_02 = 0x59,
  CS_SCAN_POS_03 = 0x5A,
  CS_SCAN_POS_04 = 0x5B,
  CS_SCAN_POS_10 = 0x5C,
  CS_SCAN_POS_11 = 0x5D,
  CS_SCAN_POS_12 = 0x5E,
  CS_SCAN_POS_13 = 0x5F,
  CS_SCAN_POS_14 = 0x60,

  CS_FINGER_TH_00 = 0x61,
  CS_FINGER_TH_01 = 0x62,
  CS_FINGER_TH_02 = 0x63,
  CS_FINGER_TH_03 = 0x64,
  CS_FINGER_TH_04 = 0x65,
  CS_FINGER_TH_10 = 0x66,
  CS_FINGER_TH_11 = 0x67,
  CS_FINGER_TH_12 = 0x68,
  CS_FINGER_TH_13 = 0x69,
  CS_FINGER_TH_14 = 0x6A,

  DEVICE_ID = 0x7A,
  DEVICE_STATUS = 0x7B,

  CS_SLID_CONFIG = 0x75,
  I2C_DEV_LOCK = 0x79,

  CS_READ_BUTTON = 0x81,
  CS_READ_BLM = 0x82,
  CS_READ_STATUS0 = 0x88,
  CS_READ_STATUS1 = 0x89,
  COMMAND_REG = 0xA0,
};
///

class TouchCY8
{
private:
  uint8_t m_addr;

public:
  TouchCY8(uint8_t addr = CY8C201A0_SLAVE_ADDR);
  
  // Low level commands
  bool writeRegister(uint8_t reg);
  bool writeCommand(uint8_t reg, uint8_t command);
  bool writeCommandSequence(uint8_t reg, uint8_t* commands, uint8_t n);
  uint8_t receiveDataByte();
  void receiveData(uint8_t* buffer, uint8_t n);
  
  // High-level commands
  uint8_t getDeviceId();
  uint8_t getDeviceStatus();
  
  void changeI2CAddress(uint8_t old_addr, uint8_t new_addr);
  
  void enterSetupMode();
  void enterNormalMode();
  
  void restoreFactoryDefault();
  void softwareReset();
  void saveToFlash();
  
  // GPIO / buttons / sliders configuration
  void setupGPIO(bool gpio0, bool gpio1);
  void setupCapSense(bool cs0, bool cs1);
  
  // Read status
  uint8_t readStatus(uint8_t port);
};

