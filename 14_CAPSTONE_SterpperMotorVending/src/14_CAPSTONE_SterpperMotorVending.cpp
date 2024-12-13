/* 
 * Projec: 14_CAPSTONE-StepperMotorVending
 * Author: Lisa Casaus
 * Date: 12.12.24
 * For comprehensive documentation and examples, please visit:
 * Code from Duck Duck Go
 * https://docs.particle.io/firmware/best-practices/firmware-template/
 */

#include "Particle.h"
#include "Stepper.h"

Stepper myStepper (2048,D4, D6, D5, D7);
int speed = 3;
int steps;



SYSTEM_MODE(SEMI_AUTOMATIC);
SYSTEM_THREAD(ENABLED);


void setup() {
myStepper.setSpeed(speed);///speed is an integer specifying RPm 
}


void loop() {
myStepper.step(-3000);//steps is a signed integer indicating how many steps to move
delay (50);//myStepper.step(-1000);

}
