/*  Praktikum 9 Sensor TMP 36 dean LCD 162
    Disimulasikan pada ThinkerCAD

    Nama : Aswin Saputra
*/

#include <LiquidCrystal.h>

#define DEBUG 1
#define LCD_RS 7
#define LCD_EN 6
#define LCD0_D4 5
#define LCD0_D5 4
#define LCD0_D6 3
#define LCD0_D7 2

void tempInit(struct sensorTmp *sensor,
              int pin, int offset, int factor);
void getdata(struct sensorTmp *sensor);
void sendToDisplay(struct sensorTmp *sensor);

LiquidCrystal LCD0(
    LCD_RS,
    LCD_EN,
    LCD0_D4,
    LCD0_D5,
    LCD0_D6,
    LCD0_D7);

struct sensorTmp
{
    int pin;
    int voffset;
    int factor;
    unsigned int adcValue;
    double mV;
    float tempC;
};

void setup()
{
    if (DEBUG)
    {
        Serial.begin(9600);
    }
    LCD0.begin(16, 2);
    struct sensorTmp tmp36;
    /*TMP36 pin A0 offset Increase Factor*/
    tempInit(&tmp36, A0, 500, 10);

    while (1)
    {
        getdata(&tmp36);
        sendToDisplay(&tmp36);
        if (DEBUG)
        {
            Serial.println(tmp36.mV);
            Serial.println(tmp36.tempC);
        }
    }
}
void loop() {}

/*
getData(&stucturename){
  sensor->adcValue = analogRead(sensor->pin);
  sensor->mV = float(sensor->adcValue) / ADC_BIT * MILLI_VOLT_REF;
  sensor->tempC = (sensor->mV - sensor->voffset) / sensor->factor;
}
Sensor TMP 36
Vout = 500mV + 10* Temperatur
TmpC = vout- 500 / 10

Sensor LM35
Vout = 10 * Temperatur
TmpC = vout/10
*/
#define MILLI_VOLT_REF 5000.0
#define ADC_BIT 1023.0

void getdata(struct sensorTmp *sensor)
{
    sensor->adcValue = analogRead(sensor->pin);
    sensor->mV = double(sensor->adcValue) / ADC_BIT * MILLI_VOLT_REF;
    sensor->tempC = (sensor->mV - sensor->voffset) / sensor->factor;
}

void tempInit(
    struct sensorTmp *sensor,
    int pin,
    int offset,
    int factor)
{
    // pinMode(sensor->pin, INPUT); // analog input in A0
    sensor->pin;
    sensor->voffset = offset;
    sensor->factor = factor;
}

#define DISPLAY_MV "mVolt"
#define DISPLAY_TEMP "Temp"
#define DELIMITER ":"
#define UPPER_POS strlen(DISPLAY_MV)
#define LOWER_POS strlen(DISPLAY_TEMP)
#define STR_COL_POS ((UPPER_POS) > (LOWER_POS) ? (UPPER_POS + 1) : (LOWER_POS + 1))
#define VAL_COL_POS ((UPPER_POS) > (LOWER_POS) ? (UPPER_POS + 3) : (LOWER_POS + 3))

void sendToDisplay(struct sensorTmp *sensor)
{
    LCD0.setCursor(0, 0);
    LCD0.print(DISPLAY_MV);
    LCD0.setCursor(STR_COL_POS, 0);
    LCD0.print(DELIMITER);
    LCD0.setCursor(VAL_COL_POS, 0);
    LCD0.print(sensor->mV);

    LCD0.setCursor(0, 1);
    LCD0.print(DISPLAY_TEMP);
    LCD0.setCursor(STR_COL_POS, 1);
    LCD0.print(DELIMITER);
    LCD0.setCursor(VAL_COL_POS, 1);
    LCD0.print(sensor->tempC);
}