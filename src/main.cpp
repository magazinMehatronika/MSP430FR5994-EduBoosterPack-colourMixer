#include <Arduino.h>

// colourMixer magazinMehatronika eduIot projekat 2022

#include "LCD_screen.h"
#include "LCD_utilities.h"
#include "LCD_screen_font.h"
#include "LiquidCrystal.h"
#include <Screen_HX8353E.h>
#include "SPI.h"

Screen_HX8353E myScreen;

uint16_t valueBlue = 0;
uint16_t valueBlueO = 0;
uint16_t valueGreen = 0;
uint16_t valueGreenO = 0;
uint16_t valueRed = 0;
uint16_t valueRedO = 0;

#define joystickX 2
#define joystickY 26
uint16_t x, y;

int i=0;
int k = 0;

void setup() {

  pinMode(GREEN_LED, OUT);
  pinMode(RED_LED,OUT);    

  pinMode(37,OUT); // Blue
  pinMode(38,OUT); // Green
  pinMode(39,OUT); // Red

  pinMode(45,INPUT_PULLUP);
  pinMode(46,INPUT_PULLUP);
  pinMode(32,INPUT);
  pinMode(33,INPUT);

  Serial.begin(9600);
  
  myScreen.begin();
  myScreen.clear();

  myScreen.gText(10,110,"magazinMehatronika", whiteColour);
}

void loop() {

  x = map(analogRead(joystickX), 0, 4096, 0, 128);
  y = map(analogRead(joystickY), 0, 4096, 128, 0);
    if (x < 60)      x = 1;
    if (x > 126)    x = 126;
    if (y < 1)      y = 1;
    if (y > 126)    y = 126;

if ( x>80)
        { if (valueRed<100) { valueRedO=valueRed; valueRed++; k=1;}
        }
  if ( x<50)
        { if (valueRed>0) {valueRedO=valueRed; valueRed--; k=1;}    
        }

  if ( digitalRead(32))
        { if (valueBlue<100) { valueBlueO=valueBlue; valueBlue++; k=1;}
        }
  if ( digitalRead(33))
        { if (valueBlue>0) {valueBlueO=valueBlue; valueBlue--; k=1;}    
        }
  if ( y<50)
        { if (valueGreen<100) { valueGreenO=valueGreen; valueGreen++; k=1;}
        }
  if ( y>80)
        { if (valueGreen>0) {valueGreenO=valueGreen; valueGreen--; k=1;}    
        }
  analogWrite(39,valueRed*32/100);
  analogWrite(38,valueGreen*32/100);
  analogWrite(37,valueBlue*32/100);
  
  delay(200);
  // myScreen.clear();
  if (k==1) {
      k=0;
      
      myScreen.setFontSize(1);
      myScreen.gText(15,80, String(valueRedO)+"%",blackColour); 
      myScreen.gText(15,80, String(valueRed)+"%",redColour);
      for (i=0; i<10; i++) {myScreen.dRectangle(10+i,50+i,20-2*i,20-2*i,myScreen.calculateColour( valueRed*8*32/101, 0, 0));}

      myScreen.gText(55,80, String(valueGreenO)+"%",blackColour); 
      myScreen.gText(55,80, String(valueGreen)+"%",greenColour);
      for (i=0; i<10; i++) {myScreen.dRectangle(50+i,50+i,20-2*i,20-2*i, myScreen.calculateColour( 0, valueGreen*8*32/101, 0));}
      
      myScreen.gText(95,80, String(valueBlueO)+"%",blackColour); 
      myScreen.gText(95,80, String(valueBlue)+"%",blueColour);
      for (i=0; i<10; i++) {myScreen.dRectangle(90+i,50+i,20-2*i,20-2*i,myScreen.calculateColour( 0, 0, valueBlue*8*32/100));}
      
      for (i=0; i<10; i++) {myScreen.dRectangle(40+i,10+i,20-2*i,20-2*i, myScreen.calculateColour( valueRed*8*32/101, valueGreen*8*32/101, valueBlue*8*32/101));
                            myScreen.dRectangle(60+i,10+i,20-2*i,20-2*i, myScreen.calculateColour( valueRed*8*32/101, valueGreen*8*32/101, valueBlue*8*32/101));}
          
      }
  

}