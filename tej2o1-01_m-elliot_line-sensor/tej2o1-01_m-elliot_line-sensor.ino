// Date: 2023-06-07
// Course: TEJ2O1-01
// Name: Elliot McNeil
// Description:
//     Turns on either the yellow or green LED depending on if a line is
//     detected

#include "src/tej2o1-01_m-elliot_utility.h"

// Make sure PULSE is in use
#ifndef USE_PULSE
#error This code requires PULSE
#endif

// Line sensor location
constexpr int LINE_SENSOR = 2;

// Initializes the program
void setup()
{
    Util::Initialize();
}

// Detect lines
void loop()
{
    if (pulse.readLineSensor(LINE_SENSOR))
    {
        pulse.setGreenLED(HIGH);
        pulse.setYellowLED(LOW);
    }
    else
    {
        pulse.setGreenLED(LOW);
        pulse.setYellowLED(HIGH);
    }
}
