void Light_RGB(int R, int G, int B){
    for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = Rgb(R, G, B);
    }
    leds.show();
}

void Light(int Hue){
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = Hsv(Hue, S, LedBrs);
  }
  leds.show();  
}

                  /*PIXEL SHADOW*/

void PixelShadowRight() {
  for (int i = 0; i < NUM_LEDS; i++) {
    p++;
    if (p > NUM_LEDS - 1)
      p -= NUM_LEDS;
    leds[p] = Hsv(H + (2 * i), S, (LedBrs / NUM_LEDS) * i);
  }
  leds.show();
  p++;
  delay(40);
}

void PixelShadowLeft() {
  for (int i = 0; i < NUM_LEDS; i++) {
    p--;
    if (p < 0)
      p += NUM_LEDS;
    leds[p] = Hsv(H + (2 * i), S, (LedBrs / NUM_LEDS) * i);
  }
  leds.show();
  p--;
  delay(40);
}

                  /*PIXEL SHADOW*/

void NoColor() {
  LedBrs = DefBrs;
  S = 0;
}

void Speed2() {
  delay(40);
}

void Color() {
  S = 255;
  H ++;
  if (H > 255)
    H = 0;
}

 void tobreath(int Speed) {
  if (LedBrs >= 253)
    j = -1;
  if (LedBrs <= 18)
    j = 1;
  LedBrs += (Speed * j);
}

                  /*EXTRAS*/
                  
void randomizer() {
  S = 255;
  if (H != x) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = Hsv(H, S, LedBrs); leds.show();
    }
    if (H > 255){Serial.print("BUM");
      H = 0;
    }
    if (H < 0) H = 256;
    H += j;
  }
  else {
    x = random(0, 256);
    if (random(2) == 1) j = 1;
    else j = -1;
  }
}

