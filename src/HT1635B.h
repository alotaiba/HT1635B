#pragma once

/* HT1635B library by Abdulrahman Saleh Khamis
*
* This library allows for easy interfacing with HT1635B LED driver chip
* using I2C protocol. It is a low level library where you can control
* individual LED pixels on 44 rows x 8 commons display with a single
* chip.
*
* This chip has an internal PWM controller to control the brightness of LEDs.
*/

// This will load the definition for common Particle variable types
#include "Particle.h"

#define HT1635B_I2C_ADDRESS       0x68
#define HT1632B_CMD_RAM_W         0b10000000
#define HT1635B_CMD_BLINK         0b10000100
#define HT1635B_CMD_COM           0b10001000
#define HT1635B_CMD_OSC           0b10100000
#define HT1635B_CMD_SYSTEM_MODE   0b10000010
#define HT1635B_CMD_BRIGHTNESS    0b11000000

#define HT1635B_ROW_SIZE    43

class HT1635B
{
  public:
    /**
     * Constructor
     * Creates a new HT1635B class to manage a single HT1635B chip.
     */
    HT1635B();

    void begin(uint8_t i2caddr = HT1635B_I2C_ADDRESS);
    void setRowMemory(uint8_t index, uint8_t data);
    void clearRowMemory(uint8_t index, uint8_t data);
    void setPixel(int x, int y);
    void clearPixel(int x, int y);
    void clear();
    void render();

    void setBrightness(uint8_t brightness);
    void setBlinking(uint8_t speed);
    void setCOM(uint8_t option);
    void setOSC(uint8_t mode);
    void setSystemMode(uint8_t mode);

  private:
    uint8_t i2caddr_; // I2C address of the device
    uint8_t row_[HT1635B_ROW_SIZE]; // row memory buffer
    uint8_t getYByteLocation_(uint8_t y);
};
