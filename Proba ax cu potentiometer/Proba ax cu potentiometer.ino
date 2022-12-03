#include <DynamixelSerial.h>
#include <Arduino.h>
#include <AX12A.h>

#define ID1  (16u)
#define ID2  (6u)
#define ID3  (11u)

  int sensorVal1, sensorVal2, sensorVal3 = 0;
  int Val = 0;
  int Poz1, Poz2, Poz3;

void setup() {
 
  
  ax12a.begin(1000000,10, &Serial);
  //Serial.begin(9600, A0);
  delay(1000);
}

void loop() {
  ax12a.ledStatus(ID1, OFF);
  ax12a.ledStatus(ID2, OFF);
  ax12a.ledStatus(ID3, OFF);
  delay(1000);
 
  sensorVal1 = analogRead(A0);
  Serial.println(sensorVal1);

  sensorVal2 = analogRead(A1);
  Serial.println(sensorVal2);

  sensorVal3 = analogRead(A3);
  Serial.println(sensorVal3);

if (sensorVal1 != Val){
  Poz1 = sensorVal1;
  Action();
  ax12a.ledStatus(ID1, ON);
}

if (sensorVal2 != Val){
  Poz2 = sensorVal2;
  Action();
  ax12a.ledStatus(ID2, ON);
}

if (sensorVal3 != Val){
  Poz3 = sensorVal3;
  Action();
  ax12a.ledStatus(ID3, ON);
}

}
void Action(){

  ax12a.moveSpeed(ID1,Poz1,100);
  ax12a.moveSpeed(ID2,Poz2,100);
  ax12a.moveSpeed(ID3,Poz3,100);
  
  delay(2000);
  
  
}



