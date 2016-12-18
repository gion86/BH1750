/*
 * This library is for Digital Light sensor BH1750FVI,
 * uses I2C Communication protocol to interface with the sensor.
 *
 * Revision merged with library from Christopher Laws, March, 2013.
 * Credits for the first version to: Mohannad Rawashdeh, www.genotronex.com.
 *
 * Modified to use a private: USI_TWI &busI2C reference at the I2C bus
 * from the application.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef BH1750FVI_h
#define BH1750FVI_h

#include "Arduino.h"
#include "TinyWireM.h"

// Device address when address pin LOW: default
#define BH1750_I2CADDR_L                    0x23

// Device address when address pin HIGH
#define BH1750_I2CADDR_H                    0x5C

// #############################################################
// All command here taken from Data sheet OPECODE Table page 5
// #############################################################

// No active state
#define BH1750_POWER_DOWN                   0x00

// Waiting for measurement command
#define BH1750_POWER_ON                     0x01

// Reset data register value - not accepted in POWER_DOWN mode
#define BH1750_RESET                        0x07

// Start measurement at 1lx resolution. Measurement time is approx 120ms.
#define BH1750_CONTINUOUS_HIGH_RES_MODE     0x10

// Start measurement at 0.5lx resolution. Measurement time is approx 120ms.
#define BH1750_CONTINUOUS_HIGH_RES_MODE_2   0x11

// Start measurement at 4lx resolution. Measurement time is approx 16ms.
#define BH1750_CONTINUOUS_LOW_RES_MODE      0x13

// Start measurement at 1lx resolution. Measurement time is approx 120ms.
// Device is automatically set to Power Down after measurement.
#define BH1750_ONE_TIME_HIGH_RES_MODE       0x20

// Start measurement at 0.5lx resolution. Measurement time is approx 120ms.
// Device is automatically set to Power Down after measurement.
#define BH1750_ONE_TIME_HIGH_RES_MODE_2     0x21

// Start measurement at 1lx resolution. Measurement time is approx 120ms.
// Device is automatically set to Power Down after measurement.
#define BH1750_ONE_TIME_LOW_RES_MODE        0x23

// Default measurement accuracy
#define LUX_ACC_COEF                        1.2

// Default value for measurement time register (MTReg, from datasheet)
#define MTREG_DEF_VALUE                     69

/**
 * The I2C library actually supported is only TinyWireM, to save
 * code space on the small ATTiny MCU.
 * A reference to the library has to be passed to this class.
 */
class BH1750FVI {
public:
  /**
   * Constructor
   *
   * bus: I2C (TWI) communication bus instance, only TinywireM is supported
   */
  BH1750FVI(USI_TWI &bus);

  /**
   * The powerOn() method has to be called after begin() on the I2C bus
   */
  void powerOn(void);

  /**
   * Put the sensor to powerdown state: powerOn() or setMode() wake up the device
   */
  void sleep(void);

  /**
   * Reset the internal data register (holds the last sensed data)
   */
  void reset(void);

  /**
   * Wake up with default mode, and with custom mode
   */
  void wakeUp();
  void wakeUp(uint8_t mode);

  /**
   * Get/set measurement time register value [31..254]
   */
  uint8_t getMtreg();
  void setMtreg(uint8_t mtreg);

  /**
   * Get/set measurement mode
   */
  uint8_t getMode();
  void setMode(uint8_t mode);

  /**
   * Set address to be "high" or "low", with the corresponding output pin
   */
  void setAddress(uint8_t addPin, boolean add);
  /**
   * Get current device I2C address:
   */
  uint8_t getAddress();

  /**
   * Returns light intensity in lux: range and accuracy depend on
   * sensor mode configuration
   */
  float getLightIntensity(void);

private:
  void writeToBus(uint8_t DataToSend);
  uint8_t address;
  uint8_t currentMode;

  // Measurement time register
  float mtreg;

  // High resolution coefficient = [1.0, 2.0]
  float hiResCoef;

  USI_TWI &busI2C;
};

#endif

