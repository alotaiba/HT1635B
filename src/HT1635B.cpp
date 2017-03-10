/* HT1635B library by Abdulrahman Saleh Khamis
 */

#include "HT1635B.h"

HT1635B::HT1635B() {
  i2caddr_ = 0;
  memset(row_, 0, sizeof(row_));
}

void HT1635B::begin(uint8_t i2caddr) {
  i2caddr_ = i2caddr;
  Wire.begin();

  // Set N-MOS
  setCOM(0);
  // No blink
  setBlinking(0);
  // RC master mode 0, use on chip OSC, OSC pin Hi-Z, Sync pin high
  setOSC(4);
  // System enabled, LED on
  setSystemMode(3);
  // Brightness level 1 (low)
  setBrightness(1);

  clear();
  render();
}

void HT1635B::setRowMemory(uint8_t index, uint8_t data) {
  row_[index] |= data;
}

void HT1635B::clearRowMemory(uint8_t index, uint8_t data) {
  row_[index] &= ~(data);
}

void HT1635B::setPixel(int x, int y) {
  setRowMemory(x, getYByteLocation_(y));
}

void HT1635B::clearPixel(int x, int y) {
  clearRowMemory(x, getYByteLocation_(y));
}

void HT1635B::clear() {
  memset(row_, 0, sizeof(row_));
}

void HT1635B::render() {
  //I2c buffer is only 32 byte
  //since the RAM data is 44 bytes long
  //it needs to be sent in two chunks
  Wire.beginTransmission(i2caddr_);
  Wire.write(HT1632B_CMD_RAM_W);
  Wire.write(0x00); //address for row 0
  for (size_t j = 0; j < 30; j++) { // draw row 0 -> row 29
    Wire.write(row_[j]);
  }
  Wire.endTransmission();

  Wire.beginTransmission(i2caddr_);
  Wire.write(HT1632B_CMD_RAM_W);
  Wire.write(0x3C); //address for row 30
  for (size_t j = 30; j < 44; j++) { // draw row 30 -> row 43
    Wire.write(row_[j]);
  }
  Wire.endTransmission();
}


void HT1635B::setBrightness(uint8_t brightness) {
  /**
  * Power-on default is highest brightness (15)
  * 0-lowest to 15-highest
  */
  Wire.beginTransmission(i2caddr_);
  Wire.write(HT1635B_CMD_BRIGHTNESS);
  Wire.write(brightness);
  Wire.endTransmission();
}

void HT1635B::setBlinking(uint8_t speed) {
  /**
  * Power-on default is no blink
  * 0: No blink
  * 1: 2Hz blink (2 blinks per second) fastest
  * 2: 1Hz blink (1 blink per second) normal
  * 3: 0.5Hz blink (1 second on/1 second off) slow
  */
  Wire.beginTransmission(i2caddr_);
  Wire.write(HT1635B_CMD_BLINK);
  Wire.write(speed);
  Wire.endTransmission();
}

void HT1635B::setCOM(uint8_t option) {
  /**
  * Power-on default is N-MOS
  * 0: N-MOS
  * 1: P-MOS
  */
  Wire.beginTransmission(i2caddr_);
  Wire.write(HT1635B_CMD_COM);
  Wire.write(option);
  Wire.endTransmission();
}

void HT1635B::setOSC(uint8_t mode) {
  /**
  * Power-on default is RC master mode 0 (4)
  * 0-3: Slave mode, use external OSC, OSC pin input, Sync pin input
  * 4 - RC master mode 0, use on chip OSC, OSC pin Hi-Z, Sync pin high
  * 5 - RC master mode 1, use on chip OSC, OSC pin output, Sync pin output
  * 6 - EXT CLK master mode 0, use external OSC, OSC pin input, Sync pin high
  * 7 - EXT CLK master mode 1, use external OSC, OSC pin input, Sync pin output
  */
  Wire.beginTransmission(i2caddr_);
  Wire.write(HT1635B_CMD_OSC);
  Wire.write(mode);
  Wire.endTransmission();
}

void HT1635B::setSystemMode(uint8_t mode) {
  /**
  * Power-on default is System disabled, LED off (0-1)
  * 0-1: System disabled, LED off
  * 2 - System enabled, LED off
  * 3 - System enabled, LED on
  */
  Wire.beginTransmission(i2caddr_);
  Wire.write(HT1635B_CMD_SYSTEM_MODE);
  Wire.write(mode);
  Wire.endTransmission();
}

uint8_t HT1635B::getYByteLocation_(uint8_t y) {
  uint8_t firstBit = 0b10000000;
  uint8_t yBitLocationInByte = y % 8;
  return (firstBit >> yBitLocationInByte);
}
