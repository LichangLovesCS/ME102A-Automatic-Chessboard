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


int change(String str1,String str2)
{
  int posx1 = 0;
  int posy1 = 0;
  int posx2 = 0;
  int posy2 = 0;

      switch(str1[0])
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
      switch(str1[1])
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
  int x = 0;
  int y = 0;
   while (0<1) {
    if (limitSwitchTop.touched() > 0){
        x = x+1;}
    if (limitSwitchTop.touched() == 0 && x<=7){
      steppery.move(-100);
      steppery.run();}
    else{
      break;}}
   while (0<1) {
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



    while (y < (t+200)){
      y = y+1;
      delay(1);
      stepperx.run();
      steppery.run();
      if (y == t){delay(500);
        myservo1.write(deg); delay(1000);}
    }
}


void knight(String str, int mark){
// str = "n" + "cp" + "moveto" + "prev pos"
String strx = "oo";
String stry = "oo";
int xpos[] = {0, 0};
int ypos[] = {0, 0};
strx[0] = str[1];
strx[1] = str[3];
stry[0] = str[2];
stry[1] = str[4];
int x = 0;
int y = 0;
for (int i = 0; i<2; i++){
    if (strx[i] == 'a'){
      xpos[i] = 1;}
    if (strx[i] == 'b'){
      xpos[i] = 2;}
    if (strx[i] == 'c'){
      xpos[i] = 3;}
    if (strx[i] == 'd'){
      xpos[i] = 4;}
    if (strx[i] == 'e'){
      xpos[i] = 5;}
    if (strx[i] == 'f'){
      xpos[i] = 6;}
    if (strx[i] == 'g'){
      xpos[i] = 7;}
    if (strx[i] == 'h'){
      xpos[i] = 8;}
    if (stry[i] == '1'){
      ypos[i] = 1;}
    if (stry[i] == '2'){
      ypos[i] = 2;}
    if (stry[i] == '3'){
      ypos[i] = 3;}
    if (stry[i] == '4'){
      ypos[i] = 4;}
    if (stry[i] == '5'){
      ypos[i] = 5;}
    if (stry[i] == '6'){
      ypos[i] = 6;}
    if (stry[i] == '7'){
      ypos[i] = 7;}
    if (stry[i] == '8'){
      ypos[i] = 8;}
}

int changex = xpos[1] - xpos[0];
int changey = ypos[1] - ypos[0];


Serial.println(changex);
Serial.println(changey);

if (mark == 0){myservo1.write(0); delay(500);}
if (mark == 0 && changex == -1 && changey == 2){
  stepperx.move(-100);}
if (mark == 0 && changex == -1 && changey == -2){
  stepperx.move(-100);}
if (mark == 0 && changex == -2 && changey == -1){
  steppery.move(100);}
if (mark == 0 && changex == 2 && changey == -1){            // step 1
  steppery.move(100);}
if (mark == 0 && changex == 1 && changey == 2){
  stepperx.move(100);}
if (mark == 0 && changex == 1 && changey == -2){
  stepperx.move(100);}
if (mark == 0 && changex == -2 && changey == 1){
  steppery.move(-100);}
if (mark == 0 && changex == 2 && changey == 1){
  steppery.move(-100);}

if (mark == 1 && changex == -1 && changey == 2){
  steppery.move(-400);}
if (mark == 1 && changex == 1 && changey == 2){
  steppery.move(-400);}
if (mark == 1 && changex == -1 && changey == -2){         //step 2
  steppery.move(400);}
if (mark == 1 && changex == 1 && changey == -2){
  steppery.move(400);}
if (mark == 1 && changex == -2 && changey == -1){
  stepperx.move(-400);}
if (mark == 1 && changex == -2 && changey == 1){
  stepperx.move(-400);}
if (mark == 1 && changex == 2 && changey == -1){
  stepperx.move(400);}
if (mark == 1 && changex == 2 && changey == 1){
  stepperx.move(400);}

if (mark == 2 && changex == -2 && changey == -1){
  steppery.move(100);}
if (mark == 2 && changex == 2 && changey == -1){
  steppery.move(100);}
if (mark == 2 && changex == 2 && changey == 1){         //step 3
  steppery.move(-100);}
if (mark == 2 && changex == -2 && changey == 1){
  steppery.move(-100);}
if (mark == 2 && changex == -1 && changey == 2){
  stepperx.move(-100);}
if (mark == 2 && changex == -1 && changey == -2){
  stepperx.move(-100);}
if (mark == 2 && changex == 1 && changey == 2){
  stepperx.move(100);}
if (mark == 2 && changex == 1 && changey == -2){
  stepperx.move(100);}

while (y < 500){
  y = y+1;
  delay(1);
  stepperx.run();
  steppery.run();}


if (mark == 2){delay(500); myservo1.write(70); delay(500);}

}
void removepiece(int direct, int stp){
  int y = 0;
  int lr = 0;
  if (direct < 100){lr = -1;}
  if (direct > 100){lr = 1;}
  Serial.println(lr);
  if (stp == 1){steppery.move(-100);}

  if (stp == 2){stepperx.moveTo(direct);}

  if (stp == 3){steppery.moveTo(direct);}

  if (stp == 4){stepperx.move(55 * lr);}

  while (y < 1500){
  y = y+1;
  delay(1);
  stepperx.run();
  steppery.run();}

}
void loop()
{
    String str;
    String str1 = "oo";
    String str2 = "oo";
    String str3 = "oo";
    int t1 = 0;
    int t2 = 0;
    int val = 0;
    String Pos = "0000";
    int posint = 0;
    if(Serial.available() > 0)
    {
        str = Serial.readStringUntil('\n');
        Serial.println(str);
        str1[0] = str[1];
        str1[1] = str[2];
        str2[0] = str[3];
        str2[1] = str[4];
        str3[0] = str[5];
        str3[1] = str[6];}
        if (str[0] == 'n' && str.length() == 7){
          movepiece(str1, 0, 2500);
          delay(200);
          knight(str, 0); //step1
          delay(200);
          knight(str, 1); //step2
          delay(200);
          knight(str, 2); //step3
          }
        else if (str[5] == 'o'){
        t1 = change(str1, str2);
        movepiece(str1, 0, 2500);
        movepiece(str2, 90, t1);}
        else if (str.length() == 7){
        t1 = change(str1, str3);
        t2 = change(str1, str2);
        movepiece(str1, 0, t1);
        movepiece(str2, 90, t2);}
        else if (str == "cent"){center();}


        else if (str.length() == 13 && str[12] == 'x' && str[0] == 'n'){
        myservo1.write(90);
        t1 = change(str1, str3);
        t2 = change(str1, str2);
        movepiece(str2, 0, t1);
        Pos = str.substring(8,12);
        posint = Pos.toInt();
        if (str[7] == 'b'){val = 55;}
        else if (str[7] == 'w'){val = 1565;}
        removepiece(val, 1);
        removepiece(val, 2);
        removepiece(posint, 3);
        removepiece(val, 4);
        myservo1.write(90);
        delay(500);
        movepiece(str1, 0, 2500);
        delay(500);
        knight(str, 0); //step1
        delay(200);
        knight(str, 1); //step2
        delay(200);
        knight(str, 2); //step3
        myservo1.write(90);}


        else if (str.length() == 13 && str[12] == 'x'){
        myservo1.write(90);
        t1 = change(str1, str3);
        t2 = change(str1, str2);
        movepiece(str2, 0, t1);
        Pos = str.substring(8,12);
        posint = Pos.toInt();
        if (str[7] == 'b'){val = 55;}
        else if (str[7] == 'w'){val = 1565;}
        removepiece(val, 1);
        removepiece(val, 2);
        removepiece(posint, 3);
        removepiece(val, 4);
        myservo1.write(90);
        delay(500);
        movepiece(str1, 0, 2500); 
        movepiece(str2, 0, t2);
        myservo1.write(90);}
}
