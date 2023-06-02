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

// Determines whether to support normal Arduino or TETRIX
#define USE_PULSE 0

#if USE_PULSE
#include <PULSE.h>

// Global PULSE instance
PULSE pulse;
#else
// The pin the LED is on
#define PIN 3
#endif

#define CANCEL 0x18 // ASCII cancel, means error/redo

// Timings in milliseconds
#define DOT 500 // Length of .
#define DASH 1000 // Length of -
#define LETTER_PAUSE 1250 // space between letters
#define WORD_PAUSE 1500 // space between words

#define CANCEL_INDEX 60 // index of the CANCEL character in the tables

// Calculate the size of a normal array (i.e. not a pointer)
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

byte GetCharacterIndex(wchar_t character)
{
    // MUST BE KEPT IN SYNC WITH THE TABLE IN Encode
    // 122 bytes
    const wchar_t LOOKUP_TABLE[] = {
        L'А', L'Б', L'В', L'Г', L'Д', L'Е', L'Ж', L'З',
        L'И', L'Й', L'К', L'Л', L'М', L'Н', L'О', L'П',
        L'Р', L'С', L'Т', L'У', L'Ф', L'Х', L'Ц', L'Ч',
        L'Ш', L'Щ', L'Ъ', L'Ы', L'Ь', L'Э', L'Ю', L'Я',
        L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9', L'0',
        L'.', L',', L'?', L'\'', L'!', L'/', L'(', L')', L'&', L':', L';', L'=', L'+', L'-', L'_', L'"', L'$', L'@', L'\x18'
    };

    for (int i = 0; i < ARRAY_SIZE(LOOKUP_TABLE); i++)
    {
        if (character == LOOKUP_TABLE[i])
        {
            return i;
        }
    }

    return CANCEL_INDEX; // unknown character or error case
}

// Converts the given character to Morse code, outputting it by blinking the 
// LED and serial. Returns whether the character was a cancel/invalid.
bool Encode(wchar_t character)
{
    // Element 1 stores dot = 0, dash = 1 as binary, element 2 is length of 
    // sequence (number of bits to check)
    // MUST BE KEPT IN SYNC WITH THE LOOKUP TABLE IN GetCharacterIndex
    // 122 bytes
    const byte TABLE[][2] = {
        {0b01,       2}, // А     .-
        {0b1000,     4}, // Б     -...
        {0b011,      3}, // В     .--
        {0b110,      3}, // Г     --.
        {0b100,      3}, // Д     -..
        {0b0,        1}, // Е     .
        {0b0001,     4}, // Ж     ...-
        {0b1100,     4}, // З     ..--
        {0b00,       2}, // И     ..
        {0b0111,     4}, // Й     .---
        {0b101,      3}, // К     -.-
        {0b0100,     4}, // Л     .-..
        {0b11,       2}, // М     --
        {0b10,       2}, // Н     -.
        {0b111,      3}, // О     ---
        {0b0110,     4}, // П     .--.
        {0b010,      3}, // Р     .-.
        {0b000,      3}, // С     ...
        {0b1,        1}, // Т     -
        {0b001,      3}, // У     ..-
        {0b0010,     4}, // Ф     ..-.
        {0b0000,     4}, // Х     ....
        {0b1010,     4}, // Ц     -.-.
        {0b1110,     4}, // Ч     ---.
        {0b1111,     4}, // Ш     ----
        {0b1101,     4}, // Щ     --.-
        {0b11011,    5}, // Ъ     --.--
        {0b1011,     4}, // Ы     -.--
        {0b1001,     4}, // Ь     -..-
        {0b00100,    5}, // Э     ..-..
        {0b0011,     4}, // Ю     ..--
        {0b0101,     4}, // Я     .-.-
        {0b01111,    5}, // 1     .----
        {0b00111,    5}, // 2     ..---
        {0b00011,    5}, // 3     ...--
        {0b00001,    5}, // 4     ....-
        {0b00000,    5}, // 5     .....
        {0b10000,    5}, // 6     -....
        {0b11000,    5}, // 7     --...
        {0b11100,    5}, // 8     ---..
        {0b11110,    5}, // 9     ----.
        {0b11111,    5}, // 0     -----
        {0b010101,   6}, // .     .-.-.-
        {0b110011,   6}, // ,     --..--
        {0b001100,   6}, // ?     ..--..
        {0b011110,   6}, // '     .----.
        {0b101011,   6}, // !     -.-.--
        {0b10010,    5}, // /     -..-.
        {0b10110,    5}, // (     -.--.
        {0b101101,   6}, // )     -.--.-
        {0b01000,    5}, // &     .-...
        {0b111000,   6}, // :     ---...
        {0b10101,    6}, // ;     -.-.-.
        {0b100001,   6}, // =     -....-
        {0b01010,    5}, // +     .-.-.
        {0b10001,    5}, // -     -...-
        {0b001101,   6}, // _     ..--.-
        {0b010010,   6}, // "     .-..-.
        {0b0001001,  7}, // $     ...-..-
        {0b011010,   6}, // @     .--.-.
        {0b00000000, 8}, // error ........
    };

    if ( character == L' ' )
    {
        Serial.write("space\r\n");
#if USE_TETRIX
        pulse.setRedLED(LOW);
#endif
        delay(WORD_PAUSE);

        return false;
    }
    else
    {
        byte index = GetCharacterIndex(character);
        byte sequence = TABLE[index][0];
        byte sequenceLength = TABLE[index][1];

        Serial.print(character, HEX);
        Serial.print("\t");
        for ( int i = sequenceLength - 1; i >= 0; i-- )
        {
            bool Bit = (sequence >> i) & 0b1; // Get just the current bit
            Serial.print(Bit ? '-' : '.'); // Write a dash or dot depending on the value
#if USE_TETRIX
            pulse.setRedLED(HIGH);
#else
            digitalWrite(PIN, HIGH);
#endif
            delay(Bit ? DASH : DOT);
#if USE_TETRIX
            pulse.setRedLED(LOW);
#else
            digitalWrite(PIN, LOW);
#endif
            delay(LETTER_PAUSE);
        }
        Serial.print("\r\n");

        if ( index == CANCEL_INDEX )
        {
            return true;
        }

        return false;
    }
}

// 
void EncodeString(const wchar_t* message)
{
    wchar_t c;
    while ((c = *message++))
    {
        if (Encode(c))
        {
            break;
        }
    }
}

// Initializes the program
void setup()
{
    // Initialize serial
    Serial.begin(9600);

#if USE_TETRIX
    // Initialize PULSE
    pulse.PulseBegin();
#endif
}

// Repeatedly outputs a message
void loop()
{
    // This means "Hello, world!". Morse code doesn't really have any sense of
    // capitalization, Arduino doesn't have wctype.h, and a table to convert
    // would take valuable space, so Encode only supports capital letters.
    EncodeString(L"ЗДРАВСТВУЙТЕ, ЗЕМЛЯ!");
}
