/*
LCD Test
Dit programma test hoe de lcd's werken, door er een boodschap op te printen en de cursor van plaats te doen verandren.
Emil D'Hauwe
*/

// Bibliotheken
#include <LiquidCrystal_I2C.h>

//Geef lcd's een I2C-adres, en zeg hoe groot ze zijn.
LiquidCrystal_I2C lcd(0x27, 2, 16);

LiquidCrystal_I2C lcd1(0x20, 2, 16);


void setup()
{
    //Start lcd's en zet licht aan.
    lcd.init();
    lcd1.init();
    lcd.backlight();
    lcd1.backlight();

    //Print een tekst op de lcd.
    lcd.print("Pannenkoek");
}

void loop()
{
    // countdown
    lcd.clear();
    lcd.print("Count: ");

    for (int i = 10; i >= 0; i--)
    {
        lcd.setCursor(7, 0);
        lcd.print("   ");
        lcd.setCursor(7, 0);
        lcd.print(i);
        delay(1000);
    }

    lcd1.setCursor(5, 0);
    lcd1.print("Boem");
}