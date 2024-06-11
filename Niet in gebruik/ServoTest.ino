#include <Servo.h>

Servo slagboom1;

// De hoek van de servo in graden
#define SERVOPIN 6
#define DELAY 1000

void setup()
{
    // De servo wordt aa6ngesloten op pin 9
    slagboom1.attach(SERVOPIN);
    Serial.begin(9600);
}

void loop()
{
    // Slagboom open
    slagboomOpen();
    // Slagboom dicht
    slagboomDicht();

}

bool slagboomOpen()
{
    // De servo draait naar 90 graden

        slagboom1.write(90);
        Serial.println("Slagboom 1 open");

    delay(DELAY);
    return true;
}

bool slagboomDicht()
{
    // De servo draait naar 0 graden
        slagboom1.write(0);
        Serial.println("Slagboom 1 toe");

    delay(DELAY);
    return true;
}