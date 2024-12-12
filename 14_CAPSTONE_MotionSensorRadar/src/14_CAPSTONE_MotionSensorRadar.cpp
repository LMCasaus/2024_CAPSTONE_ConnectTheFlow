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
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"
#include "neopixel.h"
#include "Colors.h"
#include "IoTclassroom_CNM.h"


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

//timer
int currentTime;
int lastTime;

//\NEOPIXEL - PIEZO
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


//ULTRASONIC MOTION SENSOR
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
 

 //NEOPIXEL
 Serial.printf ("the Piezo Sensor is working \n");
  pinMode(analogPiezo, INPUT);
  pixel.begin();
  pixel.setBrightness(bri);
  pixel.show();

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

//RELAY
 pinMode(RELAY_LED, OUTPUT);
 pinMode(RELAY_PIN, OUTPUT);

}
void loop() {


//OLED - GET WATER
  display.setTextSize (2);
  display.setCursor(0,0);
  display.printf("Hello!\n");
  display.printf("I'm Thirsty!\n");////Go find CHAR for the apostrophe
  display.printf("Can you give me some water ?\n"); ///go find character for ?
  display.display(); 
  display.clearDisplay();
  

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

  //OLED - GET PIXEL
  display.setTextSize (2);
  display.setCursor(0,0);
  display.printf("THANK YOU!\n");
  display.printf("Water goes in the cup.\n");
  display.printf ("ATTENTION\n");
  display.printf("You have become the unwitting accomplice to a Bee Bath\n");////Go find CHAR for the apostrophe
  display.printf("Hu, hu, hu, hu\n");
  display.printf(" Light up all the pixels to complete your mission\n");
  display.display(); 
  display.clearDisplay();


  //OLED - GET PIXEL




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

  
