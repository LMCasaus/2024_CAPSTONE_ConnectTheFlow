/* 
 * Project 14_CAPSTONE_RelayLoadCell
 * Author: Lisa Casaus
 * Date: 12.3.24
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "HX711.h" // must install as hx711a but include as HX711.h
#include "IoTclassroom_CNM.h"
#include "IoTTimer.h"

// RELAY
const int RELAYPIN = D16;

//LOADCELL
HX711 myScale (D6,D7);

const int CALFACTOR = 4;
const int SAMPLES=10;
float weight, rawData, calibration;
int offset;
int grams;

//TIMER
int currentTime; 
int lastTime;
 
Timer pumpWaitTimer;
Timer pumpTimer;




// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(SEMI_AUTOMATIC);


void setup() {
Serial.begin (9600);
waitFor(Serial.isConnected,10000);

//RELAY
pinMode(RELAYPIN, OUTPUT);

//LOADCELL
myScale.set_scale();
  delay (5000);
  myScale.tare();
  myScale.set_scale(CALFACTOR);

}


void loop() {
currentTime = millis();

//LOADCELL TIMER


if (pumpWaitTimer.isTimerReady()) {
  if (weight >= 244) {
    weight = myScale.get_units(SAMPLES);
    Serial.printf ("The weight is %f \n", weight);
    delay(5000);
    pumpTimer.startTimer (5000);
    digitalWrite(RELAYPIN, HIGH);
  }
  if(pumpTimer.isTimerReady()) {
    digitalWrite (RELAYPIN, LOW);
  }
  
}
//if (weight > 244 || weight < 800) {
//if (weight > 244) {
//   digitalWrite (RELAYPIN,HIGH);
// }
// else {
//   digitalWrite (RELAYPIN, LOW);
  
// }


/* //Chaeck if RELAY is working
digitalWrite (RELAYPIN,HIGH);
delay (10000);
digitalWrite(RELAYPIN,LOW);
delay (10000);
*/

}
