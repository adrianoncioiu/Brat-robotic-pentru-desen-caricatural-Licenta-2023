#include <DynamixelSerial.h>

int id1 = 11;
int id2 = 6;
int id3 = 16;

void setup(){
Dynamixel.setSerial(&Serial);
Dynamixel.begin(1000000,10);  
delay(1000);
}

void loop(){
  Dynamixel.move(id1,random(200,800));  // 200 to 800
  delay(1000);
  Dynamixel.moveSpeed(id1,random(200,800),random(200,800));
  delay(2000);
  Dynamixel.setEndless(id1,ON);
  Dynamixel.turn(id1,RIGTH,1000);
  delay(3000);
  Dynamixel.turn(id1,LEFT,1000);
  delay(3000);
  Dynamixel.setEndless(id1,OFF);
  Dynamixel.ledStatus(id1,ON);
  Dynamixel.moveRW(id1,512);
  delay(1000);
  Dynamixel.action();
  Dynamixel.ledStatus(id1,OFF);
 
delay(1000);

  Dynamixel.move(id2,random(200,800));  // 200 to 800
  delay(1000);
  Dynamixel.moveSpeed(id2,random(200,800),random(200,800));
  delay(2000);
  Dynamixel.setEndless(id2,ON);
  Dynamixel.turn(id2,RIGTH,1000);
  delay(3000);
  Dynamixel.turn(id2,LEFT,1000);
  delay(3000);
  Dynamixel.setEndless(id2,OFF);
  Dynamixel.ledStatus(id2,ON);
  Dynamixel.moveRW(id2,512);
  delay(1000);
  Dynamixel.action();
  Dynamixel.ledStatus(id2,OFF);

    Dynamixel.move(id3,random(200,800));  // 200 to 800
  delay(1000);
  Dynamixel.moveSpeed(id3,random(200,800),random(200,800));
  delay(2000);
  Dynamixel.setEndless(id3,ON);
  Dynamixel.turn(id3,RIGTH,1000);
  delay(3000);
  Dynamixel.turn(id3,LEFT,1000);
  delay(3000);
  Dynamixel.setEndless(id3,OFF);
  Dynamixel.ledStatus(id3,ON);
  Dynamixel.moveRW(id3,512);
  delay(1000);
  Dynamixel.action();
  Dynamixel.ledStatus(id3,OFF);
 
delay(1000);
 
delay(1000);

}
