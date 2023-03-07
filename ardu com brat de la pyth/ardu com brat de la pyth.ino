#include <DynamixelSerial.h>

int id1 = 11;
int id2 = 6;
int id3 = 16;
int command=9;

void setup(){
    Dynamixel.setSerial(&Serial);
    Dynamixel.begin(1000000,10);
    Serial.begin(1000000);
    delay(1000);
}

void loop(){
    Dynamixel.moveSpeed(id2,random(200,800),random(200,800));
    if(Serial.available() > 0) {
        command = Serial.read()-'0';
    }
    if (command == 0) {
        Dynamixel.turn(id1, LEFT, 1000);
        delay(2000);
        }
    if (command == 1) {
        Dynamixel.turn(id1, RIGTH, 1000);
        delay(2000);
    }
  
}