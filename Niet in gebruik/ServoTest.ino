/*
Slagboom test
Deze code test de slagbomen door ze te openen en te sluiten.

Emil D'Hauwe
*/

#include <Servo.h>

Servo slagboom1;
Servo slagboom2;

// Constanten
#define SERVOPIN1 3
#define SERVOPIN2 5
#define DELAY 1000

void setup()
{
    // De servo wordt aangesloten op de pinnen
    slagboom1.attach(SERVOPIN1);
    slagboom2.attach(SERVOPIN2);
    Serial.begin(9600);
}

void loop()
{
    // Slagboom 1 open
    slagboomOpen(1);
    // Slagboom 1 dicht
    slagboomDicht(1);
    // Slagboom 2 open
    slagboomOpen(2);
    // Slagboom 2 dicht
    slagboomDicht(2);
}

bool slagboomOpen(int servoNummer)
{
    // De servo draait naar 90 graden
    if (servoNummer == 1)
    {
        slagboom1.write(90);
        Serial.println("Slagboom 1 open");
    }
    else if (servoNummer == 2)
    {
        slagboom2.write(90);
        Serial.println("Slagboom 2 open");
    }
    delay(DELAY);
    return true;
}

bool slagboomDicht(int servoNummer)
{
    // De servo draait naar 0 graden
    if (servoNummer == 1)
    {
        slagboom1.write(0);
        Serial.println("Slagboom 1 toe");
    }
    else if (servoNummer == 2)
    {
        slagboom2.write(0);
        Serial.println("Slagboom 2 toe");
    }
    delay(DELAY);
    return true;
}