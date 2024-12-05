/* 
 * Project CAPSTONE_LoadCell_WaterWeight
 * Author: Lisa Casaus
 * Date: 12.2.24
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "HX711.h" // must install as hx711a but include as HX711.h

HX711 myScale (D6,D7);

const int CALFACTOR = 1000;
const int SAMPLES=10;

float weight, rawData, calibration;
int offset;
int grams;


SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);
SerialLogHandler logHandler(LOG_LEVEL_INFO);


void setup() {
  Serial.begin (9600); // i  had 9500 but it should be 9600
   waitFor(Serial.isConnected,10000);

  myScale.set_scale();
  delay (5000);
  myScale.tare(0); // set the tare weight or leave at zero
  myScale.set_scale(CALFACTOR);
}

void loop() {
  weight = myScale.get_units(SAMPLES);
  offset = myScale.get_offset();//returns the offset by tare();
  delay(5000);
  Serial.printf ("The weight is %f \n", weight);
}

