#include <DynamixelSerial.h>

int id1 = 11;
int id2 = 6;
int id3 = 16;
int command=2;
int Position;

void setup(){
    Dynamixel.setSerial(&Serial);
    Dynamixel.begin(1000000,10);
    Serial.begin(1000000);
    delay(1000);
}

void loop(){
    //Dynamixel.moveSpeed(id2,random(200,800),random(200,800));
    //Position = Dynamixel.readPosition(id1);
    //Serial.print("I received:  ");
    //Serial.println(Position, DEC);
    if(Serial.available() > 0) {
        command = Serial.read()-'0';
        Serial.println(command-'0', DEC);
        
       // Dynamixel.turn(id1, LEFT, 1000);
        Serial.flush();
    
    }
    if (command == 0) {
        Serial.println("stanga");
        Dynamixel.turn(id1, LEFT, 1000);
        delay(2000);
        
        
        
        }
      Serial.flush();
    if (command == 1) {
        Serial.println("dreapta");
        Dynamixel.turn(id1, RIGTH, 1000);
        delay(2000);
        
    }
      Serial.flush();
   
}