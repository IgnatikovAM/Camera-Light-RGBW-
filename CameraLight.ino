
#include <Adafruit_NeoPixel.h> //https://github.com/adafruit/Adafruit_NeoPixel


#define   LED_PIN              11 //пин на светодиоды rgb
#define   LED_WHITE_PIN        12 //пин на светодиоды rgbw 4000K и 3500K
#define   ANALOG_PIN_RED       A0 //пин для потенциометра
#define   ANALOG_PIN_GREEN     A1 //пин для потенциометра
#define   ANALOG_PIN_BLUE      A2 //пин для потенциометра
#define   ANALOG_PIN_WHITE     A3 //пин для потенциометра
#define   ANALOG_PIN_WHITE_2   A4 //пин для потенциометра
#define   ColoursNum           5 //Количество  потенциометров
#define   KEY_PIN              9 //кнопка

#define   PIXEL_IN_STICK              4//Количество светодиодов на полочке 
#define   PIXEL_IN_W_WHITE_STICK      (2 * PIXEL_IN_STICK)//rgbw 3500k //полоски// 2*4=8
#define   PIXEL_IN_C_WHITE_STICK      (2 * PIXEL_IN_STICK)//rgbw 4500k//полоски // 2*4=8
#define   PIXEL_IN_COLOUR_STICK_1     PIXEL_IN_STICK//полоска rgb//4 светодиода
#define   PIXEL_IN_COLOUR_STICK_2     PIXEL_IN_STICK//полоска rgb//4 светодиода
#define   PIXEL_NUM                   (PIXEL_IN_COLOUR_STICK_1 + PIXEL_IN_COLOUR_STICK_2)// две полоски по 8 rgb
#define   PIXEL_WHITE_NUM             (PIXEL_IN_W_WHITE_STICK + PIXEL_IN_C_WHITE_STICK)//две полоски по 8 rgbw 4500k 3500k//





Adafruit_NeoPixel LEDS_WHITE = Adafruit_NeoPixel(PIXEL_WHITE_NUM, LED_WHITE_PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_NeoPixel LEDS = Adafruit_NeoPixel(PIXEL_NUM, LED_PIN, NEO_GRB + NEO_KHZ800);


unsigned int COLOURS[ColoursNum];
byte ANALOG_PINS[ColoursNum] = {ANALOG_PIN_RED, ANALOG_PIN_GREEN, ANALOG_PIN_BLUE, ANALOG_PIN_WHITE, ANALOG_PIN_WHITE_2};
bool Active = false;

void setup()
{
  digitalWrite(KEY_PIN, HIGH);
  LEDS.begin();
  LEDS.show();
  LEDS_WHITE.begin();
  LEDS_WHITE.show();
}
//----------------------------------------
void loop()
{
  if (Active)
  {
    for (byte i = 0; i < ColoursNum; i++)
    {
      COLOURS[i] = analogRead(ANALOG_PINS[i]) / 4;
    }
  
    for (byte i = 0; i < PIXEL_NUM; i++)
      LEDS.setPixelColor(i, COLOURS[0], COLOURS[1], COLOURS[2]);
    for (byte i = 0; i < PIXEL_IN_W_WHITE_STICK; i++)
      LEDS_WHITE.setPixelColor(i, COLOURS[0], COLOURS[1], COLOURS[2], COLOURS[3]);
    for (byte i = PIXEL_IN_W_WHITE_STICK; i < (PIXEL_IN_W_WHITE_STICK + PIXEL_IN_C_WHITE_STICK); i++)
      LEDS_WHITE.setPixelColor(i, COLOURS[0], COLOURS[1], COLOURS[2], COLOURS[4]);

    LEDS_WHITE.show();
    LEDS.show();
  }

  if (!digitalRead(KEY_PIN))
  {
    delay(300);
    if (!digitalRead(KEY_PIN))
    {
      if (Active)
      {
        Active = false;
        for (byte i = 0; i < PIXEL_NUM; i++)
          LEDS.setPixelColor(i, 0);
        for (byte i = 0; i < PIXEL_IN_W_WHITE_STICK; i++)
          LEDS_WHITE.setPixelColor(i, 0);
        for (byte i = PIXEL_IN_W_WHITE_STICK; i < (PIXEL_IN_W_WHITE_STICK + PIXEL_IN_C_WHITE_STICK); i++)
          LEDS_WHITE.setPixelColor(i, 0);

        LEDS_WHITE.show();
        LEDS.show();
      }
      else
        Active = true;
    }
  }
}
//----------------------------------------





