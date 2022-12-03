#include <DynamixelSerial.h>
#include <Arduino.h>
#include <AX12A.h>

#define ID  (16u)

  int sensorVal = 0;
  int Val = 0;
  int Poz;

void setup() {
 
  
  ax12a.begin(1000000,10, &Serial);
  //Serial.begin(9600, A0);
  delay(1000);
}

void loop() {
  ax12a.ledStatus(ID, OFF);
  delay(1000);
 
  sensorVal = analogRead(A0);
  Serial.println(sensorVal);
if (sensorVal != Val){
  Poz = sensorVal;
  Action();
}

}
void Action(){

  ax12a.moveSpeed(ID,Poz,100);
  ax12a.ledStatus(ID, ON);

  delay(2000);
  
  
}



