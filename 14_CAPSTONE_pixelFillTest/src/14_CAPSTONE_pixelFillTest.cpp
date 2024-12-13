/* 
 * Project 14_CAPSTONE_pixelFillTest
 * Author: LisaCasaus
 * Date: 12.5.24
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "neopixel.h"
#include "Colors.h"

#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#include "Stepper.h"

//STEPPER
Stepper myStepper (2048,D4, D6, D5, D7);
int speed = 3;
int steps;


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



const int PIXELCOUNT = 60; //total number of neopixelsconsy
const int OFFSET = 16;
const int stepperTrigger = 58;


//NEOPIXELS
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

  
}

void loop() {


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

//PRESS ME

display.setTextSize (1);
display.setCursor(0,0);
display.printf("Thank you for the water. Please press over THERE to fill the lights\n");
display.display(); 
display.clearDisplay();


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
  //myStepper.step ();//steps is a signed integer indicating how many steps to move
}



  }

// //PRESS ME
pixelFill( 59, 59, white);
pixel.show();
delay (5000);

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

