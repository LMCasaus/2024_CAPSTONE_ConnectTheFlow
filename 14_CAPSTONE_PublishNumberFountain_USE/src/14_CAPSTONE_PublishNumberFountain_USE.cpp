/* 
 * Project 14_CAPSTONE_PublishNumberFountain
 * Author: Lisa Casaus
 * Date: 12.11.24
 * For comprehensive documentation and examples, please visit:
 * 
 * //EJ  Provided Code 
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

#include "Particle.h"
#include <Adafruit_MQTT.h>
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h"
#include "Adafruit_MQTT/Adafruit_MQTT.h"
#include "credentials.h"
#include "Grove-Ultrasonic-Ranger.h" //#include "Ultrasonic.h" is for Arduino //Grove-Ultrasonic-Ranger is the one to look for 

/************ Do NOT CHANGE***   ***************/ 
TCPClient TheClient; 

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details. 
Adafruit_MQTT_SPARK mqtt(&TheClient,AIO_SERVER,AIO_SERVERPORT,AIO_USERNAME,AIO_KEY); 

// FEEDS ==================ADD YOUR FEED HERE======================//
// Setup Feeds to publish or subscribe 
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname> 
Adafruit_MQTT_Publish waterCountFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/capstonewatercount"); 


/************Declare Variables*************/

const int promAddress = 0x01; //Address in EEPROM that will store the water count value even when the device is power cycled.
int waterCounter; //counts the number of human interctions with the fountain. the trigger of the realy sends data to the feed.
bool incrementCounter;
// ============================ TRIGGER PUBLISH -- RELAY HEADER ====================//
//================================================================================//
Ultrasonic ultrasonic(D7);
const int RELAY_PIN = D16;
long RangeInInches;
long RangeInCentimeters;
//================================================================================//
//================================================================================//

/************Declare Functions*************/
void MQTT_connect();
bool MQTT_ping();

SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected,10000);

  // Connect to Internet but not Particle Cloud
  WiFi.on();
  WiFi.connect();
  while(WiFi.connecting()) {
    Serial.printf(".");
  }
  Serial.printf("\n\n");

 


// ============================ TRIGGER PUBLISH -- RELAY SETUP ====================//
 pinMode(RELAY_PIN, OUTPUT);
waterCounter = EEPROM.read(promAddress);// EEPROM is important as a way to store the data even when unplugged -- it can be published after the fact
Serial.printf("New response number #  %i\n", waterCounter);
delay(2000);

}

void loop() {

  MQTT_connect();
  MQTT_ping();
// Part of your code that reads the ultrasonic and triggers the relay. 
  

//===========The RELAYPIN triggers the publishing of data to the feed. Number of visitors and interactions
//is used to gather data on high traffic areas that can be capitalized on
    

// ============================ TRIGGER PUBLISH -- RELAY LOOP ====================//
// ============================ TRIGGER PUBLISH -- RELAY LOOP ====================//
 RangeInCentimeters = ultrasonic.MeasureInCentimeters(); // two measurements should keep an interval
  Serial.printf ("cm %i\n",RangeInCentimeters);//0~400cm
  
  if (RangeInCentimeters <= 1) {
   digitalWrite(RELAY_PIN,HIGH);
   // digitalWrite(RELAY_LED,HIGH);
   incrementCounter = TRUE;
  
  }  
  else {
    digitalWrite(RELAY_PIN,LOW);
   // digitalWrite(RELAY_LED,LOW);
   //incrementCounter = FALSE; // we will make this false  i the next if statement
  }
 // Each time the relay is triggered. turn the relay on and set the bool incrementCounter to TRUE, save the value in EEPROM, and publish.
  if(incrementCounter) {
        waterCounter++;
        waterCountFeed.publish(waterCounter);
        EEPROM.write(promAddress, waterCounter);// store the data for later if unplugged or diconnected from the internet
        Serial.printf("New response number #  %i\n", waterCounter);
        incrementCounter = FALSE;// set the increment counter false - no need o keep counting- we want incidents onnly when relay is triggered
  }
}


// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;
 
  // Return if already connected.
  if (mqtt.connected()) {
    return;
  }
 
  Serial.print("Connecting to MQTT... ");
 
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.printf("Error Code %s\n",mqtt.connectErrorString(ret));
       Serial.printf("Retrying MQTT connection in 5 seconds...\n");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds and try again
  }
  Serial.printf("MQTT Connected!\n");
}

bool MQTT_ping() {
  static unsigned int last;
  bool pingStatus;

  if ((millis()-last)>120000) {
      Serial.printf("Pinging MQTT \n");
      pingStatus = mqtt.ping();
      if(!pingStatus) {
        Serial.printf("Disconnecting \n");
        mqtt.disconnect();
      }
      last = millis();
  }
  return pingStatus;
}









