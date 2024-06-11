/*
Keypad Test
Dit programma test hoe de keypad werkt door een code te vragen.
Emil D'Hauwe
*/

// Bibliotheken
#include <Keypad.h>

// Constanten
const String GOEDECODE = "1234";

// Variablen
String ingegevenCode = "";

// Keypad
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad1 = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    bool code = codeIngeven();
}

// codeIngeven is een bool, omdat dit later handig is. In dit programma heeft het geen nut.
bool codeIngeven()
{
    ingegevenCode = "";
    
    while (true)
    {
        char toets = keypad1.getKey();
        while (toets == 0)
        {
            toets = keypad1.getKey();
        }
        if (toets == '#')
        {
            if (ingegevenCode == GOEDECODE)
            {
                Serial.println("Code correct");
                return true;
            }
            else
            {
                Serial.println("Code incorrect");
                return false;
            }
        }

        else if (toets == '*')
        {
            ingegevenCode = "";
            Serial.println("Code gewist");
        }
        else
        {
            ingegevenCode += toets;
            Serial.println(ingegevenCode);
        }
    }
}