
// Sketch uses 2076 bytes (6%) of program storage space. Maximum is 30720 bytes.
// Global variables use 101 bytes (4%)

#include <LiquidCrystal.h>
#define LCD_RS 7
#define LCD_EN 6
#define LCD0_D4 5
#define LCD0_D5 4
#define LCD0_D6 3
#define LCD0_D7 2


LiquidCrystal LCD0(
    LCD_RS,
    LCD_EN,
    LCD0_D4,
    LCD0_D5,
    LCD0_D6,
    LCD0_D7);
#define MILLI_VOLT_REF 5000.0
#define ADC_BIT 1023.0


void setup()
{
  LCD0.begin(16, 2);
}

void loop()
{
    int adcValue = analogRead(A0);
    getdata(tmp36);
    LCD0.setCursor(0, 0);
    float mV = adcValue / ADC_BIT * MILLI_VOLT_REF;
    LCD0.print("Mv : ");
    LCD0.setCursor(5, 0);
    LCD0.print(mV);
    delay(500);
    LCD0.setCursor(0, 1);
    LCD0.print("Temp : ");
    LCD0.setCursor(8, 1);
    float tempC = (mV - 500.0) / 10.0;
    LCD0.print(tempC);
    delay(500);
  };