#include "AX12A.h"
#define DirectionPin   (10u)
#define BaudRate      (1000000ul)
#define L1 (0.0935f)
#define L2 (0.150f)
#define RAD2DEG (57.2974F)
#define DEG2DIGITAL (3.4133F)
#define L1_OFFSET (205)
#define L2_OFFSET (512)
#define JOINT_1 (7u) 
#define JOINT_2 (11u) 
#define JOINT_3 (1u)
#define POSITON_TOLLERANCE 5
#define JOINTSPEED (150)

struct postura 
{
  int q1;
  int q2;
};
struct point
{
  float x;
  float y;
};
void pencilUp ();
void pencilDown ();
void goToBase ();
void goToPoint (float xe, float ye);
postura calcPostura (float xe, float ye);



void setup() {
  ax12a.begin(BaudRate, DirectionPin, &Serial1);
  ax12a.setAngleLimit(JOINT_1, 50, 973);
  ax12a.setAngleLimit(JOINT_2, 50, 973);

  goToBase();
  delay(1000);
  pencilDown ();
  pencilUp ();

  delay (3000);
  
}

void loop() {

	goToPoint(-0.02,-0.13);
  goToPoint(-0.12,-0.16);

  goToBase();
  delay (3000);
}

postura calcPostura (float xe, float ye)
{
   postura post;
   float L = sqrt(xe*xe + ye*ye);
   post.q1 = (int)((atan(ye/xe) - acos( (L2*L2 - L*L - L1*L1)/(-2.f*L1*L)))*RAD2DEG*DEG2DIGITAL);
   post.q2 = (int)(acos((L*L - L1*L1 - L2*L2)/(2.f*L1*L2))*RAD2DEG*DEG2DIGITAL);
   post.q1 = post.q1 + L1_OFFSET;
   post.q2 = post.q2 + L2_OFFSET;
   return post;
   
}

void pencilUp ()
{
  ax12a.moveSpeed (JOINT_3, 650, JOINTSPEED);
  int currPos = 0;
  do{
    currPos = ax12a.readPosition(JOINT_3);
  }while(!(currPos >= (650 - POSITON_TOLLERANCE) && currPos <= (650 + POSITON_TOLLERANCE)));
}
void pencilDown ()
{
  ax12a.moveSpeed (JOINT_3, 512, JOINTSPEED);
    int currPos = 0;
  do{
    currPos = ax12a.readPosition(JOINT_3);
  }while(!(currPos >= (512 - POSITON_TOLLERANCE) && currPos <= (512 + POSITON_TOLLERANCE)));
}

void goToPoint(float xe, float ye)
{
  
  postura post;
  post = calcPostura(xe, ye);
  postura postCurr;
  ax12a.moveSpeed(JOINT_1, post.q1, JOINTSPEED);
  ax12a.moveSpeed(JOINT_2, post.q2, JOINTSPEED);
  delay(2000);
  pencilDown();
  delay(1000);
  pencilUp();
  delay(1000);

  
/*  Serial.print("Going to point (");
  Serial.print(xe);
  Serial.print(", ");
  Serial.print(ye);
  Serial.println(")");
*/
  do {
    postCurr = readCurrentPosture();

    Serial.print("Current posture: (");
    Serial.print(postCurr.q1);
    Serial.print(", ");
    Serial.print(postCurr.q2);
    Serial.println(")");

      }while(!isPostureReach(postCurr.q1,postCurr.q2,post.q1,post.q2));
}

postura readCurrentPosture(){
  postura tempPost;
  tempPost.q1 = ax12a.readPosition(JOINT_1);
  tempPost.q2 = ax12a.readPosition(JOINT_2);
  return tempPost;
}

bool isPostureReach(int currq1, int currq2, int finishq1, int finishq2){
  bool result = false;
  if(currq1 >= (finishq1 - POSITON_TOLLERANCE) && currq1 <= (finishq1 + POSITON_TOLLERANCE) &&
  currq2 >= (finishq2 - POSITON_TOLLERANCE) && currq2 <= (finishq2 + POSITON_TOLLERANCE))
   {
    result=true;
   }
   else
   {
    result = false;
   }
  return result;
}

void goToBase ()
{
  pencilUp();
  postura post;
  post = calcPostura(L1+L2, 0);
  ax12a.moveSpeed (JOINT_1, post.q1, JOINTSPEED);
  ax12a.moveSpeed (JOINT_2, post.q2, JOINTSPEED);
}


