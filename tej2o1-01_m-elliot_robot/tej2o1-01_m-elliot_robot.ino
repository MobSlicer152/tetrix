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
    Robot() = default;

    // Initialize the robot
    Robot(uint8_t leftMotor, uint8_t rightMotor, uint8_t armServo, uint8_t gripperServo, uint8_t lineSensor, uint8_t sonicSensor)
        : m_leftMotor(leftMotor), m_rightMotor(rightMotor), m_armServo(armServo), m_gripperServo(gripperServo), m_lineSensor(lineSensor), m_sonicSensor(sonicSensor)
    {
        m_pulse.PulseBegin();
        SetArm(90);
        SetGripper(0);
        delay(1000);
        Serial.println("Robot initialized");
    }

    // Set arm position 0-180 degrees
    void SetArm(uint32_t degrees)
    {
        Serial.println(String("Arm ") + degrees);
        m_pulse.setServoPosition(m_armServo, degrees);
    }

    // Set gripper percentage
    void SetGripper(uint32_t percent)
    {
        Serial.println(String("Gripper ") + String(percent) + "%");
        m_pulse.setServoPosition(m_gripperServo, percent / 100.0f * 180);
    }

    // Go straight
    void Drive(uint16_t duration, bool backward)
    {
        Serial.println(String("Drive ") + String(duration) + String(" ") + backward);
        m_pulse.setMotorPower(m_rightMotor, 100);
        m_pulse.setMotorPower(m_leftMotor, -100);
        delay(duration);
        m_pulse.setMotorPower(m_rightMotor, 0);
        m_pulse.setMotorPower(m_leftMotor, 0);
    }

    // Turn left
    void TurnLeft(uint16_t duration)
    {
        Serial.println(String("Left turn ") + duration);
        m_pulse.setMotorPower(m_rightMotor, 100);
        m_pulse.setMotorPower(m_leftMotor, -10);
        delay(duration);
        m_pulse.setMotorPower(m_rightMotor, 0);
        m_pulse.setMotorPower(m_leftMotor, 0);
    }

    // Turn right
    void TurnRight(uint16_t duration)
    {
        Serial.println(String("Left turn ") + duration);
        m_pulse.setMotorPower(m_rightMotor, 10);
        m_pulse.setMotorPower(m_leftMotor, -100);
        delay(duration);
        m_pulse.setMotorPower(m_rightMotor, 0);
        m_pulse.setMotorPower(m_leftMotor, 0);
    }

    // Rotate in place
    void Turn(uint16_t duration, bool left)
    {
        Serial.println(String("In-place turn ") + String(duration) + String(" left ") + left);
        m_pulse.setMotorPower(m_rightMotor, left ? 100 : -100);
        m_pulse.setMotorPower(m_leftMotor, left ? -100 : 100);
        delay(duration);
        m_pulse.setMotorPower(m_rightMotor, 0);
        m_pulse.setMotorPower(m_leftMotor, 0);
    }

    // Stop motors
    void Stop()
    {
        Serial.println("Stop");
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
Robot robot;

PULSE pulse;

void setup()
{
    robot = Robot(1, 2, 2, 1, 2, 3);
    robot.Drive(1000, false);
}

void loop()
{
}
