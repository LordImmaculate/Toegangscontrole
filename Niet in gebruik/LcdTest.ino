/*
LCD I2C Test
In dit programma testen we hoe een LCD-display werkt met I2C.
We gebruiken 2 LCD's. Op de eerste */

//Importeer de LiquidCrystal bibliotheek
#include <LiquidCrystal_I2C.h>

//Adres van de LCD's, rijen en kolommen
LiquidCrystal_I2C lcd(0x27, 2, 16);

LiquidCrystal_I2C lcd1(0x20, 2, 16);


void setup()
{
    //Start lcd's en zet backlight aan
    lcd.init();
    lcd1.init();
    lcd.backlight();
    lcd1.backlight();

    //Toon tekst op lcd
    lcd.print("Hello world");
}

void loop()
{
    //Wis alles op lcd en toon "Count: "
    lcd.clear();
    lcd.print("Count: ");

    //Tel af vanaf 100 tot 0, en wanneer 0 is bereikt toon "Boem" op de 2de LCD.
    for (int i = 100; i >= 0; i--)
    {
        lcd.setCursor(7, 0);
        lcd.print("   ");
        lcd.setCursor(7, 0);
        lcd.print(i);
        delay(500);   
    }

    //setCursor verplaats de cursor naar een kolom en rij op het LCD-scherm
    lcd1.setCursor(5, 1);
    lcd1.print("Boem");
}