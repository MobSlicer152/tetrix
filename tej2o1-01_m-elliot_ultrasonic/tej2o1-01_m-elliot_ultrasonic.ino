// Date: 2023-06-07
// Course: TEJ2O1-01
// Name: Elliot McNeil
// Description:
//     Blinks the green LED faster until within 5 cm, then outputs
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
    // Print the message if necessary
    if (distance < 5)
    {
        Morse::Print(L"Близлежащий объект+");
        delay(1000);
    }
    else if (distance < 50)
    {
        // Delay for longer the farther away
        pulse.setGreenLED(HIGH);
        delay(distance * 25);
        pulse.setGreenLED(LOW);
        delay(distance * 25);
    }
}
