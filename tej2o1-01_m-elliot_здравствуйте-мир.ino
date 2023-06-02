/*++

Date:

    2023-06-01

Course:

    TEJ2O1-01

Name:

    Elliot McNeil

Description:

    This program implements Russian Morse code with output to an LED and serial.

--*/

// Definitions moved here for convenience and Arduino-specific reasons
#include "tej2o1-01_m-elliot_utility.h"

// Initializes the program
void setup()
{
    // Initialize serial
    Serial.begin(9600);

#if USE_TETRIX
    // Initialize PULSE
    pulse.PulseBegin();
#else
    // Initialize desired LED
    pinMode(LED_PIN, OUTPUT);
#endif
}

// Repeatedly outputs a message
void loop()
{
    // This means "Hello, world!". Morse code doesn't really have any sense of
    // capitalization, Arduino doesn't have wctype.h, and a table to convert
    // would take valuable space, so Encode only supports capital letters.
    Morse::Print(L"ЗДРАВСТВУЙТЕ, МИР!");
}
