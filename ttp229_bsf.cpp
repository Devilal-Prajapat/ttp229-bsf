#include "Arduino.h"
#include "ttp229_bsf.h"

#define SCL_PIN 14
#define SDO_PIN 12

#ifdef ISR_PREFIX
#else
#define ISR_PREFIX     ICACHE_RAM_ATTR
#endif

#define KEY_1     0xFFFE
#define KEY_2     0xFFFD
#define KEY_3     0xFFFB
#define KEY_4     0xFFF7

#define KEY_5     0xFFEF
#define KEY_6     0xFFDF
#define KEY_7     0xFFBF
#define KEY_8     0xFF7F

#define KEY_9     0xFEFF
#define KEY_10    0xFDFF
#define KEY_11    0xFBFF
#define KEY_12    0xF7FF

#define KEY_13    0xEFFF
#define KEY_14    0xDFFF
#define KEY_15    0xBFFF
#define KEY_16    0x7FFF


TTP229_BSF :: TTP229_BSF()
{
  keypad_flag = false;
  __scl_pin = SCL_PIN;
  __sdo_pin = SDO_PIN;
  key_data = 0xFFFF;
  key_pressed = 0;
}

TTP229_BSF :: ~TTP229_BSF()
{  

}

void TTP229_BSF :: setPins(int scl_pin, int sdo_pin)
{
  __scl_pin = scl_pin;
  __sdo_pin = sdo_pin;
}

void TTP229_BSF :: init()
{
  pinMode(__scl_pin, OUTPUT);
  pinMode(__sdo_pin, INPUT);
}

void TTP229_BSF :: ReadKeypad(void)
{
  key_data = 0x0000;
  for (int i = 0; i < 16; i++)
  {
    digitalWrite(__scl_pin, LOW);
    key_data |= (digitalRead(__sdo_pin) << i);
    digitalWrite(__scl_pin, HIGH);
  }
  //Serial.println(key_data, BIN);
}

bool TTP229_BSF :: getFlag(void)
{
  return keypad_flag;
}

void TTP229_BSF :: clearFlag(void)
{
  keypad_flag = false;
}

uint16_t TTP229_BSF :: getKey(void)
{
  switch (key_data)
  {
    case KEY_1:
      key_pressed = 1;
      break;
    case KEY_2:
      key_pressed = 2;
      break;
    case KEY_3:
      key_pressed = 3;
      break;
    case KEY_4:
      key_pressed = 4;
      break;
    case KEY_5:
      key_pressed = 5;
      break;
    case KEY_6:
      key_pressed = 6;
      break;
    case KEY_7:
      key_pressed = 7;
      break;
    case KEY_8:
      key_pressed = 8;
      break;
    case KEY_9:
      key_pressed = 9;
      break;
    case KEY_10:
      key_pressed = 10;
      break;
    case KEY_11:
      key_pressed = 11;
      break;
    case KEY_12:
      key_pressed = 12;
      break;
    case KEY_13:
      key_pressed = 13;
      break;
    case KEY_14:
      key_pressed = 14;
      break;
    case KEY_15:
      key_pressed = 15;
      break;
    case KEY_16:
      key_pressed = 16;
      break;
    default:
      break;
  }
  // Serial.println(key_data, BIN);
  return key_data;
}

uint16_t TTP229_BSF :: getPressedKey(void)
{
  return key_pressed;
}

void TTP229_BSF :: clearPressedKey(void)
{
  key_pressed = 0;
}

void TTP229_BSF :: setInterruptMode(void)
{
  keypad_flag = 0;
  pinMode(__sdo_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(__sdo_pin), TTP229_BSF :: onKeypadInterrupt, FALLING);
}


void TTP229_BSF :: handleKeyPadInterrupt(void)
{
  key_data = 0x0000;
  for (int i = 0; i < 16; i++)
  {
    digitalWrite(__scl_pin, LOW);
    ttp.key_data |= (digitalRead(__sdo_pin) << i);
    digitalWrite(__scl_pin, HIGH);
  }
  ttp.getKey();
  // ttp.keypad_flag = true;
}

ISR_PREFIX void TTP229_BSF :: onKeypadInterrupt(void)
{
  noInterrupts();
  ttp.handleKeyPadInterrupt();
  interrupts();
}

TTP229_BSF ttp;
