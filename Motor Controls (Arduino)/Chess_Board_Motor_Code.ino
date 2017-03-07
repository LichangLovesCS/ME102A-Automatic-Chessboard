#include "MeOrion.h"
#include <SoftwareSerial.h>

MeStepper stepperx(PORT_1);
MeStepper steppery(PORT_2); 
MePort updown(PORT_7);
Servo myservo1;
int16_t servo1pin =  updown.pin2();  
MeLimitSwitch limitSwitchBot(PORT_3,SLOT_1);
MeLimitSwitch limitSwitchTop(PORT_3,SLOT_2);
MeLimitSwitch limitSwitchLeft(PORT_6,SLOT_2);
MeLimitSwitch limitSwitchRight(PORT_6,SLOT_1);


void setup()
{  
  Serial.begin(9600);
  Serial.println("Start.");
  // Change these to suit your stepper if you want
  stepperx.setMaxSpeed(1000);
  stepperx.setAcceleration(20000);
  steppery.setMaxSpeed(1000);
  steppery.setAcceleration(20000);
  myservo1.attach(servo1pin);
}

int change(String str,String str2)
{
  int posx1 = 0;
  int posy1 = 0;
  int posx2 = 0;
  int posy2 = 0;

      switch(str[0])
    {
      case 'a':
      posx1 = 0;
      break;
      case 'b':
      posx1 = 400;
      break;
      case 'c':
      posx1 = 800;
      break;
      case 'd':
      posx1 = 1200;
      break;
      case 'e':
      posx1 = 1600;
      break;
      case 'f':      
      posx1 = 2000;
      break;
      case 'g':
      posx1 = 2400;
      break;
      case 'h':
      posx1 = 2800;
      break;
    }
      switch(str[1])
    {
      case '1':
      posy1 = 300;
      break;
      case '2':
      posy1 = 600;
      break;
      case '3':
      posy1 = 900;
      break;
      case '4':
      posy1 = 1200;
      break;
      case '5':
      posy1 = 1500;
      break;
      case '6':      
      posy1 = 1800;
      break;
      case '7':
      posy1 = 2100;
      break;
      case '8':
      posy1 = 2400;
      break;
    }
      switch(str2[0])
    {
      case 'a':
      posx2 = 300;
      break;
      case 'b':
      posx2 = 600;
      break;
      case 'c':
      posx2 = 900;
      break;
      case 'd':
      posx2 = 1200;
      break;
      case 'e':
      posx2 = 1500;
      break;
      case 'f':      
      posx2 = 1800;
      break;
      case 'g':
      posx2 = 2100;
      break;
      case 'h':
      posx2 = 2400;
      break;
    }
      switch(str2[1])
    {
      case '1':
      posy2 = 300;
      break;
      case '2':
      posy2 = 600;
      break;
      case '3':
      posy2 = 900;
      break;
      case '4':
      posy2 = 1200;
      break;
      case '5':
      posy2 = 1500;
      break;
      case '6':      
      posy2 = 1800;
      break;
      case '7':
      posy2 = 2100;
      break;
      case '8':
      posy2 = 2400;
      break;
    }

  int dx1 = abs(posx1-posx2);
  int dy1 = abs(posy1-posy2);
  Serial.println(dx1);
  Serial.println(dy1);
  int t1 = sqrt(pow(dx1,2)+pow(dy1,2));
  return t1;   
}


void center()
{   
   while (0<1) {
    int x = 0;
    if (limitSwitchTop.touched() > 0){
        x = x+1;}
    if (limitSwitchTop.touched() == 0 && x<=7){
      steppery.move(-100);
      steppery.run();}
    else{
      break;}}
   while (0<1) {
    int y = 0;
    if (limitSwitchLeft.touched() > 0){
        y = y+1;}
    if (limitSwitchLeft.touched() == 0 && y<=7){
      stepperx.move(-100);
      stepperx.run();}
    else
      break;
}}

void movepiece(String x, int deg, int t){
  int y = 0;
    switch(x[0])
    {
      case 'a':
      stepperx.moveTo(110);
      break;
      case 'b':
      stepperx.moveTo(310);
      break;
      case 'c':
      stepperx.moveTo(510);
      break;
      case 'd':
      stepperx.moveTo(710);
      break;
      case 'e':
      stepperx.moveTo(910);
      break;
      case 'f':      
      stepperx.moveTo(1110);
      break;
      case 'g':
      stepperx.moveTo(1310);
      break;
      case 'h':
      stepperx.moveTo(1510);
      break;
    }
      switch(x[1])
    {
      case '1':
      steppery.moveTo(1750);
      break;
      case '2':
      steppery.moveTo(1550);
      break;
      case '3':
      steppery.moveTo(1350);
      break;
      case '4':
      steppery.moveTo(1150);
      break;
      case '5':
      steppery.moveTo(950);
      break;
      case '6':      
      steppery.moveTo(750);
      break;
      case '7':
      steppery.moveTo(550);
      break;
      case '8':
      steppery.moveTo(350);
      break;
    }


    
    while (y < t){
      y = y+1; 
      delay(1);
      stepperx.run(); 
      steppery.run();
      if (y == t-400){ 
        myservo1.write(deg);}
    }
}

void loop() 
{
    String str;
    String str2 = "oo";
    int t1 = 0;
    if(Serial.available() > 0)
    {
        str = Serial.readStringUntil('\n');
        str2[0] = str[2];
        str2[1] = str[3]; 
        t1 = change(str, str2);}

        
    if (str == "center"){center();}
    if (str.length() == 4){
      movepiece(str, 0, 2500);      
      movepiece(str2, 90, t1);}
}                    



 

