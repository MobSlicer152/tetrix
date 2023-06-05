#include <Arduino.h>
#line 1 "C:\\Users\\bramb\\source\\repos\\tetrix\\tej2o1-01_m-elliot_servo\\tej2o1-01_m-elliot_servo.ino"
// Date: 2023-06-05
// Course: TEJ2O1-01
// Name: Elliot McNeil
// Description: Rotates a servo motor back and forth a random amount

#include "src/tej2o1-01_m-elliot_utility.h"

// Make sure PULSE is in use
#ifndef USE_PULSE
#error This code requires PULSE
#endif

// Initializes the program
#line 14 "C:\\Users\\bramb\\source\\repos\\tetrix\\tej2o1-01_m-elliot_servo\\tej2o1-01_m-elliot_servo.ino"
void setup();
#line 21 "C:\\Users\\bramb\\source\\repos\\tetrix\\tej2o1-01_m-elliot_servo\\tej2o1-01_m-elliot_servo.ino"
void loop();
#line 14 "C:\\Users\\bramb\\source\\repos\\tetrix\\tej2o1-01_m-elliot_servo\\tej2o1-01_m-elliot_servo.ino"
void setup()
{
    // Initialize my library
    Util::Initialize();
}

// Rotates the motor randomly
void loop()
{
    
}

