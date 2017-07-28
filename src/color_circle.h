#include <SmartLeds.h>

const int LedPin = 32, NUM_LEDS = 60;

int serialPrint = 1, H = 160, AH = 110, Px = 0, p = 0, DefBrs = 128, LedBrs = 155, S = 0, ABrs = 16 /*k fci breath*/, j = 1, /*k fci breath*/ /*k fci randomizer*/ x = AH /*k fci randomizer*/
  //BARVY hezka modra: H 160 B 155 S 255
  ,red = 96, magenta = 128, blue = 160, cyan = 213, green = 0, yellow = 43;

SmartLed leds( LED_WS2812, NUM_LEDS, LedPin, 0, DoubleBuffer );

#include "color_circle_funcions.h"

volatile int cnt = 1;
volatile unsigned long timeHigh; 
volatile unsigned long minDifTime = 30;

String ActualMode[] = {
  "white",
  "red",
  "magenta",
  "blue",
  "cyan",                         //5
  "green",
  "yellow",
  "white",
  "color changing",
  "color changing speed 2",       //10
  "Rotation Right",        
  "Rotation Left",
  "R Right Speed 2",
  "R Left Speed 2",
  "Color Rotation Right",         //15
  "Color Rotation Left", 
  "Color Rotation Right Speed 2",
  "Color Rotation Left Speed 2",
  "breath red",
  "Color Breath",                 //20
  "R Right Breath",
  "R Right Breath Color",
  "breath green"
};




void counter(){
  // if(digitalRead(interruptPin) == LOW){
  //   timeHigh = millis();
  // }
  // else{
  //   if((millis() - timeHigh) > minDifTime){
    cnt++;  
  //   }
  // }
}

void color_circle_setup() {}

void Zmen_HSV(){
  if (Serial.available()){
    char a = Serial.read();
    int change = Serial.parseInt();
    Serial.println(a);
    Serial.println(a, DEC);
    Serial.println(change);
    if(tolower(a) == 'b'){
      LedBrs = change;
      Serial.print("Brightness zmeneno na ");
    }
    else if(tolower(a) == 'h'){
      H = change;
      Serial.print("Hue zmeneno na ");
    }
    else if(tolower(a) == 's'){
      S = change;
      Serial.print("S (saturate) zmeneno na ");
    }
    else{
      Serial.println("Spatne zadane!");
    }
    Serial.println(change);
    delay(2000);  
  }
}

void color_circle_loop() {
  Zmen_HSV();
  switch (cnt){
    case 0:
      LedBrs = 0;
      Light(0);
      break;
    case 1:
      NoColor();   Light(red);
      break;
    case 2:
      S = 255;   Light(red);
      break;
    case 3:
      Light(magenta);
      break;
    case 4:
      Light(blue);
      break;
    case 5:
      Light(cyan);
      break;
    case 6:
      Light(green);
      break;
    case 7:
      Light(yellow);
      break;
    case 8:
      NoColor();   Light(red);
      break;
    case 9:
      Color();   Light(H);   delay(40);
      break;
    case 10:
      Color();   Speed2();   Speed2();
      Light(H);
      break;
    case 11:
      NoColor();   PixelShadowRight();
      break;
    case 12:
      NoColor();   PixelShadowLeft();
      break;
    case 13:
      NoColor();   PixelShadowRight();   Speed2();
      break;
    case 14:
      NoColor();   PixelShadowLeft();   Speed2();
      break;
    case 15:
      Color();   PixelShadowRight();
      break;
    case 16:
      Color();   PixelShadowLeft();
      break;
    case 17:
      Color();   PixelShadowRight();    Speed2();
      break;
    case 18:
      Color();    PixelShadowLeft();    Speed2();
      break;
    case 19:
      H = 0;   tobreath(2);   Light(H);
      break;
    case 20:
      Color();   tobreath(2);   Light(H);
      break;
    case 21:
      Color();   tobreath(2);   PixelShadowLeft();
      break;
    case 22:
      Color();   tobreath(2);   PixelShadowRight();
      break;
    case 23:
      tobreath(2);   Light(green);
      break;
    case 24:
      tobreath(2);   Light(cyan);
      break;
    case 25:
      tobreath(2);   Light(blue);
      break;
    case 26:
      tobreath(2);   Light(magenta);
      break;
    case 27:
      tobreath(2);   Light(red);
      break;
    case 28:
      tobreath(2);   Light(yellow);
      break;
    case 29:
      randomizer();
      break;
    default:
      cnt = 1;
      LedBrs = DefBrs;
      break;
  }
  delay(40);
  if(serialPrint == 1){
    Serial.print(cnt);Serial.print("\n");Serial.print("H = ");Serial.print(H);Serial.print("   LedBrs = ");Serial.print(LedBrs);Serial.print(" Mode = ");
    //Serial.println(ActualMode[cnt - 1]);
  }
}



