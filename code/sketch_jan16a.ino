//﻿Digital Arduino Clock Code

// this code orginally wrote by plouc68000 on https://www.hackster.io/plouc68000/simplest-uno-digital-clock-ever-4613aa 
// and edited omn some part for my own use
// note that you should use Potentiometer for pin3 of lcd (V0) and you may have adjust your constrast for better output



#include "LiquidCrystal.h"

// This defines the LCD wiring to the DIGITALpins
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// initial Time display is 12:59:45 PM
int h=12;
int m=59;
int s=45;
int flag=1; //PM

// Time Set Buttons
int button1;
int button2;
int hs=8;// pin 8 for Hours Setting
int ms=9;// pin 9 for Minutes Setting

// Digital LCD Constrast setting
int cs=6;// pin 5 for contrast PWM
static int contrast=100;// default contrast

// For accurate Time reading, use Arduino Real Time Clock
static uint32_t last_time, now = 0; // RTC


void setup()
{
  lcd.begin(16,2);
  pinMode(hs,INPUT_PULLUP);
  pinMode(ms,INPUT_PULLUP);
  
  now=millis(); // read RTC initial value
  analogWrite(cs,contrast);
}


void loop()
{ 
// Update LCD Display
// Print TIME in Hour, Min, Sec + AM/PM
 lcd.setCursor(0,0);
 lcd.print("Time ");
 if(h<10)lcd.print("0");// always 2 digits
 lcd.print(h);
 lcd.print(":");
 if(m<10)lcd.print("0");
 lcd.print(m);
 lcd.print(":");
 if(s<10)lcd.print("0");
 lcd.print(s);

 if(flag==0) lcd.print(" AM");
 if(flag==1) lcd.print(" PM");
 
 lcd.setCursor(0,1);// for Line 2
 lcd.print("AKIAU uni");

// improved replacement of delay(1000) 
// Much better accuracy, no more dependant of loop execution time
 
 while ((now-last_time) < 1000 ) // wait1000ms
 {
  now=millis();
 }

 last_time=now; // prepare for next loop 
 s=s+1; //increment sec. counting
// lcd.clear(); not needed



/*-------Time setting-------*/
 button1=digitalRead(hs);
 if(button1==0) h=h+1;

// debug contrast
//if(button1==0)  contrast=contrast+10;
//if (contrast==260) contrast=250;// contrast max 250

button2=digitalRead(ms);
// debug contrast
//if(button2==0) contrast=contrast-10;
//if (contrast==0) contrast=10;// contrast min 10
 
analogWrite(cs,contrast); // update contrast

if(button2==0){
 s=0;
 m=m+1;
 }


/* ---- manage seconds, minutes, hours am/pm overflow ----*/
 if(s==60){
  s=0;
  m=m+1;
 }
 if(m==60)
 {
  m=0;
  h=h+1;
 }
 if(h==13)
 {
  h=1;
  flag=flag+1;
  if(flag==2)flag=0;
 }
 
// Loop end
}
