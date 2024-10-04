#include <Arduino.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Arduino.h"

#include "Print.h"
#include <SPI.h>

TIM_HandleTypeDef htim2;
 
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);

    int in1 = 9;
    int Dis1 = 8;
    int NDis1 = 7;
    int in2 = 10;

    const bool on = HIGH;
    const bool off = LOW;
    bool Dir;
    int counter=0;
 

  void setup (void)
    {
      pinMode(/*in1*/ PB_8, OUTPUT);    
      pinMode(/*Dis1*/ D8, OUTPUT);
      pinMode(/*NDis1*/ D7, OUTPUT);

      #define OLED_MOSI  D12
      #define OLED_CLK  D13
      #define OLED_MISO   D11

      pinMode(/*24*/ D6, OUTPUT);
      pinMode(/*in2*/ D10, OUTPUT);
      Serial.begin (9600);
      Serial.println ();

      digitalWrite(SS, HIGH);  // ensure SS stays high for now
      SPI.begin ();

      // Slow down the master a bit
      SPI.setClockDivider(SPI_CLOCK_DIV8);
    }  

  uint16_t transferAndWait (const uint16_t what)
    {
      SPI.beginTransaction(SPISettings((uint32_t)13700, MSBFIRST, SPI_MODE1));
       delay(100);
      digitalWrite(D6, LOW);
       delay(100);
      uint16_t a = SPI.transfer16(what);    // Send aus dem Master
      
      delay(100);
      digitalWrite(D6, HIGH);
       delay(100);
      SPI.endTransaction();
      return a;
    }


void HB_Activation()
{ 
  digitalWrite(D8, HIGH);
  delay(250);
  digitalWrite(D8, LOW);
  Serial.println(transferAndWait(100100000000000), BIN); 

}
void HB_Activated(bool Dir, int a , int b)
{ 
  delayMicroseconds(10);
  digitalWrite( D10, HIGH);
  delayMicroseconds(10);
  digitalWrite( D10, LOW);
  delayMicroseconds(10);
  digitalWrite(D7, HIGH); 
  pinMode(PB_8, OUTPUT);
  digitalWrite(PB_8, HIGH);

 int ledPin = 5;
int dutyCycle = 180; // 127 entspricht 50%    127 von 254 
analogWrite(ledPin, dutyCycle);



digitalWrite(D10, Dir);

  delay (100); 

}

void HB_Reset()
{
  
 Serial.println(transferAndWait(0x2401), HEX);
  delay(100);
 Serial.println(transferAndWait(0x2201), HEX);
  delay(100);
 Serial.println(transferAndWait(0x2000), HEX);  
  delay(100);
 Serial.println(transferAndWait(0111000000000011), BIN);    
}

void loop (void)
{   int a; int b;
    a=180;
    b=40;
    int Sek;

    counter++;
    if(counter > 1)
    {HB_Reset();
    }

    HB_Reset();
       

    HB_Activation();

    
    Sek =3600;
    int i=10*Sek;
    Dir =off;
    while (i--)
    { 
      HB_Activated(Dir, 100 , 200); 
      Serial.println(transferAndWait(1000000000000000), BIN);
     
    }  
    
}  



// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}