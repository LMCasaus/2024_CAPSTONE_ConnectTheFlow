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

const int PIXELCOUNT = 30; //total number of neopixelsconsy
const int OFFSET = 16;


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

//PIXEL ANIMATIONS
// int segment;
// int waterStart;
// int waterFlow ;
// int pressMe;
// int dropMe;


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
  
}

void loop() {


//WATER START
pixelFill (0, 0, white);

//WATER FLOW
pixelFill (1, 10,  teal);

//PRESS ME
pixelFill (11, 11, white);

//PIEZO GB
maxValue = 0;
//this loop is finding the max value
 for (i = 0; i<100; i++) {
  bits = analogRead (analogPiezo);
  volts = bitsToVolts (bits);
 if (bits>maxValue) {
    maxValue = bits;
  }
 }
pixelNum = ((PIXELCOUNT/4095.0) * maxValue); // AVOIDING DIVIDING AN INT BY AN INT
  //this loop is lighting the pixels
  if (maxValue>1000){
    for (i=12; i<pixelNum; i++) {
    pixel.setPixelColor (i,turquoise);
    pixel.show();
    delay (200);
  	}

   	pixel.show();
    pixel.clear ();
  }

//PRESS ME
pixelFill( 29, 29, white);
pixel.show();
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


// void pixelFill( int startPixel , int endPixel  , int color ){
  
//   for(int iUp=startPixel; iUp<=endPixel; iUp++){
//     pixel.setPixelColor (iUp,color);
//     }
// pixel.show();
//  }


//LOOP
 //down
      // for (k_down =10; k_down >1; k_down--){
      //   pixel.setPixelColor(k_down, blue);
      //   pixel.show();
      //   delay(50);
      //   pixel.clear();//pixel.clear(); where you show you clear has an effect on when or where your pixels light up
      //   pixel.show();//pixel.show();
       // }