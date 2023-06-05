// Date: 2023-06-01
// Course: TEJ2O1-01
// Name: Elliot McNeil
// Description:
//    This program uses a Russian Morse code library I wrote to output the
//    message "Привет, мир!" ("Hello, world!" in Russian) on the LED and
//    serial.

// Definitions moved here for convenience and Arduino-specific reasons
#include "src/tej2o1-01_m-elliot_utility.h"

// Initializes the program
void setup()
{
    // Initialize my library
    Util::Initialize();
}

// Repeatedly outputs a message
void loop()
{
    // This means "Hello, world!". Morse code doesn't really have any sense of
    // capitalization, Arduino doesn't have wctype.h, and a table to convert
    // would take valuable space, so my Morse functions only support capital
    // letters. Plus signs are used to denote the end of the message.
    Morse::Print(L"ПРИВЕТ, МИР!+");
}
