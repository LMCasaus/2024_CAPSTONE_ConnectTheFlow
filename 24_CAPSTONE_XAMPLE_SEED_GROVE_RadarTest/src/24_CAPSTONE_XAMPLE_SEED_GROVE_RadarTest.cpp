/* 
 * Project myProject
 * Author: Your Name
 * Date: 
 * For comprehensive documentation and examples, please visit:
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 * 
 * CODE SOURCE
 * https://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger/
 * library
 * Grove-Ultrasonic-Ranger 1.0.2 34679 Particle Xenon library for controlling Grove Ultrasonic Ranger, using gennal I/O communication.
 */
#include "Ultrasonic.h" //Grove-Ultrasonic-Ranger 2.0
#include "WS2812_Definitions.h"

#define PIN            3
#define NUMPIXELS      19
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#define lightness  50
// Defines the interval between LEDs lighting up
#define inter_val     4
Ultrasonic ultrasonic(D7);

// Define the LED color
byte r = 80;
byte g = 200;
byte b = 255;
volatile long RangeInCentimeters = 0;
int BassTab[]={956,851,758,716,637,568,501,956,851};//bass 1~7
// Used to define the distance represented by the 18 LEDs we will use
uint16_t  distance[18] = {inter_val*1,inter_val*2,inter_val*3,inter_val*4,inter_val*5,inter_val*6,
                            inter_val*7,inter_val*8,inter_val*9,inter_val*10,inter_val*11,inter_val*12,
                            inter_val*13,inter_val*14,inter_val*15,inter_val*16,inter_val*17,inter_val*18};

void setup()
{
  // Enables the LED strip
    pixels.begin();
    pixels.show();
    pinMode(3, OUTPUT);
}

SYSTEM_MODE(SEMI_AUTOMATIC);
void loop()
{
    // Read in the value from the Ultrasonic Ranger
    RangeInCentimeters = get_ultrasonic_distance();
    // The logic for the if statements below follows as thus:
    //    if (Distance Read > X) and (Distance Read is < Y){
    //        turn on (N) LEDs;
    //        while (Distance Read > X) and (Distance Read < Y)
    //            Read distance again
    //    else(...)
    if ((RangeInCentimeters>0)&&(RangeInCentimeters<3)){
        action_rgbled_on (0);
        while((RangeInCentimeters>distance[0])&&(RangeInCentimeters<=distance[1]))
            RangeInCentimeters = get_ultrasonic_distance();
    }else
    if ((RangeInCentimeters>distance[0])&&(RangeInCentimeters<=distance[1])){
        action_rgbled_on (2);
        while((RangeInCentimeters>distance[0])&&(RangeInCentimeters<=distance[1]))
            RangeInCentimeters = get_ultrasonic_distance();
    }else
    if ((RangeInCentimeters>distance[1])&&(RangeInCentimeters<=distance[2])){
        action_rgbled_on (4);
        while((RangeInCentimeters>distance[1])&&(RangeInCentimeters<=distance[2]))
            RangeInCentimeters = get_ultrasonic_distance();
    }else
    if ((RangeInCentimeters>distance[2])&&(RangeInCentimeters<=distance[3])){
        action_rgbled_on (6);
        while((RangeInCentimeters>distance[2])&&(RangeInCentimeters<=distance[3]))
            RangeInCentimeters = get_ultrasonic_distance();
    }else
    if ((RangeInCentimeters>distance[3])&&(RangeInCentimeters<=distance[4])){
        action_rgbled_on (8);
        while((RangeInCentimeters>distance[3])&&(RangeInCentimeters<=distance[4]))
            RangeInCentimeters = get_ultrasonic_distance();
    }else      
    if ((RangeInCentimeters>distance[4])&&(RangeInCentimeters<=distance[5])){
        action_rgbled_on (10);
        while((RangeInCentimeters>distance[4])&&(RangeInCentimeters<=distance[5]))
            RangeInCentimeters = get_ultrasonic_distance();
    }else               
    if ((RangeInCentimeters>distance[5])&&(RangeInCentimeters<=distance[6])){
        action_rgbled_on (12);
        while((RangeInCentimeters>distance[5])&&(RangeInCentimeters<=distance[6]))
            RangeInCentimeters = get_ultrasonic_distance();
    }else         
    if ((RangeInCentimeters>distance[6])&&(RangeInCentimeters<=distance[7])){
        action_rgbled_on (14);
        while((RangeInCentimeters>distance[6])&&(RangeInCentimeters<=distance[7]))
            RangeInCentimeters = get_ultrasonic_distance();
    }else
    if ((RangeInCentimeters>distance[7])&&(RangeInCentimeters<=distance[8])){
        action_rgbled_on (16);
        while((RangeInCentimeters>distance[7])&&(RangeInCentimeters<=distance[8]))
            RangeInCentimeters = get_ultrasonic_distance();
    }else      
    if ((RangeInCentimeters>distance[8])&&(RangeInCentimeters<=distance[9])){
        action_rgbled_on (18);
        while((RangeInCentimeters>distance[8])&&(RangeInCentimeters<=distance[9]))
            RangeInCentimeters = get_ultrasonic_distance();
    }
    // If we execute this code we will be at the maximum display distance of the LEDs, so turn them all off.
    else 
    {
        for(int i=0;i < 18; i++) 
        {
            // Set LEDs off
            pixels.setPixelColor(i,0,0,0);
        }
        pixels.show();
        delay(1);
    }

}

// This fuction reads the distance from the Grove Ultrasonic Ranger and returns the value.
// This fuction can only return a number > 0.
long get_ultrasonic_distance()
{
    long RangeInCentimeters = 0;
    RangeInCentimeters = ultrasonic.MeasureInCentimeters();
    // Asks for a positive number to be returned
    if (RangeInCentimeters > 0)
    {
      return RangeInCentimeters;
    }
    else return 0;
}

// This function turns on the specified LED and sets the LED RGB value.
void action_rgbled_on (int led_num)
{       // Sets LED colors from LED 0 to len_num
        for(int i=0;i < led_num; i++) {
          pixels.setPixelColor(i,r,g,b);
        }
        // Turn on the LEDs / Update their color
        pixels.show();
        delay(10);
}

