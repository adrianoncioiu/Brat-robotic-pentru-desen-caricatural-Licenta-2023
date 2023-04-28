#include "AX12A.h"
#define DirectionPin   (10u)
#define BaudRate      (1000000ul)
#define ID        (1u)
#define L1 (0.0935f)
#define L2 (0.118f)
#define RAD2DEG (57.2974F)
#define DEG2DIGITAL (3.4133F)
#define L1_OFFSET (205u)
#define L2_OFFSET (512u)
#define JOINT_1 (16u) // 16
#define JOINT_2 (11u)  // 8
#define JOINT_3 (6u) // 15
#define DISCRETIZARE (2u)
#define SCALEWIDTH (1)
#define SCALEHEIGHT (1.5)
#define LETTERSIZE (0.01)
#define SPACESIZE (0.005)
#define POSITON_TOLLERANCE 5
#define JOINTSPEED (500)
#define LINESPACE (0.005)

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
void drawLine (float xs, float ys, float xf, float yf);
void drawLitera (char c, point &anchor);
void drawText (char *s, point &anchor);


void setup() {
  ax12a.begin(BaudRate, DirectionPin, &Serial);
}

void loop() {
  point anchor;
  anchor.x = 0.00;
  anchor.y = 0.13;
  //drawText ((char*)"MESOTA", anchor);
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

void goToPoint (float xe, float ye)
{
  postura post;
  post = calcPostura(xe, ye);
  postura postCurr;
  ax12a.moveSpeed (JOINT_1, post.q1, JOINTSPEED);
  ax12a.moveSpeed (JOINT_2, post.q2, JOINTSPEED);
  do{
    postCurr = readCurrentPosture();
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
  postura post;
  post = calcPostura(L1+L2, 0);
  ax12a.moveSpeed (JOINT_1, post.q1, JOINTSPEED);
  ax12a.moveSpeed (JOINT_2, post.q2, JOINTSPEED);
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
void drawLine (float xs, float ys, float xf, float yf)
{
  goToPoint (xs, ys);
  pencilDown();
  point traiectorie [DISCRETIZARE];
  for (int i=0 ; i<= DISCRETIZARE ; i++)
  {
    float dx = xf - xs;
    float dy = yf - ys;
    float pasx = dx / (float)DISCRETIZARE;
    float pasy = dy / (float)DISCRETIZARE;
    traiectorie[i].x = xs + pasx * i;
    traiectorie[i].y = ys + pasy * i;  
    goToPoint (traiectorie[i].x,traiectorie[i].y);
  }
  pencilUp();
}

