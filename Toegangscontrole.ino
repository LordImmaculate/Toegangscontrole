/*  In vullen: volledige beschrijving van de werking

  Emil D'Hauwe
*/

// Bibliotheken
#include <Servo.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

// Constanten
#define INTRIGPIN 5
#define INECHOPIN 4
#define UITTRIGPIN 3
#define UITECHOPIN 2
#define SLAGBOOMPIN 6
#define SLAGBOOMDELAY_ms 10
#define DUURPULS_ms 10
#define WACHTTIJD_ms 500
#define MINAFSTAND_cm 20
#define LCDADRES 0x27

#define GOEDECODE "2024"

// Variablen
String code = "";
int aantalPlaatsen = 1;

// Bibliotheken Starten
Servo slagboom;
LiquidCrystal_I2C lcd(LCDADRES, 2, 16);

// Keypad
const byte ROWS = 4;
const byte COLS = 4;
byte rowPins[ROWS] = {A0, 13, 12, 11};
byte colPins[COLS] = {10, 9, 8, 7};

char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

Keypad keypad1 = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.print("Aantal Plaatsen:");
  lcd.setCursor(0, 1);
  lcd.print(aantalPlaatsen);

  // Pinnen Instellen
  pinMode(INTRIGPIN, OUTPUT);
  pinMode(INECHOPIN, INPUT);
  pinMode(UITTRIGPIN, OUTPUT);
  pinMode(UITECHOPIN, INPUT);
  slagboom.attach(SLAGBOOMPIN);

  sluitSlagboom();
}

void loop()
{
  // BUITENRIJDEN

  if (sensUit() == true)
  {
    // Er staat een wagen aan de uitrit

    if (sensIn() == false)
    {
      // Er staat geen wagen aan de inrit

      openSlagboom();

      // Wacht tot de wagen aan de inrit is

      while (sensIn() == false)
        ;

      // Wacht tot de wagen weg is bij de inrit

      while (sensIn() == true)
        ;

      sluitSlagboom();

      aantalPlaatsen++;
      printPlaatsen();
    }
  }

  // BINNENRIJDEN

  if (aantalPlaatsen > 0)
  {
    if (sensIn() == true)
    {
      // Er staat een wagen voor de inrit

      if (sensUit() == false)
      {
        // Er staat geen wagen voor uitrit

        lcd.clear();
        lcd.print("Geef code in");
        if (leesCode())
        {
          openSlagboom();

          while (sensUit() == false)
            ;
          while (sensUit() == true)
            ;
          sluitSlagboom();
          aantalPlaatsen--;
          printPlaatsen();
        }
      }
    }
  }
}

bool sensIn()
{
  // Lokale Variablen
  int afstand_cm;
  long pulsDuratie;

  // Stuur een 10 ms puls naar de trigger pin
  digitalWrite(INTRIGPIN, HIGH);
  delay(DUURPULS_ms);
  digitalWrite(INTRIGPIN, LOW);

  // Lees de duratie van de pin in
  pulsDuratie = pulseIn(INECHOPIN, HIGH);

  // Berken de afstand in cm
  afstand_cm = pulsDuratie * 0.034 / 2;
  delay(WACHTTIJD_ms);
  if (afstand_cm <= MINAFSTAND_cm)
    return true;
  else
    return false;
}

bool sensUit()
{
  // Lokale Variablen
  int afstand_cm;
  long pulsDuratie;

  // Stuur een 10 ms puls naar de trigger pin
  digitalWrite(UITTRIGPIN, HIGH);
  delay(DUURPULS_ms);
  digitalWrite(UITTRIGPIN, LOW);

  // Lees de duratie van de pin in
  pulsDuratie = pulseIn(UITECHOPIN, HIGH);

  // Berken de afstand in cm
  afstand_cm = pulsDuratie * 0.034 / 2;
  delay(WACHTTIJD_ms);
  if (afstand_cm <= MINAFSTAND_cm)
    return true;
  else
    return false;
}

void openSlagboom()
{
  // De servo draait naar 90 graden
  for (int hoek = 90; hoek >= 0; hoek--)
  {
    slagboom.write(hoek);
    delay(SLAGBOOMDELAY_ms);
  }
  Serial.println("Slagboom open");
}

void sluitSlagboom()
{
  for (int hoek = 0; hoek <= 90; hoek++)
  {
    // De servo draait naar 0 graden
    slagboom.write(hoek);
    delay(SLAGBOOMDELAY_ms);
  }
  Serial.println("Slagboom toe");
}

bool leesCode()
{
  String ingegevenCode = "";

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
        lcd.clear();
        lcd.print("Code correct");
        return true;
      }
      else
      {
        Serial.println("Code incorrect");
        lcd.clear();
        lcd.print("Code incorrect");
        return false;
      }
    }

    else if (toets == '*')
    {
      ingegevenCode = "";
      Serial.println("Code gewist");
      lcd.clear();
      lcd.print("Code gewist");
    }
    else
    {
      ingegevenCode += toets;
      Serial.println(ingegevenCode);
      lcd.clear();
      lcd.print(ingegevenCode);
      lcd.setCursor(0, 1);
    }
  }
}

void printPlaatsen()
{
  if (aantalPlaatsen == 0)
          {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Volzet");
          }

          else
          {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Aantal Plaatsen:");
            lcd.setCursor(0, 1);
            lcd.print(aantalPlaatsen);
          }
}