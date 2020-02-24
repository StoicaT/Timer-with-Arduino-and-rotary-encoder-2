

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

#define btMem A3 //Button "Memory" to ground
#define oRel 9 // OUT relay
#define oBuz 10 // OUT buzzer
#define pUsh A2 // Push rot. enc. to ground
#define rEnb A1 //Rot enc "B" to ground
#define rEna A0 //Rot enc "A" to ground

void setup() {
   lcd.begin(16, 2);
   pinMode(btMem, INPUT_PULLUP);
   pinMode(pUsh, INPUT_PULLUP);
   pinMode(rEnb, INPUT_PULLUP);
   pinMode(rEna, INPUT_PULLUP);
   pinMode(oRel, OUTPUT);
   pinMode(oBuz, OUTPUT);
   
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
   }while(digitalRead(pUsh)==HIGH);//Push button
  delay(10);
  counter=0;
 
  
  md=6;// set sX10
   lcd.clear();
  lcd.print("Set t:        _");
  lcdpr();
  do{  
 zs= roTen();
 lcdpr();
 }while(digitalRead(pUsh)==HIGH);//Push button
  delay(10);
  counter=0;
 
  
  md=10;// set min.
   lcd.clear();
  lcd.print("Set t:      _");
  lcdpr();
  do{ 
 m= roTen();
 lcdpr();
 }while(digitalRead(pUsh)==HIGH);//Push button
 delay(10);
 counter=0;
 
  
  md=6;// set min.X10
  lcd.clear();
  lcd.print("Set t:     _");
  lcdpr();
  do{
  zm= roTen();
  lcdpr();
  }while(digitalRead(pUsh)==HIGH);//Push button
  delay(10);
  counter=0;
  
  
  md=5;// set h
  lcd.clear();
  lcd.print("Set t:   _");
  lcdpr();
  do{//
  h= roTen();
  lcdpr();
  }while(digitalRead(pUsh)==HIGH);//Push button
  delay(10);
  counter=0;
  
  
  md=3;//set hX10;
   lcd.clear();
  lcd.print("Set t:  _");
  lcdpr();
  do{
  zh= roTen();
  lcdpr();
 }while(digitalRead(pUsh)==HIGH);//Push button
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
  
  
  
  while(0==digitalRead(pUsh));// Push button to start
  while(1==digitalRead(pUsh));
  
  while(millis() % 1000 != 0);//sincro with Time Base
  delay(50);
  
  digitalWrite(oRel,HIGH);//start timer
   
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
   
  digitalWrite(oRel,LOW);//stop timer
  
   digitalWrite(oBuz,HIGH);//beep to end
   delay(2000);
   digitalWrite(oBuz,LOW);
   }while(digitalRead(btMem)==HIGH);//"Memory" button
   }}// end of loop
    
 byte roTen(){ // Rotary encoder routine 
 
 while(digitalRead(pUsh) &digitalRead(rEnb) & digitalRead(rEna)==1);
 
 if(digitalRead(pUsh)==0){
  return counter;
  
  }
   switch(digitalRead(rEna)) {
    case HIGH:
    while(digitalRead(rEna)==0);
    while(digitalRead(rEnb)==0);
    counter ++;
     counter=counter%md;
    break;
    case LOW:
   while(digitalRead(rEnb)==0);
   while(digitalRead(rEna)==0);
   counter --;
   if(counter==-1){
    counter=md-1;//left begin with md-1
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
   
   
   
