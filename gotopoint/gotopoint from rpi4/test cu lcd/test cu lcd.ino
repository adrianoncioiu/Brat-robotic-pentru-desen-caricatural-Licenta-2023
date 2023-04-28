#include <LiquidCrystal.h>

// defineste pini LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // seteaza numarul de coloane si linii ale LCD-ului
  lcd.begin(16, 2);
  lcd.print("hello, world!");

  // porneste comunicatia seriala
  Serial.begin(1000000);
}

void loop() {
  // verifica daca au fost primite date prin portul serial
  if (Serial.available() > 0) { // verifică dacă există date disponibile la portul serial
    String data = Serial.readStringUntil('\n'); // citiți datele până la caracterul newline ('\n')
    float x = data.substring(0, data.indexOf(',')).toFloat(); // extrageți coordonata x din șirul de date
    float y = data.substring(data.indexOf(',') + 1).toFloat(); // extrageți coordonata y din șirul de date
    
    lcd.clear();  // Sterge afisajul LCD-ului
    lcd.setCursor(0,0);  // Seteaza cursorul la pozitia (0,0)
    lcd.print("x:");  // Afiseaza textul "x:"
    lcd.print(x);  // Afiseaza coordonata x
    lcd.setCursor(0,1);  // Seteaza cursorul la pozitia (0,1)
    lcd.print("y:");  // Afiseaza textul "y:"
    lcd.print(y);  // Afiseaza coordonata y
  }
}
