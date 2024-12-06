/* 
 * Project EXAMPLE
 * Author: DC Bapon
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 * 
 * CODE SOURCE
 * https://youtu.be/uJ9r2lP-ARA?si=guoCo8qzyW_9UWPw
 */

// Include Particle Device OS APIs
#include "Particle.h"
//#include "Ultrasonic.h " //Grove-Ultrasonic-Ranger

#define trigger 5
#define echo 4
#define Relay 6

float time=0,distance=0;
 

// Let Device OS manage the connection to the Particle Cloud
SYSTEM_MODE(SEMI_AUTOMATIC);


void setup()
{
Serial.begin(9600);

 pinMode(trigger,OUTPUT);
 pinMode(echo,INPUT);
 pinMode(Relay,OUTPUT);

 delay(2000);
}

void loop()
{
 measure_distance();

 if(distance<5)
 {
   digitalWrite(Relay,HIGH);
 }
 else
 {
   digitalWrite(Relay,LOW);
 }

 delay(500);
}

void measure_distance()
{
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 digitalWrite(trigger,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 time=pulseIn(echo,HIGH);
 
 distance=time*200/20000;
}
