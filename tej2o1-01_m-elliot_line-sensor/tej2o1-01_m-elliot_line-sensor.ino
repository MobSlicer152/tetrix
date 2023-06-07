// Date: 2023-06-07
// Course: TEJ2O1-01
// Name: Elliot McNeil
// Description:
//     Turns on either the yellow or green LED depending on if a line is
//     detected, and outputs "Объект обнаружен" ("object detected") if one is.

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
    Util::ResetLeds();
    if (pulse.readLineSensonr(LINE_SENSOR))
    {
        pulse.setGreenLED(HIGH);
        Morse::Print(L"Объект обнаружен+");
    }
    else
    {
        pulse.setYellowLED(HIGH);
    }
}
