#include "AX12A.h"
#define DirectionPin   (10u)
#define BaudRate      (1000000ul)
#define ID        (1u)
#define L1 (0.0935f)
#define L2 (0.183f)
#define RAD2DEG (57.2974F)
#define DEG2DIGITAL (3.4133F)
#define L1_OFFSET (205u)
#define L2_OFFSET (512u)
#define JOINT_1 (16u) // 16
#define JOINT_2 (11u)  // 8
//#define JOINT_3 (6u) // 15
#define DISCRETIZARE (2u)
#define SCALEWIDTH (1)
#define SCALEHEIGHT (1.5)
#define LETTERSIZE (0.01)
#define SPACESIZE (0.005)
#define POSITON_TOLLERANCE 5
#define JOINTSPEED (50)
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
//void pencilUp ();
//void pencilDown ();
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
  drawText ((char*)"GGO", anchor);
  //drawLine(anchor.x + 0.5*SCALEWIDTH,anchor.y + 0.005*SCALEHEIGHT,anchor.x + 0.11*SCALEWIDTH,anchor.y + 0.015*SCALEHEIGHT);
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
    result = true;
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
/*void pencilUp ()
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
}*/
void drawLine (float xs, float ys, float xf, float yf)
{
  goToPoint (xs, ys);
  //pencilDown();
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
  //pencilUp();
}
void drawLitera (char c, point &anchor)
{
  
  switch (c)
  {
    case 'A':
        drawLine(anchor.x + 0.0*SCALEWIDTH,anchor.y + 0.0*SCALEHEIGHT,anchor.x + 0.005*SCALEWIDTH,anchor.y + 0.01*SCALEHEIGHT);
        drawLine(anchor.x + 0.005*SCALEWIDTH,anchor.y + 0.01*SCALEHEIGHT,anchor.x + 0.01*SCALEWIDTH,anchor.y + 0.00*SCALEHEIGHT);
        drawLine(anchor.x + 0.0*SCALEWIDTH,anchor.y + 0.005*SCALEHEIGHT,anchor.x + 0.01*SCALEWIDTH,anchor.y + 0.005*SCALEHEIGHT);
        break;
    case 'B': 
            drawLine(anchor.x + 0.0 * SCALEWIDTH, anchor.y + 0.0 * SCALEHEIGHT, anchor.x + 0.0 * SCALEWIDTH , anchor.y + 0.01*SCALEHEIGHT);
            drawLine(anchor.x + 0.0 * SCALEWIDTH, anchor.y + 0.01 * SCALEHEIGHT, anchor.x + 0.01 * SCALEWIDTH , anchor.y + 0.01*SCALEHEIGHT);
            drawLine(anchor.x + 0.01* SCALEWIDTH, anchor.y + 0.01 * SCALEHEIGHT, anchor.x + 0.01 * SCALEWIDTH , anchor.y + 0.005*SCALEHEIGHT);
            drawLine(anchor.x + 0.01 * SCALEWIDTH, anchor.y + 0.005 * SCALEHEIGHT, anchor.x + 0.0 * SCALEWIDTH , anchor.y + 0.005*SCALEHEIGHT);
            drawLine(anchor.x + 0.01 * SCALEWIDTH, anchor.y + 0.005 * SCALEHEIGHT, anchor.x + 0.01 * SCALEWIDTH , anchor.y + 0.0*SCALEHEIGHT);
            drawLine(anchor.x + 0.01 * SCALEWIDTH, anchor.y + 0.0 * SCALEHEIGHT, anchor.x + 0.0 * SCALEWIDTH , anchor.y + 0.0*SCALEHEIGHT);
            break; 
    case 'C':
            drawLine(anchor.x + (0.01 * SCALEWIDTH), anchor.y + (0.01*SCALEHEIGHT), anchor.x + (0.0 * SCALEWIDTH), anchor.y + (0.01 * SCALEHEIGHT));
            drawLine(anchor.x + (0.0 * SCALEWIDTH), anchor.y + (0.01*SCALEHEIGHT), anchor.x + (0.0 * SCALEWIDTH), anchor.y + (0.0 * SCALEHEIGHT));
            drawLine(anchor.x + (0.0 * SCALEWIDTH), anchor.y + (0.0*SCALEHEIGHT), anchor.x + (0.01 * SCALEWIDTH), anchor.y + (0.0 * SCALEHEIGHT));
            break;  
    case 'D':
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT),anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT));
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT),anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT));
            drawLine(anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT),anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT));
            break;
    case 'E':
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT),anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT));
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT),anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT));
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT),anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT));
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.005*SCALEHEIGHT),anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.005*SCALEHEIGHT));
            break;
    case 'F':
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT),anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT));
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT),anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT));
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.007*SCALEHEIGHT),anchor.x+(0.007*SCALEWIDTH),anchor.y+(0.005*SCALEHEIGHT));     
            break;  
    case 'G':
            drawLine(anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT),anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT));
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT),anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT));
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT),anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT));
            drawLine(anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT),anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.005*SCALEHEIGHT));
            drawLine(anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.005*SCALEHEIGHT),anchor.x+(0.003*SCALEWIDTH),anchor.y+(0.005*SCALEHEIGHT));
            break;  
    case 'H':
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT),anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT));
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.005*SCALEHEIGHT),anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.005*SCALEHEIGHT));
            drawLine(anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT),anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT));
            break; 
    case 'I':
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT),anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT));
            anchor.x -= SCALEWIDTH*LETTERSIZE;
            break;
    case 'J': 
            drawLine(anchor.x+(0.007*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT),anchor.x+(0.007*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT));
            drawLine(anchor.x+(0.007*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT),anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT));
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT),anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.003*SCALEHEIGHT));
            break; 
    case 'K':
        drawLine(anchor.x + 0.0*SCALEWIDTH,anchor.y + 0.0*SCALEHEIGHT,anchor.x + 0.0*SCALEWIDTH,anchor.y + 0.01*SCALEHEIGHT);
        drawLine(anchor.x + 0.0*SCALEWIDTH,anchor.y + 0.005*SCALEHEIGHT,anchor.x + 0.005*SCALEWIDTH,anchor.y + 0.01*SCALEHEIGHT);
        drawLine(anchor.x + 0.0*SCALEWIDTH,anchor.y + 0.005*SCALEHEIGHT,anchor.x + 0.005*SCALEWIDTH,anchor.y + 0.0*SCALEHEIGHT);
        break;
    case 'L': 
        drawLine(anchor.x + 0.0 * SCALEWIDTH, anchor.y + 0.01 * SCALEHEIGHT, anchor.x + 0.0 * SCALEWIDTH , anchor.y + 0.0*SCALEHEIGHT);
        drawLine(anchor.x + 0.0 * SCALEWIDTH, anchor.y + 0.0 * SCALEHEIGHT, anchor.x + 0.01 * SCALEWIDTH , anchor.y + 0.0*SCALEHEIGHT);
        break;
    case 'M':
           drawLine(anchor.x + (SCALEWIDTH * 0.00),anchor.y + (SCALEHEIGHT * 0.00),anchor.x +(SCALEWIDTH * 0.00),anchor.y +(SCALEHEIGHT * 0.01));
           drawLine(anchor.x + (SCALEWIDTH * 0.00),anchor.y + (SCALEHEIGHT * 0.01),anchor.x +(SCALEWIDTH * 0.005),anchor.y +(SCALEHEIGHT * 0.005));
           drawLine(anchor.x + (SCALEWIDTH * 0.005),anchor.y + (SCALEHEIGHT * 0.005),anchor.x +(SCALEWIDTH * 0.01),anchor.y +(SCALEHEIGHT * 0.01));
           drawLine(anchor.x + (SCALEWIDTH * 0.01),anchor.y + (SCALEHEIGHT * 0.01),anchor.x +(SCALEWIDTH * 0.01),anchor.y +(SCALEHEIGHT * 0.00));
           break;   
     case 'N':
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT),anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT));
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT),anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT));
            drawLine(anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT),anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT));
            break;
    case 'O': 
            drawLine(anchor.x + 0.0 * SCALEWIDTH, anchor.y + 0.0 * SCALEHEIGHT, anchor.x + 0.0 * SCALEWIDTH , anchor.y + 0.01*SCALEHEIGHT);
            drawLine(anchor.x + 0.0 * SCALEWIDTH, anchor.y + 0.01 * SCALEHEIGHT, anchor.x + 0.01 * SCALEWIDTH , anchor.y + 0.01*SCALEHEIGHT);
            drawLine(anchor.x + 0.01 * SCALEWIDTH, anchor.y + 0.01 * SCALEHEIGHT, anchor.x + 0.01 * SCALEWIDTH , anchor.y + 0.0*SCALEHEIGHT);
            drawLine(anchor.x + 0.01 * SCALEWIDTH, anchor.y + 0.0 * SCALEHEIGHT, anchor.x + 0.0 * SCALEWIDTH , anchor.y + 0.0*SCALEHEIGHT);
            break;
    case 'P': 
            drawLine(anchor.x + 0.0 * SCALEWIDTH, anchor.y + 0.0 * SCALEHEIGHT, anchor.x + 0.0 * SCALEWIDTH , anchor.y + 0.01*SCALEHEIGHT);
            drawLine(anchor.x + 0.0 * SCALEWIDTH, anchor.y + 0.01 * SCALEHEIGHT, anchor.x + 0.01 * SCALEWIDTH , anchor.y + 0.01*SCALEHEIGHT);
            drawLine(anchor.x + 0.01* SCALEWIDTH, anchor.y + 0.01 * SCALEHEIGHT, anchor.x + 0.01 * SCALEWIDTH , anchor.y + 0.005*SCALEHEIGHT);
            drawLine(anchor.x + 0.01 * SCALEWIDTH, anchor.y + 0.005 * SCALEHEIGHT, anchor.x + 0.0 * SCALEWIDTH , anchor.y + 0.005*SCALEHEIGHT);
            break;
    case 'Q': drawLine(anchor.x + (0 * SCALEWIDTH) ,anchor.y + (0 * SCALEHEIGHT),anchor.x + (0.007 * SCALEWIDTH),anchor.y + (0 * SCALEHEIGHT)); 
             drawLine(anchor.x + (0.007 * SCALEWIDTH) ,anchor.y + (0 * SCALEHEIGHT),anchor.x + (0.01 * SCALEWIDTH),anchor.y + (0.003 * SCALEHEIGHT)); 
             drawLine(anchor.x + (0.01 * SCALEWIDTH) ,anchor.y + (0.003 * SCALEHEIGHT),anchor.x + (0.01 * SCALEWIDTH),anchor.y + (0.01 * SCALEHEIGHT)); 
             drawLine(anchor.x + (0.01 * SCALEWIDTH) ,anchor.y + (0.01 * SCALEHEIGHT),anchor.x + (0 * SCALEWIDTH),anchor.y + (0.01 * SCALEHEIGHT));
             drawLine(anchor.x + (0 * SCALEWIDTH) ,anchor.y + (0.01 * SCALEHEIGHT),anchor.x + (0 * SCALEWIDTH),anchor.y + (0 * SCALEHEIGHT));
             drawLine(anchor.x + (0.005 * SCALEWIDTH) ,anchor.y + (0.005 * SCALEHEIGHT),anchor.x + (0.01 * SCALEWIDTH),anchor.y + (0 * SCALEHEIGHT));
             break;
    case 'R': 
            drawLine(anchor.x + 0.0 * SCALEWIDTH, anchor.y + 0.0 * SCALEHEIGHT, anchor.x + 0.0 * SCALEWIDTH , anchor.y + 0.01*SCALEHEIGHT);
            drawLine(anchor.x + 0.0 * SCALEWIDTH, anchor.y + 0.01 * SCALEHEIGHT, anchor.x + 0.01 * SCALEWIDTH , anchor.y + 0.01*SCALEHEIGHT);
            drawLine(anchor.x + 0.01* SCALEWIDTH, anchor.y + 0.01 * SCALEHEIGHT, anchor.x + 0.01 * SCALEWIDTH , anchor.y + 0.005*SCALEHEIGHT);
            drawLine(anchor.x + 0.01 * SCALEWIDTH, anchor.y + 0.005 * SCALEHEIGHT, anchor.x + 0.0 * SCALEWIDTH , anchor.y + 0.005*SCALEHEIGHT);
            drawLine(anchor.x + 0.0 * SCALEWIDTH, anchor.y + 0.005 * SCALEHEIGHT, anchor.x + 0.01 * SCALEWIDTH , anchor.y + 0.0*SCALEHEIGHT);
            break;
    case 'S':
            drawLine(anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT),anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT));
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT),anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.005*SCALEHEIGHT));
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.005*SCALEHEIGHT),anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.005*SCALEHEIGHT));
            drawLine(anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.005*SCALEHEIGHT),anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT));
            drawLine(anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT),anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT));
            break;
    case 'T':
        drawLine(anchor.x + 0.0*SCALEWIDTH,anchor.y + 0.01*SCALEHEIGHT,anchor.x + 0.01*SCALEWIDTH,anchor.y + 0.01*SCALEHEIGHT);
        drawLine(anchor.x + 0.005*SCALEWIDTH,anchor.y + 0.01*SCALEHEIGHT,anchor.x + 0.005*SCALEWIDTH,anchor.y + 0.00*SCALEHEIGHT);
        break;                     
    case 'U':
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT),anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT));
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT),anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT));
            drawLine(anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT),anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT));
            break;
    case 'V':
            drawLine(anchor.x+(0.0*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT),anchor.x+(0.005*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT));
            drawLine(anchor.x+(0.005*SCALEWIDTH),anchor.y+(0.00*SCALEHEIGHT),anchor.x+(0.01*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT));
            break;
    case 'W': drawLine(anchor.x + (0 * SCALEWIDTH) ,anchor.y + (0.01 * SCALEHEIGHT),anchor.x + (0.003 * SCALEWIDTH),anchor.y + (0 * SCALEHEIGHT)); 
             drawLine(anchor.x + (0.003 * SCALEWIDTH) ,anchor.y + (0 * SCALEHEIGHT),anchor.x + (0.006 * SCALEWIDTH),anchor.y + (0.01 * SCALEHEIGHT)); 
             drawLine(anchor.x + (0.003 * SCALEWIDTH) ,anchor.y + (0.01 * SCALEHEIGHT),anchor.x + (0.006 * SCALEWIDTH),anchor.y + (0 * SCALEHEIGHT)); 
             drawLine(anchor.x + (0.006 * SCALEWIDTH) ,anchor.y + (0 * SCALEHEIGHT),anchor.x + (0.009 * SCALEWIDTH),anchor.y + (0.01 * SCALEHEIGHT));
             break;
    case 'X': 
             drawLine(anchor.x + (0 * SCALEWIDTH) ,anchor.y + (0 * SCALEHEIGHT),anchor.x + (0.01 * SCALEWIDTH),anchor.y + (0.01 * SCALEHEIGHT));
             drawLine(anchor.x + (0 * SCALEWIDTH) ,anchor.y + (0.01 * SCALEHEIGHT),anchor.x + (0.01 * SCALEWIDTH),anchor.y + (0 * SCALEHEIGHT));
             break;
    case 'Y': 
             drawLine(anchor.x + (0.005 * SCALEWIDTH) ,anchor.y + (0 * SCALEHEIGHT),anchor.x + (0.005 * SCALEWIDTH),anchor.y + (0.005 * SCALEHEIGHT));
             drawLine(anchor.x + (0.005 * SCALEWIDTH) ,anchor.y + (0.005 * SCALEHEIGHT),anchor.x + (0 * SCALEWIDTH),anchor.y + (0.01 * SCALEHEIGHT));
             drawLine(anchor.x + (0.005 * SCALEWIDTH) ,anchor.y + (0.005 * SCALEHEIGHT),anchor.x + (0.01 * SCALEWIDTH),anchor.y + (0.01 * SCALEHEIGHT));
             break;
    
    case ' ':
            anchor.x -= SCALEWIDTH*SPACESIZE;
            break;
    
   
    
          
    case '!':
            drawLine(anchor.x+(0.005*SCALEWIDTH),anchor.y+(0.0*SCALEHEIGHT),anchor.x+(0.005*SCALEWIDTH),anchor.y+(0.01*SCALEHEIGHT));
            drawLine(anchor.x+(0.005*SCALEWIDTH),anchor.y+(-0.009*SCALEHEIGHT),anchor.x+(0.005*SCALEWIDTH),anchor.y+(0.00*SCALEHEIGHT));
            anchor.x -= SCALEWIDTH*LETTERSIZE;
            break; 
      
    case '\n':
            anchor.y = anchor.y + SCALEHEIGHT*LINESPACE;
            break;
     
    default:
        break;
  }
  anchor.x = anchor.x + SCALEWIDTH*(LETTERSIZE + SPACESIZE);
  
}
void drawText (char s[], point &anchor)
{
   for(int i=0;i<strlen(s);i++)
   {
    drawLitera(s[i], anchor);
   }
}
