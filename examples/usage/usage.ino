/* Example usage for HT1635B library by Abdulrahman Saleh Khamis.
 * Demonstrates sparkle effect on a 41 row x 8 column LED matrix display.
 *
 */

#include "HT1635B.h"
#include <string>

#define ROWS  41
#define COLS  7

int  offset = ROWS;
int counter = 0;
String mystring;

// Initialize objects from the lib
HT1635B LEDmatrix;

SYSTEM_THREAD(ENABLED);

void setup() {
  Serial.begin(115200);
  LEDmatrix.begin();
  LEDmatrix.setBrightness(3);
}

void loop() {
  fullLEDsBlinking();
}

/*void scrollText() {
  char charBuffer[] = {"12345678"};
  LEDmatrix.clear();
  LEDmatrix.drawText(charBuffer, sizeof(charBuffer), offset, 0);
  LEDmatrix.render();
  delay(50);
  offset--;
  if (offset == -1) {
    delay(1000);
    offset = ROWS;
  }
}*/

void sparkles() {
  LEDmatrix.setPixel(random(41), random(7));
  LEDmatrix.clearPixel(random(41), random(7));
  LEDmatrix.render();
}

/*void connectedCounter() {
  if (!Particle.connected()) {
    if (mystring.length() >= 3) {
      mystring = "";
    } else {
      mystring.concat(".");
    }
  } else {
    counter++;
    mystring = String(counter);
  }
  LEDmatrix.clear();
  LEDmatrix.drawText(mystring.c_str(), mystring.length()+1, 1, 0);
  LEDmatrix.render();
  delay(200);
}*/

void allLEDs(boolean operation) {
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      if (operation == TRUE) {
        LEDmatrix.setPixel(i, j);
      } else {
        LEDmatrix.clearPixel(i, j);
      }
    }
  }
}

void fullLEDsBlinking() {
  allLEDs(HIGH);
  LEDmatrix.render();
  delay(500);
  allLEDs(LOW);
  LEDmatrix.render();
  delay(500);
}
