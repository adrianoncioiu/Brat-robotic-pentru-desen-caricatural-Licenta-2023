#include <DynamixelSerial.h>
#include <Arduino.h>
#include <AX12A.h>

#define ID  (16u)

  int sensorValue = 0;
  int Val = 0;

void setup() {
 
  
  ax12a.begin(1000000,10, &Serial);
  //Serial.begin(9600, A0);
  delay(1000);
}

void loop() {
  ax12a.ledStatus(ID, OFF);
 
  sensorValue = analogRead(A0);
  Serial.println(sensorValue);

  if(sensorValue < Val){
    ActionS();

  }
  if(sensorValue > Val){

    ActionD();
  }

}
void ActionD(){

  ax12a.moveSpeed(ID,512,100);
  ax12a.ledStatus(ID, ON);

  delay(2000);
  
  
}
void ActionS(){

  ax12a.moveSpeed(ID, 1023,100);
  ax12a.ledStatus(ID, ON);

  delay(2000);
 
}


