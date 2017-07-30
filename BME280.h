/*******************************************************************************************************************
** Class definition header for the Bosch BME280 temperature / humidity / pressure sensor. The sensor is described **
** at https://www.bosch-sensortec.com/bst/products/all_products/bme280 and the datasheet is available from Bosch  **
** at https://ae-bst.resource.bosch.com/media/_tech/media/datasheets/BST-BME280_DS001-11.pdf                      **
**                                                                                                                **
** The BME280 uses either SPI or I2C. The initial library version uses only I2C.                                  **
**                                                                                                                **
** The most recent version of the library is available at
** Although programming for the Arduino and in c/c++ is new to me, I'm a professional programmer and have learned,**
** over the years, that it is much easier to ignore superfluous comments than it is to decipher non-existent ones;**
** so both my comments and variable names tend to be verbose. The code is written to fit in the first 80 spaces   **
** and the comments start after that and go to column 117 - allowing the code to be printed in A4 landscape mode. **
**                                                                                                                **
** This program is free software: you can redistribute it and/or modify it under the terms of the GNU General     **
** Public License as published by the Free Software Foundation, either version 3 of the License, or (at your      **
** option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY     **
** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the   **
** GNU General Public License for more details. You should have received a copy of the GNU General Public License **
** along with this program.  If not, see <http://www.gnu.org/licenses/>.                                          **
**                                                                                                                **
** Vers.  Date       Developer           Comments                                                                 **
** ====== ========== =================== ======================================================================== **
** 1.0.0b 2017-07-30 Arnd@SV-Zanshin.Com Initial coding                                                           **
**                                                                                                                **
*******************************************************************************************************************/
#include "Arduino.h"                                                          // Arduino data type definitions    //
#include <Wire.h>                                                             // Standard I2C "Wire" library      //
#ifndef BME280_h                                                              // Guard code definition            //
  #define BME280_h                                                            // Define the name inside guard code//
  /*****************************************************************************************************************
  ** Declare constants used in the class                                                                          **
  *****************************************************************************************************************/
  const uint8_t  BME280_ADDRESS          = 0x77;                              // Device address power-up default  //
  const uint8_t  BME280_I2C_DELAY        =    0;                              // I2C and write time delay         //
  const uint8_t  BME280_T1_REG           = 0x88;                              //                                  //
  const uint8_t  BME280_T2_REG           = 0x8A;                              //                                  //
  const uint8_t  BME280_T3_REG           = 0x8C;                              //                                  //
  const uint8_t  BME280_P1_REG           = 0x8E;                              //                                  //
  const uint8_t  BME280_P2_REG           = 0x90;                              //                                  //
  const uint8_t  BME280_P3_REG           = 0x92;                              //                                  //
  const uint8_t  BME280_P4_REG           = 0x94;                              //                                  //
  const uint8_t  BME280_P5_REG           = 0x96;                              //                                  //
  const uint8_t  BME280_P6_REG           = 0x98;                              //                                  //
  const uint8_t  BME280_P7_REG           = 0x9A;                              //                                  //
  const uint8_t  BME280_P8_REG           = 0x9C;                              //                                  //
  const uint8_t  BME280_P9_REG           = 0x9E;                              //                                  //
  const uint8_t  BME280_H1_REG           = 0xA1;                              //                                  //
  const uint8_t  BME280_H2_REG           = 0xE1;                              //                                  //
  const uint8_t  BME280_H3_REG           = 0xE3;                              //                                  //
  const uint8_t  BME280_H4_REG           = 0xE4;                              //                                  //
  const uint8_t  BME280_H5_REG           = 0xE5;                              //                                  //
  const uint8_t  BME280_H6_REG           = 0xE7;                              //                                  //
  const uint8_t  BME280_CHIPID_REG       = 0xD0;                              //                                  //
  const uint8_t  BME280_VERSION_REG      = 0xD1;                              //                                  //
  const uint8_t  BME280_SOFTRESET_REG    = 0xE0;                              //                                  //
  const uint8_t  BME280_CAL26_REG        = 0xE1;                              // R calibration stored in 0xE1-0xF0//
  const uint8_t  BME280_CONTROLHUMID_REG = 0xF2;                              //                                  //
  const uint8_t  BME280_CONTROL_REG      = 0xF4;                              //                                  //
  const uint8_t  BME280_CONFIG_REG       = 0xF5;                              //                                  //
  const uint8_t  BME280_PRESSUREDATA_REG = 0xF7;                              //                                  //
  const uint8_t  BME280_TEMPDATA_REG     = 0xFA;                              //                                  //
  const uint8_t  BME280_HUMIDDATA_REG    = 0xFD;                              //                                  //
  /*****************************************************************************************************************
  ** Declare enumerated types used in the class                                                                   **
  *****************************************************************************************************************/
  enum modeTypes         {SleepMode,ForcedMode,ForcedMode2,NormalMode,        // Enumerate device modes           //
                          UnknownMode };                                      //                                  //
  enum sensorTypes       {TemperatureSensor,HumiditySensor,PressureSensor,    // Enumerate the sensor types       //
                          UnknownSensor};                                     //                                  //
  enum oversamplingTypes {NoOversampling,Oversample1,Oversample2,Oversample4, // Enumerate oversampling values    //
                          Oversample8,Oversample16,UnknownOversample };       //                                  //
  /*****************************************************************************************************************
  ** Main BME280 class for the temperature / humidity / pressure sensor                                           **
  *****************************************************************************************************************/
  class BME280_Class {                                                        // Class definition                 //
    public:                                                                   // Publicly visible methods         //
      BME280_Class();                                                         // Class constructor                //
      ~BME280_Class();                                                        // Class destructor                 //
      bool     begin(const uint8_t I2CAddress = BME280_ADDRESS );             // I2C Communications at address    //
      uint8_t  mode();                                                        // return device mode               //
      uint8_t  mode(const uint8_t operatingMode);                             // Set device mode                  //
      bool     setOversampling(const uint8_t sensor, const uint8_t sampling); // Set enum sensorType Oversampling //
      uint8_t  getOversampling(const uint8_t sensor);                         // Get enum sensorType oversampling //
    private:                                                                  // Private methods                  //
      bool     writeI2C(const uint8_t addr,uint8_t *pdata,                    // Write n-Bytes to I2C             //
                        const uint8_t bytesToWrite);                          //                                  //
      uint8_t  readI2C(const uint8_t addr, uint8_t *pdata,                    // Read n-Bytes from I2C            //
                       const uint8_t bytesToRead);                            //                                  //
      uint8_t  readByte(const uint8_t addr);                                  // Read 1 byte from address on I2C  //
      void     writeByte(const uint8_t addr, const uint8_t data);             // Write 1 byte at address to I2C   //
      uint16_t readWord(const uint8_t addr);                                  // Read 2 byte from address on I2C  //
      uint16_t readWordLE(const uint8_t addr);                                // Read 2 byte from address on I2C  //
      void     writeWord(const uint8_t addr, const uint16_t data);            // Write 2 bytes at address to I2C  //
      bool     _TransmissionStatus = false;                                   // I2C communications status        //
      uint8_t  _I2CAddress         = BME280_ADDRESS;                          // Actual I2C address used w/default//
      uint16_t _cal_dig_T1         = 0;                                       //                                  //
      int16_t  _cal_dig_T2         = 0;                                       //                                  //
      int16_t  _cal_dig_T3         = 0;                                       //                                  //
      uint16_t _cal_dig_P1         = 0;                                       //                                  //
      int16_t  _cal_dig_P2         = 0;                                       //                                  //
      int16_t  _cal_dig_P3         = 0;                                       //                                  //
      int16_t  _cal_dig_P4         = 0;                                       //                                  //
      int16_t  _cal_dig_P5         = 0;                                       //                                  //
      int16_t  _cal_dig_P6         = 0;                                       //                                  //
      int16_t  _cal_dig_P7         = 0;                                       //                                  //
      int16_t  _cal_dig_P8         = 0;                                       //                                  //
      int16_t  _cal_dig_P9         = 0;                                       //                                  //
      uint8_t  _cal_dig_H1         = 0;                                       //                                  //
      int16_t  _cal_dig_H2         = 0;                                       //                                  //
      uint8_t  _cal_dig_H3         = 0;                                       //                                  //
      int16_t  _cal_dig_H4         = 0;                                       //                                  //
      int16_t  _cal_dig_H5         = 0;                                       //                                  //
      int8_t   _cal_dig_H6         = 0;                                       //                                  //
  }; // of BME280 class definition                                            //                                  //
#endif                                                                        //----------------------------------//