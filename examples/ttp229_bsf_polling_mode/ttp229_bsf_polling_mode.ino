#include "ttp229_bsf.h"
void setup() {
  Serial.begin(9600);
  ttp.init();
}

void loop() {
  ttp.ReadKeypad();  
  Serial.println(ttp.getKey(), BIN);
  Serial.println(ttp.getPressedKey(), HEX);
  ttp.clearPressedKey();
  delay(100);
}
