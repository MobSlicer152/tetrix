#pragma once

#include <Arduino.h>

// Determines whether to support normal Arduino or TETRIX
#define USE_PULSE 1

#if USE_PULSE
#include <PULSE.h>

// Global PULSE instance
extern PULSE pulse;
#else
// The pin the LED is on
#define LED_PIN LED_BUILTIN
#endif

// Calculate the size of a normal array (i.e. not a pointer)
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

// ASCII cancel, means error/redo
#define CANCEL 0x18

// Morse code functions
namespace Morse {
    // Timings in milliseconds
    constexpr short DOT_LENGTH = 500; // Length of .
    constexpr short DASH_LENGTH = 1000; // Length of -
    constexpr short LETTER_PAUSE_LENGTH = 1250; // space between letters
    constexpr short WORD_PAUSE_LENGTH = 1500; // space between words
    constexpr short MESSAGE_PAUSE_LENGTH = 2000; // space between messages

    // Converts the given character to Morse code, outputting it by blinking the 
    // LED and serial. Returns whether the character was a cancel/invalid.
    extern bool Output(wchar_t character);

    // Outputs a NUL-terminated UTF-16 string
    extern void Print(const wchar_t* message);

    // Structure to store Morse code sequences
    typedef struct Code {
        wchar_t character; // the character represented
        char sequence; // binary, 1 = dash, 0 = dot
        char length; // number of relevant bits in sequence
    };

    // Look up a character in the Morse code table
    extern const Code& GetCharacterCode(wchar_t character);
}