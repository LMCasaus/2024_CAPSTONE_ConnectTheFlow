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

const int CALFACTOR = 1000;
const int SAMPLES=10;
float weight, rawData, calibration;
int offset;
int grams;

//TIMER
int currentTime; 
int lastTime;
 
IoTTimer pumpWaitTimer;
IoTTimer pumpTimer;




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
  myScale.tare(0); // set the tare weight or leave at zero
  myScale.set_scale(CALFACTOR);

}


void loop() {
//currentTime = millis();

//LOADCELL 
  weight = myScale.get_units(SAMPLES);
  offset = myScale.get_offset();//returns the offset by tare();
  Serial.printf ("The weight is %f \n", weight);
  delay(5000);

// if (weight >= 200) {
//   digitalWrite (RELAYPIN,HIGH);
//   Serial.printf ("fill cup \n");
// }
// if  (weight <= 244 ) {
//   digitalWrite (RELAYPIN, LOW);
// }
}

//TIMER
// if (pumpWaitTimer.isTimerReady()) {
//   if (weight >= 244) {
//     weight = myScale.get_units(SAMPLES);
//     Serial.printf ("The weight is %f \n", weight);
//     delay(5000);
//     pumpTimer.startTimer (5000);
//     digitalWrite(RELAYPIN, HIGH);
//   }
//   if(pumpTimer.isTimerReady()) {
//     digitalWrite (RELAYPIN, LOW);
//   }
// }

//if (weight > 244 || weight < 800) {
/* //Chaeck if RELAY is working
digitalWrite (RELAYPIN,HIGH);
delay (10000);
digitalWrite(RELAYPIN,LOW);
delay (10000);
*/


