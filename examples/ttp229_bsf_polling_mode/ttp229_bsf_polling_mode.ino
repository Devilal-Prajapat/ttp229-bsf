#include "ttp229_bsf.h"
void setup() {
  Serial.begin(9600);
  ttp.init();
  ttp.setInterruptMode();
  // put your setup code here, to run once:

}

void loop() {
  ttp.ReadKeypad();  
  Serial.println(ttp.getKey(), BIN);
  Serial.println(ttp.getPressedKey(), HEX);
  ttp.clearPressedKey();
  delay(100);
  // put your main code here, to run repeatedly:

}