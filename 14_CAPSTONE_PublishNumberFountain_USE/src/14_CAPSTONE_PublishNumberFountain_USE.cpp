/* 
 * Project 14_CAPSTONE_PublishNumberFountain
 * Author: Lisa Casaus
 * Date: 12.11.24
 * For comprehensive documentation and examples, please visit:
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
Adafruit_MQTT_Subscribe subFeed = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/capstonewatercount"); 


/************Declare Variables*************/
unsigned int last, lastTime;
//float subValue,pubValue;
int subValue,pubValue;
int randNumber;
bool getWaterCount; //counts the number of human interctions with the fountain. the trigger of the realy sends data to the feed
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

  // Setup MQTT subscription
  mqtt.subscribe(&subFeed);

// ============================ TRIGGER PUBLISH -- RELAY SETUP ====================//
 pinMode(RELAY_PIN, OUTPUT);


}

void loop() {

  MQTT_connect();
  MQTT_ping();

  // this is our 'wait for incoming subscription packets' busy subloop 
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(100))) {

//===========The RELAYPIN triggers the publishing of data to the feed. Number of visitors and interactions
//is used to gather data on high traffic areas that can be capitalized on
    if (RELAY_PIN, HIGH) {
    getWaterCount = atoi((char *) subFeed.lastread);
   Serial.printf("New response number #  %2i\n", getWaterCount);
  }

// ============================ TRIGGER PUBLISH -- RELAY LOOP ====================//
// ============================ TRIGGER PUBLISH -- RELAY LOOP ====================//
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
