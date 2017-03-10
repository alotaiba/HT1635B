/* Example usage for HT1635B library by Abdulrahman Saleh Khamis.
 * Demonstrates sparkle effect on a 41 row x 8 column LED matrix display.
 */

#include "HT1635B.h"

#define ROWS  41
#define COLS  7

// Initialize objects from the lib
HT1635B LEDmatrix;

SYSTEM_THREAD(ENABLED);

void setup() {
  LEDmatrix.begin();
  LEDmatrix.setBrightness(3);
  LEDmatrix.setBlinking(2);

  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      LEDmatrix.setPixel(i, j);
    }
  }
  LEDmatrix.render();
}

void loop() {

}
