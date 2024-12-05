/* 
 * Project CAPSTONE_OLED
 * Author: Lisa Casaus
 * Date: 12.4.24
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

// Include Particle Device OS APIs
#include "Particle.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_BME280.h"

//#include "GOfi2coLED.h"

//BITMAP
#include "sketchityBitmap.h"
#include "sketchityLines.h"


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

//BME
Adafruit_BME280 bme; //Adafruit_BME280 Read (bme);when i do not include the 'read' it does not turn green...why?
int hexAddress  = 0x76; //0x76 hex
const char degree = 0xF8;
float tempC;
int celcius;
float fahrenheit;
float celciusToFahrenheit (int celcius);
bool Status;

//timer
int currentTime;
int lastTime;

// BITMAP

SYSTEM_MODE(SEMI_AUTOMATIC);


void setup() {
  Serial.begin(9600);
  waitFor(Serial.isConnected,10000);
 
 //OLED
//initialize the screen, hexnumber 0x3C is 60 in decimal
  display.begin(SSD1306_SWITCHCAPVCC,0x3C); 
  display.setTextSize (1);
  display.setTextColor (WHITE);
  display.setCursor(0,0);
  display.printf("Hello, World!\n");
  delay (2000);
  display.display(); 
  display.clearDisplay();


//BME
  Status = bme.begin (0x76);


}

 
void loop() {

  // currentTime = millis();
  // tempC = bme.readTemperature(); //celcius
  // fahrenheit = tempC * (9.0/5.0)+32;
  // display.setCursor(0,0);
  // display.printf("Temperature(Fahrenheit)= %0.1f\n",tempC);
  // Serial.printf("Temperature(Fahrenheit)= %0.1f\n",tempC);
  // display.display();


  // miniature bitmap display
  // display.clearDisplay();
  // display.drawBitmap(0, 0, sketchityLines, 128, 64, 1);
  // display.display();

  display.setTextSize (2);
  display.setCursor(0,0);
  display.printf("Yes\n");
  display.display(); 


   
}
