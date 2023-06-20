// Date: 2023-06-01
// Course: TEJ2O1-01
// Name: Elliot McNeil
// Description: Robot

#define SIMON

#ifdef SIMON
#include <PULSE.h>
#else
#include "src/tej2o1-01_m-elliot_utility.h"
#endif

class Robot
{
  public:
    Robot() = default;

    // Initialize the robot
    Robot(uint8_t leftMotor, uint8_t rightMotor, uint8_t armServo,
          uint8_t gripperServo, uint8_t lineSensor, uint8_t sonicSensor)
        : m_leftMotor(leftMotor), m_rightMotor(rightMotor),
          m_armServo(armServo), m_gripperServo(gripperServo),
          m_lineSensor(lineSensor), m_sonicSensor(sonicSensor)
    {
#ifdef SIMON
        m_pulse.PulseBegin();
#else
        m_pulse = pulse;
#endif
        SetArm(90);
        SetGripper(0);
        delay(1000);
        Serial.println("Robot initialized");
    }

    // Set arm position 0-180 degrees
    void SetArm(uint16_t degrees)
    {
        Serial.println(String("Arm ") + degrees);
        m_pulse.setServoPosition(m_armServo, degrees);
    }

    // Set gripper percentage
    void SetGripper(uint16_t percent)
    {
        Serial.println(String("Gripper ") + percent + "%");
        m_pulse.setServoPosition(m_gripperServo, percent / 100.0f * 180);
    }

    // Go straight
    void Drive(uint16_t duration = 0, uint8_t power = 100, bool backward = false)
    {
        Serial.println(String("Drive ") + duration + " " + backward);
        m_pulse.setMotorPower(m_rightMotor, backward ? -power : power);
        m_pulse.setMotorPower(m_leftMotor, backward ? power : -power);
        if (duration > 0)
        {
            delay(duration);
            Stop();
        }
    }

    // Rotate
    void Turn(uint16_t duration = 0, bool left = false)
    {
        Serial.println(String("In-place turn ") + duration + " left " + left);
        // motors are opposite
        m_pulse.setMotorPower(m_rightMotor, left ? 100 : -100);
        m_pulse.setMotorPower(m_leftMotor, left ? 100 : -100);
        if (duration > 0)
        {
            delay(duration);
            Stop();
        }
    }

    // Detect line
    bool DetectLine()
    {
        return m_pulse.readLineSensor(m_lineSensor) == 0;
    }

    // Detect object with sonic sensor
    uint32_t DetectObject()
    {
        return m_pulse.readSonicSensorCM(m_sonicSensor);
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
#ifdef SIMON
    PULSE m_pulse;
#else
    PULSE m_pulse;
#endif

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

void setup()
{
    robot = Robot(1, 2, 3, 1, 2, 3);
#ifndef SIMON
    Util::Initialize();
    Morse::Output("Меня зовут Грег!+");
#endif
}

void AvoidObstacles()
{
    robot.Turn(500, true);
    robot.Drive(1000);
    robot.Turn(1000);
}

void End()
{
    robot.Stop();
    robot.SetArm(45);
    robot.SetGripper(100);

    // End
    while (true)
    {
#ifndef SIMON
        Morse::Output("Сделаный!+");
#endif
    }
}

void loop()
{

    if (robot.DetectObject() <= 30)
    {
        AvoidObstacles();
    }
    else
    {
        if (robot.DetectLine())
        {
            End();
        }
        else
        {
            robot.Drive(0, 50);
        }
    }
}
