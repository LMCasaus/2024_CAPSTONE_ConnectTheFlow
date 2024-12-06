/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 * 
 * CODE  fromvarious places: 
 * https://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "Grove-Ultrasonic-Ranger.h"//#include "Ultrasonic.h" is for Arduino //Grove-Ultrasonic-Ranger is the one to look for 


Ultrasonic ultrasonic(D7);
const int RELAY_LED = D2;
const int RELAY_PIN = D16;


long RangeInInches;
long RangeInCentimeters;

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(SEMI_AUTOMATIC);


void setup() {
// Put initialization like pinMode and begin functions here
 Serial.begin(9600);
 waitFor (Serial.isConnected,10000);

//RELAY
 pinMode(RELAY_LED, OUTPUT);
 pinMode(RELAY_PIN, OUTPUT);

}
void loop() {
  RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
  Serial.printf ("cm %i\n",RangeInCentimeters);//0~400cm
  
  if (RangeInCentimeters <= 1) {
   digitalWrite(RELAY_PIN,HIGH);
   // digitalWrite(RELAY_LED,HIGH);
  
  }  
  else {
    digitalWrite(RELAY_PIN,LOW);
   // digitalWrite(RELAY_LED,LOW);
  }


  /////////////////////EXAMPLE CODE///////////////
  
  // Serial.printf("Distance = ");
  // RangeInInches = ultrasonic.MeasureInInches();
  // Serial.print(RangeInInches);//0~157 inches
  // Serial.printf(" inch");
  // delay(250);

  //  RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
  //  Serial.print(RangeInCentimeters);//0~400cm
  //  Serial.println(" cm");
  //  delay(250);
  }
