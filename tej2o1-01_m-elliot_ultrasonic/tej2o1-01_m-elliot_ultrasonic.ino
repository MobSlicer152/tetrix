// Date: 2023-06-07
// Course: TEJ2O1-01
// Name: Elliot McNeil
// Description:
//     Blinks the green LED faster until within 1 cm, then outputs
//     "Близлежащий объект" ("nearby object") in Morse code.

#include "src/tej2o1-01_m-elliot_utility.h"

// Make sure PULSE is in use
#ifndef USE_PULSE
#error This code requires PULSE
#endif

// Ultrasonic sensor location
constexpr int ULTRASONIC_SENSOR = 3;

// Initializes the program
void setup()
{
    Util::Initialize();
}

// Detects objects
void loop()
{
    int distance = pulse.readSonicSensorCM(ULTRASONIC_SENSOR);
    if (distance == 1)
    {
        Morse::Print(L"Близлежащий объект+");
    }

    // Delay for longer the farther away
    pulse.setGreenLED(HIGH);
    delay(distance * 60);
    pulse.setGreenLED(LOW);
}
