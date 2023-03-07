int ledPin = 13;  // setam LED-ul intern de pe placa Arduino
int incomingByte = 0;   // variabila in care vom salva datele primite de la Python

void setup() {
  pinMode(ledPin, OUTPUT);  // setam pinul LED ca fiind output
  Serial.begin(9600);  // pornim comunicarea seriala la 9600 baud
}

void loop() {
  if (Serial.available() > 0) { // daca exista date disponibile la serial
    incomingByte = Serial.read(); // citim datele primite
    if (incomingByte == '1') { // verificam daca datele primite sunt '1'
      digitalWrite(ledPin, HIGH); // aprindem LED-ul
      Serial.println("LED aprins"); // trimitem un mesaj de confirmare catre Python
    }
    else if (incomingByte == '0') { // verificam daca datele primite sunt '0'
      digitalWrite(ledPin, LOW); // stingem LED-ul
      Serial.println("LED stins"); // trimitem un mesaj de confirmare catre Python
    }
  }
}
