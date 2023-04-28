#include <LiquidCrystal.h>

// defineste pini LCD
LiquidCrystal lcd(10, 5, 9, 7, 11, 12);

void setup() {
  // seteaza numarul de coloane si linii ale LCD-ului
  lcd.begin(16, 2);
  lcd.print("salut");

  // porneste comunicatia seriala
  //Serial.begin(1000000);
}

void loop() {
 /* 
  // Read value from serial
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Value: ");
    lcd.print(data);
  }*/
}
