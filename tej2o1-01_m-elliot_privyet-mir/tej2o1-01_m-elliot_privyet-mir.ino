// Date: 2023-06-01
// Course: TEJ2O1-01
// Name: Elliot McNeil
// Description:
//    This program uses a Russian Morse code library I wrote to output the
//    message "Привет, мир!" ("Hello, world!" in Russian) on the LED and
//    serial.

// Definitions moved here for convenience and Arduino-specific reasons
#include "src/tej2o1-01_m-elliot_utility.h"

// Make sure PULSE is in use
#ifndef USE_PULSE
#error This code requires PULSE
#endif

// Initializes the program
void setup()
{
    // Initialize my library
    Util::Initialize();
}

// Outputs the message with a 1 second delay between
void loop()
{
    // This means "Hello, world!". Plus signs are used to denote the end of the
    // message, because the sequence for them is also used for that.
    Morse::Print(L"Привет, мир!+");
    delay(1000);
}
