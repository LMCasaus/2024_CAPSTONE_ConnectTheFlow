/* 
 * Project 24_CAPSTONE_RelayPump
 * Author: Lisa Casaus
 * Date: 12.3.24
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"

// RELAY
const int RELAYPIN = D16;



// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(SEMI_AUTOMATIC);



void setup() {
Serial.begin (9500);
waitFor(Serial.isConnected,10000);

pinMode(RELAYPIN, OUTPUT);
}


void loop() {


/* //Chaeck if RELAY is working
digitalWrite (RELAYPIN,HIGH);
delay (10000);
digitalWrite(RELAYPIN,LOW);
delay (10000);
*/

}
