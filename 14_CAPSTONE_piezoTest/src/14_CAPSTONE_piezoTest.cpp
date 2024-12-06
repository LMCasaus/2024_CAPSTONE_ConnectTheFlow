/* 
 * Project 14_CAPSTONE_piezoTest
 * Author: Lisa Casaus
 * Date: 12.5.24
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "neopixel.h"
#include "Colors.h"
#include "IoTclassroom_CNM.h"

const int PIXELCOUNT = 30;
int bri = 10;
int color; 
SerialLogHandler logHandler(LOG_LEVEL_INFO);
Adafruit_NeoPixel pixel(PIXELCOUNT, SPI1 , WS2812B);

const int analogPiezo = A0;
int i;
int bits;
float volts;
const float measurement =.0008;
float bitsToVolts (int measurement);
int maxValue;
int pixelNum;

SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);

void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected,10000);
  Serial.printf ("the Piezo Sensor is working \n");
  pinMode(analogPiezo, INPUT);

  pixel.begin();
  pixel.setBrightness(bri);
  pixel.show();
  
}
// corrected code from EJ

void loop() {
maxValue = 0;

 for (i = 0; i<100; i++) {
  bits = analogRead (analogPiezo);
  volts = bitsToVolts (bits);
 if (bits>maxValue) {
    maxValue = bits;
  }
 }
pixelNum = ((PIXELCOUNT/4095.0) * maxValue); // AVOIDING DIVIDING AN INT BY AN INT
  
  if (maxValue>100){
    for (i=0; i<pixelNum; i++) {
    pixel.setPixelColor (i,green);
    pixel.show();
    delay (200);
  	}
  	pixel.clear ();
   	pixel.show();
  }
   
}

float bitsToVolts (int measurement) {
float answer;//answer is the variable
answer = (3.3 /4095) * measurement;//volts is .0008 * bits
return answer;

}
