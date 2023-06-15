// Date: 2023-06-01
// Course: TEJ2O1-01
// Name: Elliot McNeil
// Description: Robot

#include <stdint.h>

#include <Arduino.h>

#include <PULSE.h>

class Robot
{
  public:
    // Initialize the robot
    Robot(uint8_t leftMotor, uint8_t rightMotor, uint8_t armServo, uint8_t gripperServo, uint8_t lineSensor, uint8_t sonicSensor)
        : m_leftMotor(leftMotor), m_rightMotor(rightMotor), m_armServo(armServo), m_gripperServo(gripperServo), m_lineSensor(lineSensor), m_sonicSensor(sonicSensor)
    {
        m_pulse.PulseBegin();
        Serial.println("Robot initialized");
    }

    // Go straight
    void Drive(uint16_t duration, bool backward)
    {
        Serial.println(String("Drive ") + String(duration) + String("") + backward);
        m_pulse.setMotorPower(m_rightMotor, 100);
        m_pulse.setMotorPower(m_leftMotor, 100);
    }

    // Turn left
    void TurnLeft(uint16_t duration)
    {
        Serial.println(String("Left turn ") + duration);
        m_pulse.setMotorPower(m_rightMotor, 100);
        m_pulse.setMotorPower(m_leftMotor, 10);
        delay(duration);
        m_pulse.setMotorPower(m_rightMotor, 0);
        m_pulse.setMotorPower(m_leftMotor, 0);
    }

    // Turn right
    void TurnRight(uint16_t duration)
    {
        Serial.println(String("Left turn ") + duration);
        m_pulse.setMotorPower(m_rightMotor, 10);
        m_pulse.setMotorPower(m_leftMotor, 100);
        delay(duration);
        m_pulse.setMotorPower(m_rightMotor, 0);
        m_pulse.setMotorPower(m_leftMotor, 0);
    }

    // Rotate in place
    void Turn(uint16_t duration, bool left)
    {
        Serial.println(String("In-place turn ") + String(duration) + String(" left ") + left);
        m_pulse.setMotorPower(m_leftMotor, left ? -100 : 100);
        m_pulse.setMotorPower(m_rightMotor, left ? 100 : -100);
        delay(duration);
        m_pulse.setMotorPower(m_rightMotor, 0);
        m_pulse.setMotorPower(m_leftMotor, 0);
    }
  private:
    // PULSE instance
    PULSE m_pulse;

    // Pins
    uint8_t m_leftMotor;
    uint8_t m_rightMotor;
    uint8_t m_armServo;
    uint8_t m_gripperServo;
    uint8_t m_lineSensor;
    uint8_t m_sonicSensor;
};

// Set up the robot instance
Robot robot(1, 2, 0, 0, 0, 0);

void setup()
{
    robot.Drive(100, false);
}

void loop()
{
    
}
