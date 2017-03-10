/* Example usage for HT1635B library by Abdulrahman Saleh Khamis.
 * Demonstrates full LEDs blinking effect on a 41 row x 8 column
 * LED matrix display.
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
}

void loop() {
  LEDmatrix.setPixel(random(ROWS), random(COLS));
  LEDmatrix.clearPixel(random(ROWS), random(COLS));
  LEDmatrix.render();
}
