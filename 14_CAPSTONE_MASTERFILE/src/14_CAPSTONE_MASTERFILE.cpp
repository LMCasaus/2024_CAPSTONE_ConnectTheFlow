/* 
 * Project 14_CAPSTONE-MasterFile
 * Author: Lisa Casaus
 * Date: 12.11.24
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 * 
 *TO DO LIST :

A. Publish MQTT
B. Relay
B Motion Sensor
C.OLED
D.Neopixels
E.Stepper Motor

//NOTES:
Components are added but not sufficiently integrated. The code does not compile as of 12.12.24

Flashing became impossible. Possibly an update.
Decided to cut losses and focus on presentation.
If statments will be neccessary to carry out the desired order of operations. 

 */

// Include Particle Device OS APIs
#include "Particle.h"
#include <Adafruit_MQTT.h>
#include "Adafruit_MQTT/Adafruit_MQTT_SPARK.h"
#include "Adafruit_MQTT/Adafruit_MQTT.h"
#include "credentials.h"
#include "Grove-Ultrasonic-Ranger.h" //#include "Ultrasonic.h" is for Arduino //Grove-Ultrasonic-Ranger is the one to look for 
#include "Particle.h"
#include "neopixel.h"
#include "IoTclassroom_CNM.h"
#include "Colors.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Stepper.h"




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
Ultrasonic ultrasonic(D15)                    ;
const int RELAY_PIN = D16;
long RangeInInches;
long RangeInCentimeters;
//================================================================================//
//================================================================================//


//NEOPIXELS
const int PIXELCOUNT = 60; //total number of neopixelsconsy
const int OFFSET = 16;
const int stepperTrigger = 58;
int bri = 16;
int color; 
int start;
int end;

//PIEZO
const int analogPiezo = A0;
int bits;
float volts;
const float measurement =.0008;
float bitsToVolts (int measurement);
int maxValue;
int pixelNum;

void pixelFill( int startPixel , int endPixel  , int color );
int i; 
int j_up; //ascending
int k_down; //descending

Adafruit_NeoPixel pixel(PIXELCOUNT, SPI1 , WS2812B); //decl object


//OLED
const int OLED_RESET =-1;
Adafruit_SSD1306 display (OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


//STEPPER
Stepper myStepper (2048,D4, D6, D5, D7);
int speed = 3;
int steps;



/************Declare Functions*************/
void MQTT_connect();
bool MQTT_ping();

SYSTEM_MODE(SEMI_AUTOMATIC);

void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected,10000);

    Serial.printf ("the Piezo Sensor is working \n");
  pinMode(analogPiezo, INPUT);

//NEOPIXELS
  pixel.begin();
  pixel.setBrightness(bri);//value is 0-255
  pixel.show();

  // Connect to Internet but not Particle Cloud
  WiFi.on();
  WiFi.connect();
  while(WiFi.connecting()) {
    Serial.printf(".");
  }
  Serial.printf("\n\n");

     //OLED
//initialize the screen, hexnumber 0x3C is 60 in decimal
  display.begin(SSD1306_SWITCHCAPVCC,0x3C); 
  display.setTextSize (1);
  display.setTextColor (WHITE);
  display.setCursor(0,0);
  display.printf("Hello, Its Hot. Please give me some water!\n");
  delay (2000);
  display.display(); 
  display.clearDisplay();

  //MOTOR
  myStepper.setSpeed(speed);///speed is an integer specifying RPm 


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
  
  if (RangeInCentimeters == 1) {
   digitalWrite(RELAY_PIN,HIGH);
   // digitalWrite(RELAY_LED,HIGH);
   incrementCounter = TRUE;
  
  }  
  else {
    digitalWrite(RELAY_PIN,LOW);
   // digitalWrite(RELAY_LED,LOW);
   incrementCounter = FALSE; // we will make this false  i the next if statement
  }
 // Each time the relay is triggered. turn the relay on and set the bool incrementCounter to TRUE, save the value in EEPROM, and publish.
  if(incrementCounter) {
        waterCounter++;
        waterCountFeed.publish(waterCounter);
        EEPROM.write(promAddress, waterCounter);// store the data for later if unplugged or diconnected from the internet
        Serial.printf("New response number #  %i\n", waterCounter);
        incrementCounter = FALSE;// set the increment counter false - no need o keep counting- we want incidents onnly when relay is triggered
  }

void loop() {
//NEOPIXEL

//WATER START
pixelFill (0, 0, white);

//WATER FLOW
pixelFill (1, 10,  teal);

//Auto -- Ideally, this will turn on when a person is within 20 cm using the Motion Sensor
pixelFill (11, 11, white);

pixelFill (12, 20,  teal);

pixelFill (21, 21, white);

pixelFill (22, 27,  teal);

pixelFill (28,28, white);

//PRESS ME IF

pixelFill (35, 35, white);

pixelFill (41, 41, white);

pixelFill (59, 59, white);

//PIEZO GBP
maxValue = 0;
//this loop is finding the max value
 for (i = 0; i<100; i++) {
  bits = analogRead (analogPiezo);
  volts = bitsToVolts (bits);
 if (bits>maxValue) {
    maxValue = bits;
  }
 }
pixelNum = ((PIXELCOUNT/4095.0) * maxValue); // AVOIDING DIVIDING AN INT BY AN INT - thank you EJ
  //this loop is lighting the pixels
  if (maxValue>1000){
    for (i=12; i<pixelNum; i++) {
    pixel.setPixelColor (i,turquoise);
    pixel.show();
    delay (200);
  	}

   	pixel.show();
    pixel.clear ();


//INITIALIZE STEPPER
if (stepperTrigger >= 58) {
  display.setTextSize (1);
  display.setCursor(0,0);
  display.printf("Success! Please wait for your prize.\n");
  display.display(); 
  display.clearDisplay();

  myStepper.step(-3000);//steps is a signed integer indicating how many steps to move
  delay (50);//myStepper.step(-1000);
  }

else {
  display.setTextSize (1);
  display.setCursor(0,0);
  display.printf("Sorry, please try again.\n");
  display.display(); 
  display.clearDisplay();
//was not sure about how to stop the motor and how to calculate the time needed for the item to drop.
  myStepper.step ();//steps is a signed integer indicating how many steps to move
}


// //PRESS ME IF
pixelFill( 59, 59, white);
pixel.show();
delay (5000);
//PRESS ME
if (digitalWrite(RELAY_PIN,HIGH)) {

  display.setTextSize (1);
  display.setCursor(0,0);
  display.printf("Thank you for the water. Please press over THERE to fill the lights\n");
  display.display(); 
  display.clearDisplay();
}
}

//void --- isthe definition of a function 
void pixelFill( int startPixel , int endPixel  , int color ){ // this it the template for the function, it being called -- declared int he header
    for(int i=startPixel; i<=endPixel; i++){ 
      pixel.setPixelColor (i,color);
      }
  //pixel.show();
}

float bitsToVolts (int measurement) {
  float answer;//answer is the variable
  answer = (3.3 /4095) * measurement;//volts is .0008 * bits
  return answer;
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
}