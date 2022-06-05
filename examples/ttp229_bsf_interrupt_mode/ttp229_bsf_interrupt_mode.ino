#include "ttp229_bsf.h"
void setup() {
  Serial.begin(9600);
  ttp.init();
  ttp.setInterruptMode();
 }

void loop() {

	if(ttp.getPressedKey())
	{
		Serial.println(ttp.getPressedKey(), HEX);
		ttp.clearPressedKey();
	}
  delay(100);
 
}
