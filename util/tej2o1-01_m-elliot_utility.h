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
constexpr int LED_PIN = LED_BUILTIN;
#endif

// This analog pin is expected to have nothing connected so it can be used to
// seed the random number generator
constexpr int RANDOM_PIN = 0;

// ASCII cancel, means error/redo
#define CANCEL 0x18

// General utility functions
namespace Util
{
    // Initialize frequently used things
    extern void Initialize();

    // Array size
    template<class T, size_t N>
    constexpr size_t ArraySize(T (&)[N]) { return N; }
}

// Morse code functions
namespace Morse
{
    // Timings in milliseconds
    constexpr short DOT_LENGTH = 60; // Length of .
    constexpr short DASH_LENGTH = DOT_LENGTH * 3; // Length of -
    constexpr short LETTER_PAUSE_LENGTH = DOT_LENGTH * 3; // space between letters
    constexpr short WORD_PAUSE_LENGTH = DOT_LENGTH * 7; // space between words

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