/*++

Copyright (c) 2023 Elliot McNeil

Module Name:

    test.ino

Abstract:

    This module implements Russian Morse code for the TETRIX PULSE board.

Author:

    Elliot McNeil (elliot.mcneil@student.tdsb.on.ca) 2023-06-01

--*/

// Determines whether to support normal Uno or TETRIX
#define USE_PULSE 1

#if USE_PULSE
#include <PULSE.h>
PULSE pulse;
#endif

#define CANCEL 0x18 // ASCII cancel, means error/redo
#define DOT 250 // Length of .
#define DASH 500 // Length of -
#define LETTER_PAUSE 750 // space between letters
#define WORD_PAUSE 1000 // space between words

// Calculate the size of a normal array
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

byte
GetCharacterIndex(wchar_t Character)
{
    const wchar_t LookupTable[] = {
        L'А', L'а', L'Б', L'б', L'В', L'в', L'Г', L'г', L'Д', L'д', L'Е', L'е', L'Ж', L'ж', L'З', L'з',
        L'И', L'и', L'Й', L'й', L'К', L'к', L'Л', L'л', L'М', L'м', L'Н', L'н', L'О', L'о', L'П', L'п',
        L'Р', L'р', L'С', L'с', L'Т', L'т', L'У', L'у', L'Ф', L'ф', L'Х', L'х', L'Ц', L'ц', L'Ч', L'ч',
        L'Ш', L'ш', L'Щ', L'щ', L'Ъ', L'ъ', L'Ы', L'ы', L'Ь', L'ь', L'Э', L'э', L'Ю', L'ю', L'Я', L'я',
        L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9', L'0',
        L'.', L',', L':', L';', L'(', L')', L'\'', L'"', L'-', L'/', L'?', L'!', L'@', L'\x18'
    };

    for (int i = 0; i < ARRAY_SIZE(LookupTable); i++)
    {
        if (Character == LookupTable[i])
        {
            return i / isAscii((char)Character) ? 1 : 2; // divide by 2 to account for uppercase and lowercase characters
        }
    }

    return 55; // unknown character or error case
}

void
Encode(
    wchar_t Character
    )
/*++

Routine Description:

    Encode characters into Morse code, output to LED and serial.

Arguments:

    Character - The character to encode.

Return Value:

    None.

--*/
{
    // Element 1 stores dot = 0, dash = 1 as binary, element 2 is length of sequence (number of bits to check)
    const byte Table[][2] = {
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
        {0b000000,   6}, // .     ......
        {0b010101,   6}, // ,     .-.-.-
        {0b111000,   6}, // :     ---...
        {0b10101,    5}, // ;     -.-.-
        {0b101101,   6}, // ()    -.--.-
        {0b011110,   6}, // '     .----.
        {0b010010,   6}, // "     .-..-.
        {0b100001,   6}, // --    -....-
        {0b10010,    5}, // /     -..-.
        {0b001100,   6}, // ?     ..--..
        {0b110011,   6}, // !     --..--
        {0b10001,    5}, // -     -...-
        {0b00000000, 8}, // error ........
        {0b011010,   6}, // @     .--.-.
    };

    if (Character == L' ')
    {
        Serial.write("\n");
        pulse.setRedLED(LOW);
        delay(WORD_PAUSE);
    }
    else
    {
        byte Index = GetCharacterIndex(Character);
        byte Sequence = Table[Index][0];
        byte SequenceLength = Table[Index][1];

        String UnicodeString = String("u") + String(Character, HEX) + ": ";
        Serial.write(UnicodeString.c_str(), UnicodeString.length());
        for (int i = SequenceLength - 1; i >= 0; i--) {
            bool Bit = (Sequence >> i) & 0b1; // Get just the current bit
            Serial.write(Bit ? '-' : '.'); // Write a dash or dot depending on the value
#if USE_TETRIX
            pulse.setRedLED(HIGH);
#else
            // TODO: normal code
#endif
            delay(Bit ? DASH : DOT);
#if USE_TETRIX
            pulse.setRedLED(LOW);
#else
            // TODO: normal code
#endif
            delay(LETTER_PAUSE);
        }
    }
}

void
setup()
/*++

Routine Description:

    This routine initializes the microcontroller.

Arguments:

    None.

Return Value:

    None.

--*/
{
#if USE_TETRIX
    pulse.PulseBegin();
#endif
}

void 
loop()
/*++

Routine Description:

    Executes repeatedly, blinking the red LED 3 times over 3 seconds.

Arguments:

    None.

Return Value:

    None.

--*/
{
    
}
