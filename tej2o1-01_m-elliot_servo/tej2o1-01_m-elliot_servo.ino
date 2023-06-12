// Date: 2023-06-05
// Course: TEJ2O1-01
// Name: Elliot McNeil
// Description:
//     Rotates the servo motor back and forth a random amount, moving the DC motor
//     in the opposite direction, and showing which way they're rotating with the
//     LEDs

#include "src/tej2o1-01_m-elliot_utility.h"

// Make sure PULSE is in use
#ifndef USE_PULSE
#error This code requires PULSE
#endif

// Which motors to rotate
constexpr int MOTOR = 2;
constexpr int SERVO = 1;

// Initializes the program
void setup()
{
    // Initialize my library
    Util::Initialize();
}

// Randomly rotates the motors every second
void loop()
{
    int rotation = random(-100, 100);
    int rotationSign = 0;
    Util::ResetLeds();
    if (rotation == 0)
    {
        pulse.setGreenLED(HIGH);
    }
    else if (rotation < 0)
    {
        rotationSign = -1;
        pulse.setRedLED(HIGH);
    }
    else if (rotation > 0)
    {
        rotationSign = 1;
        pulse.setYellowLED(HIGH);
    }
    pulse.setMotorPower(MOTOR, rotation);

    // Move the servo in the opposite direction to the DC at the same speed
    pulse.setServoSpeed(SERVO, abs(rotation));
    pulse.setServoPosition(SERVO, (rotationSign * 180) * -1);

    delay(1000);
    pulse.setMotorPower(MOTOR, 0);
    delay(1000);
}
