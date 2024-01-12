#include "Keyboard.h"

unsigned char mode=0,kchat=254;



void setup() {
  Serial1.begin(400);
  Keyboard.begin();
  pinMode(22,INPUT); // First Switch(also connected to SW1 onboard)

  pinMode(2,OUTPUT); //USB Switcher OE, Output Enabled at LOW, high impedence at HIGH
  pinMode(3,OUTPUT); //USB Switcher - Mouse to PC(LOW) or Smartphone(HIGH)
  pinMode(4,OUTPUT); //USB Switcher - Keyboard to Next switcher(LOW) or Smartphone(HIGH)
  pinMode(5,OUTPUT); //USB Switcher - Keyboard from Previous switcher, to PC(LOW) or RP2040 USB HID(HIGH)

  pinMode(18,OUTPUT); // R LED
  pinMode(19,OUTPUT); // G LED
  pinMode(20,OUTPUT); // Y LED

  //Initial GPIO settings below
  digitalWrite(20, HIGH);
  digitalWrite(19, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(2, LOW);

}

void loop() {
  if (Serial1.available() > 0 && mode==1) {
    Keyboard.write(Serial1.read());
  }
 
  if(kchat==1){
     mode=mode==0?1:0;  //mode 0 is PC Mode, mode 1 is Smartphone Mode
     kchat=0;
     if(mode)
     {
       digitalWrite(2, HIGH);
       delay(100);
       digitalWrite(19, HIGH);
       digitalWrite(20, LOW);
       digitalWrite(3, HIGH);
       digitalWrite(4, HIGH);
       digitalWrite(5, HIGH);
       delay(500); //delay for successful disconnecting. if reconnect failed, give more time
       digitalWrite(2, LOW);
     }  
     else 
     {
       digitalWrite(2, HIGH);
       delay(100);
       digitalWrite(20, HIGH);
       digitalWrite(19, LOW);
       digitalWrite(3, LOW);
       digitalWrite(4, LOW);
       digitalWrite(5, LOW);
       delay(500); //delay for successful disconnecting. if reconnect failed, give more time
       digitalWrite(2, LOW);
     } 
  }

  //Prevent chattering below
  if(digitalRead(22)) 
  {
    kchat=254;
  }
  if(kchat>1 && !digitalRead(22)) kchat--;
}
