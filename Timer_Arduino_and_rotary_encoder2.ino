

//Designed by Stoica Tudor 07.2019  Rew 08.2019
//"Programable Timer" from 99 hours to 0.
// Possibility to memorize preset time.
// Rotary encoder.

// include the library code:
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
// LiquidCrystal (RS, E, D4,D5,D6,D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


long n=0;// time in seconds
long r1=0;//rest1
long r2=0;
int r3=0;
int r4=0;
byte zh=0;//hoursX10
byte zhi;//hoursX10 initial
byte h=0;//hours
byte hi;
byte zm=0;//minutesX10
byte zmi;
byte m=0;//minutes
byte mi;
byte zs=0;//secX10
byte zsi;
byte s=0;//sec.
byte si;
byte md;// modulo
int counter=0;

void setup() {
   lcd.begin(16, 2);
   pinMode(A3, INPUT_PULLUP);//button "Memory" to ground
   pinMode(A2, INPUT_PULLUP);//SW Left to ground
   pinMode(A1, INPUT_PULLUP);//Rot enc B to ground
   pinMode(A0, INPUT_PULLUP);//Rot enc A to ground
   pinMode(9, OUTPUT);// OUT relay
   pinMode(10, OUTPUT);// OUT buzzer
   
// welcome message
  lcd.clear();
  lcd.display();
 lcd.print("    HELLO !");
  delay(1000);
  
}

void loop() {
 
  //  preset timer routine
  md=10;// set s.
  lcd.clear();
  lcd.print("Set t:         _");
  lcdpr();
  do{
  s=roTen(); 
  lcdpr();
   }while(digitalRead(A2)==HIGH);//"Left" button
  delay(10);
  counter=0;
 
  
  md=6;// set sX10
   lcd.clear();
  lcd.print("Set t:        _");
  lcdpr();
  do{  
 zs= roTen();
 lcdpr();
 }while(digitalRead(A2)==HIGH);
  delay(10);
  counter=0;
 
  
  md=10;// set min.
   lcd.clear();
  lcd.print("Set t:      _");
  lcdpr();
  do{ 
 m= roTen();
 lcdpr();
 }while(digitalRead(A2)==HIGH);
 delay(10);
 counter=0;
 
  
  md=6;// set min.X10
  lcd.clear();
  lcd.print("Set t:     _");
  lcdpr();
  do{
  zm= roTen();
  lcdpr();
  }while(digitalRead(A2)==HIGH);
  delay(10);
  counter=0;
  
  
  md=5;// set h
  lcd.clear();
  lcd.print("Set t:   _");
  lcdpr();
  do{//
  h= roTen();
  lcdpr();
  }while(digitalRead(A2)==HIGH);
  delay(10);
  counter=0;
  
  
  md=3;//set hX10;
   lcd.clear();
  lcd.print("Set t:  _");
  lcdpr();
  do{
  zh= roTen();
  lcdpr();
 }while(digitalRead(A2)==HIGH);
  delay(10);
  counter=0;
  
    //out of set routine
    
   si=s;   // memory initial state
   zsi=zs;
   mi=m;
   zmi=zm;
   hi=h;
   zhi=zh;
    
    n=36000*zh+3600*h+600*zm+60*m+zs*10+s;//compute time in sec.
    
     if(n!=0){   //not setting
      
  do{//Memory
    
   s=si;
   zs=zsi;
   m=mi;
   zm=zmi;
   h=hi;
   zh=zhi;
  
   n=36000*zh+3600*h+600*zm+60*m+zs*10+s;//compute time in sec.
   
    //Display set time
    
  lcd.clear();
  lcd.print("Remain: hh mm ss");  
  lcd.setCursor(8,1);
  lcd.print(zh);
  lcd.print(h);
  lcd.print(" ");
  lcd.print(zm);
  lcd.print(m);
  lcd.print(" ");
  lcd.print(zs);
  lcd.print(s);
  
  
  
  while(0==digitalRead(A2));// "Start" button
  while(1==digitalRead(A2));
  
  while(millis() % 1000 != 0);//sincro with Time Base
  delay(50);
  
  digitalWrite(9,HIGH);//start timer
   
 do{//decreasing time
  
  //Displays the intermediate time
  lcd.clear();
  lcd.print("Remain: hh mm ss");  
  lcd.setCursor(8,1);
  lcd.print(zh);
  lcd.print(h);
  lcd.print(" ");
  lcd.print(zm);
  lcd.print(m);
  lcd.print(" ");
  lcd.print(zs);
  lcd.print(s);
  
  while(millis() % 1000 != 0);// Time Base, 1s.
  
  n=n-1;
  
  zh=n/36000;
  r1=n%36000;
  h=r1/3600;
  r2=r1%3600;
  zm=r2/600;
  r3=r2%600;
  m=r3/60;
  r4=r3%60;
  zs=r4/10;
  s=r4%10;
   }while(n!=0);

  lcd.clear(); //display n=0+
  lcd.print("Remain: hh mm ss");  
  lcd.setCursor(8,1);
  lcd.print(zh);
  lcd.print(h);
  lcd.print(" ");
  lcd.print(zm);
  lcd.print(m);
  lcd.print(" ");
  lcd.print(zs);
  lcd.print(s);
   
  digitalWrite(9,LOW);//stop timer
  
   digitalWrite(10,HIGH);//beep to end
   delay(2000);
   digitalWrite(10,LOW);
   }while(digitalRead(A3)==HIGH);//"Memory" button
   }}// end of loop
    
 byte roTen(){ // Rotary encoder routine 
 
 while(digitalRead(A2) &digitalRead(A1) & digitalRead(A0)==1);
 
 if(digitalRead(A2)==0){
  return counter;
  
  }
   switch(digitalRead(A0)) {
    case HIGH:
    while(digitalRead(A0)==0);
    while(digitalRead(A1)==0);
    counter ++;
     counter=counter%md;
    break;
    case LOW:
   while(digitalRead(A1)==0);
   while(digitalRead(A0)==0);
   counter --;
   if(counter==-1){//left begin with md-1
    counter=md-1;
    } 
     counter=abs(counter)%md; 
  break;
 }
   return counter;
   }                                                                
  
  void lcdpr(){ //lcd print routine
  lcd.setCursor(8,1); 
  lcd.print(zh);
  lcd.print(h);
  lcd.print(" ");
  lcd.print(zm);
  lcd.print(m);
  lcd.print(" ");
  lcd.print(zs);
  lcd.print(s);
  delay(150);
   }
   
   
   
