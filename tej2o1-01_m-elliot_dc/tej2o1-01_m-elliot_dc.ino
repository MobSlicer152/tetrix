// Data: 2023-06-06
// Course: TEJ2O1-01
// Name Elliot McNeil
// Description:
//     This program randomly spins a DC motor and activates the red, green, or
//     yellow LED depending on the direction.

#include "src/tej2o1-01_m-elliot_utility.h"

// Which motor to rotate
constexpr int MOTOR = 2;

// Initializes the program
void setup()
{
    // Initialize my library
    Util::Initialize();
}

// Randomly rotate the motor every second
void loop()
{
    int rotation = random(-100, 100);
    Util::ResetLeds();
    if (rotation == 0)
    {
        pulse.setGreenLED(HIGH);
    }
    else if (rotation < 0)
    {
        pulse.setRedLED(HIGH);
    }
    else if (rotation > 0)
    {
        pulse.setYellowLED(HIGH);
    }
    pulse.setMotorPower(MOTOR, rotation);
    delay(1000);
}
