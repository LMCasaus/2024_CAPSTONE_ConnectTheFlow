/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 * 
 *  CODE SOURCE
 * https://www.bing.com/search?q=example+code+for+millis+timer+cpp+photon2+example&qs=n&form=QBRE&sp=-1&ghc=2&lq=0&pq=example+code+for+millis+timer+cpp+photon2+example&sc=8-49&sk=&cvid=3612AA8371B44EBA81147F4E502BDD65&ghsh=0&ghacc=0&ghpl=
 */

// Include Particle Device OS APIs
#include "Particle.h"
// Define the LED pin
const int ledPin = D7;

// Variables to store the current and previous time
unsigned long previousMillis = 0;
const long interval = 500; // Interval at which to blink (milliseconds)

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
Serial.begin(9600);
 waitFor (Serial.isConnected,10000);

    // Set the LED pin as an output
    pinMode(ledPin, OUTPUT);
}

void loop() {
    // Get the current time
    unsigned long currentMillis = millis();

    // Check if the interval has passed
    if (currentMillis - previousMillis >= interval) {
      Serial.printf("Current time is \n");
        // Save the last time the LED was toggled
        previousMillis = currentMillis;

        // Toggle the LED
        digitalWrite(ledPin, !digitalRead(ledPin));
    }
}