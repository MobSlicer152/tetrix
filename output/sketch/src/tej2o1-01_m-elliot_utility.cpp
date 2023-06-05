#line 1 "C:\\Users\\bramb\\source\\repos\\tetrix\\tej2o1-01_m-elliot_servo\\src\\tej2o1-01_m-elliot_utility.cpp"
// Functions in separate file so they can be reused

#include "tej2o1-01_m-elliot_utility.h"

#ifdef USE_PULSE
PULSE pulse;
#endif

namespace Util
{
    // Initialize things frequently used
    void Initialize()
    {
        // Initialize serial
        Serial.begin(9600);

    #if USE_PULSE
        // Initialize PULSE
        pulse.PulseBegin();
    #else
        // Initialize desired LED
        pinMode(LED_PIN, OUTPUT);
    #endif

        // Seed RNG, this pin is expected to be disconnected
        randomSeed(analogRead(RANDOM_PIN));

        Serial.println("Utility library initialized");
    }
}

namespace Morse
{
    // Character encoding table, efficiently stores necessary information.
    static const Code TABLE[] = {
        {L'А',    0b01,       2}, // .-
        {L'Б',    0b1000,     4}, // -...
        {L'В',    0b011,      3}, // .--
        {L'Г',    0b110,      3}, // --.
        {L'Д',    0b100,      3}, // -..
        {L'Е',    0b0,        1}, // .
        {L'Ж',    0b0001,     4}, // ...-
        {L'З',    0b1100,     4}, // ..--
        {L'И',    0b00,       2}, // ..
        {L'Й',    0b0111,     4}, // .---
        {L'К',    0b101,      3}, // -.-
        {L'Л',    0b0100,     4}, // .-..
        {L'М',    0b11,       2}, // --
        {L'Н',    0b10,       2}, // -.
        {L'О',    0b111,      3}, // ---
        {L'П',    0b0110,     4}, // .--.
        {L'Р',    0b010,      3}, // .-.
        {L'С',    0b000,      3}, // ...
        {L'Т',    0b1,        1}, // -
        {L'У',    0b001,      3}, // ..-
        {L'Ф',    0b0010,     4}, // ..-.
        {L'Х',    0b0000,     4}, // ....
        {L'Ц',    0b1010,     4}, // -.-.
        {L'Ч',    0b1110,     4}, // ---.
        {L'Ш',    0b1111,     4}, // ----
        {L'Щ',    0b1101,     4}, // --.-
        {L'Ъ',    0b11011,    5}, // --.--
        {L'Ы',    0b1011,     4}, // -.--
        {L'Ь',    0b1001,     4}, // -..-
        {L'Э',    0b00100,    5}, // ..-..
        {L'Ю',    0b0011,     4}, // ..--
        {L'Я',    0b0101,     4}, // .-.-
        {L'1',    0b01111,    5}, // .----
        {L'2',    0b00111,    5}, // ..---
        {L'3',    0b00011,    5}, // ...--
        {L'4',    0b00001,    5}, // ....-
        {L'5',    0b00000,    5}, // .....
        {L'6',    0b10000,    5}, // -....
        {L'7',    0b11000,    5}, // --...
        {L'8',    0b11100,    5}, // ---..
        {L'9',    0b11110,    5}, // ----.
        {L'0',    0b11111,    5}, // -----
        {L'.',    0b010101,   6}, // .-.-.-
        {L',',    0b110011,   6}, // --..--
        {L'?',    0b001100,   6}, // ..--..
        {L'\'',   0b011110,   6}, // .----.
        {L'!',    0b101011,   6}, // -.-.--
        {L'/',    0b10010,    5}, // -..-.
        {L'(',    0b10110,    5}, // -.--.
        {L')',    0b101101,   6}, // -.--.-
        {L'&',    0b01000,    5}, // .-...
        {L':',    0b111000,   6}, // ---...
        {L';',    0b10101,    6}, // -.-.-.
        {L'=',    0b100001,   6}, // -....-
        {L'+',    0b01010,    5}, // .-.-.
        {L'-',    0b10001,    5}, // -...-
        {L'_',    0b001101,   6}, // ..--.-
        {L'"',    0b010010,   6}, // .-..-.
        {L'$',    0b0001001,  7}, // ...-..-
        {L'@',    0b011010,   6}, // .--.-.
        {CANCEL,  0b00000000, 8}, // ........
    };

    // Find the code for the given character, returning the address of the entry
    const Code& GetCharacterCode(wchar_t character)
    {
        // Look up the character in the table if it isn't CANCEL, otherwise just
        // return the CANCEL sequence
        for (int i = 0; i < Util::ArraySize(TABLE) && character != CANCEL; i++)
        {
            if (character == TABLE[i].character)
            {
                return TABLE[i];
            }
        }

        // Return the CANCEL sequence if the character was not found
        return TABLE[Util::ArraySize(TABLE) - 1];
    }

    bool Output(wchar_t character)
    {
        // If the character is a space, just pause
        if ( character == L' ' )
        {
            Serial.write("space\r\n");
#if USE_PULSE
            pulse.setRedLED(LOW);
#endif
            delay(WORD_PAUSE_LENGTH);

            return false;
        }
        else // Otherwise, look up the character and output it
        {
            // Get sequence for the character
            const Code& code = GetCharacterCode(character);

            // Output the value of the character in hexadecimal
            Serial.print(character, HEX);
            Serial.print("\t");

            // Iterate through the bits in the sequence
            for ( int i = code.length - 1; i >= 0; i-- )
            {
                bool Bit = (code.sequence >> i) & 0b1; // Get just the current bit
                Serial.print(Bit ? '-' : '.'); // Write a dash or dot depending on the value

                // Toggle the LED on and off, waiting the right amount of time in between
#if USE_PULSE
                pulse.setRedLED(HIGH);
#else
                digitalWrite(LED_PIN, HIGH);
#endif
                delay(Bit ? DASH_LENGTH : DOT_LENGTH);
#if USE_PULSE
                pulse.setRedLED(LOW);
#else
                digitalWrite(LED_PIN, LOW);
#endif
                delay(Bit ? DASH_LENGTH : DOT_LENGTH);
            }
            Serial.print("\r\n");

            delay(LETTER_PAUSE_LENGTH);

            return code.character == CANCEL;
        }
    }

    void Print(const wchar_t* message)
    {
        // Go through all characters in the string until the NUL byte at the
        // end
        wchar_t c;
        while ((c = *message++))
        {
            if (Output(c))
            {
                break;
            }
        }

        // Wait to start the next message
        Serial.print("END\r\n\n");
        delay(MESSAGE_PAUSE_LENGTH);
    }
}