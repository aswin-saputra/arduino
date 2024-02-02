
// #include <arduino.h>
#include <avr/io.h>
#include <LiquidCrystal.h>

#define DEBUG 1
#define LCD_RS 7
#define LCD_EN 6
#define LCD0_D4 5
#define LCD0_D5 4
#define LCD0_D6 3
#define LCD0_D7 2

#define MILLI_VOLT_REF 5000.0
#define ADC_BIT 1023.0
#define DISPLAY_MV "mVolt"
#define DISPLAY_TEMP "Temp"
#define DELIMITER ":"

// float getTempC(int);

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
    int adcValue;
    float mV;
    float tempC;
};

void getdata(struct sensorTmp *sensor)
{
    sensor->adcValue = analogRead(sensor->pin);
    sensor->mV = float(sensor->adcValue) / ADC_BIT * MILLI_VOLT_REF;
    sensor->tempC = (sensor->mV - sensor->voffset) / sensor->factor;
}

void tempInit(
    struct sensorTmp *sensor,
    uint8_t pin,
    int offset,
    uint8_t factor)
{
    pinMode(sensor->pin, INPUT); // analog input in A0
    sensor->voffset = offset;
    sensor->factor = factor;
}
void sendToDisplay(struct sensorTmp *sensor)
{
    LCD0.setCursor(0, 0);
    LCD0.print(DISPLAY_MV);
    LCD0.setCursor(strlen(DISPLAY_MV) + 1, 0);
    LCD0.print(DELIMITER);
    LCD0.setCursor(strlen(DISPLAY_MV) + 2, 0);
    LCD0.print(sensor->mV);

    LCD0.setCursor(0, 1);
    LCD0.print(DISPLAY_TEMP);
    LCD0.setCursor(strlen(DISPLAY_TEMP) + 2, 1);
    LCD0.print(DELIMITER);
    LCD0.setCursor(strlen(DISPLAY_TEMP) + 3, 1);
    LCD0.print(sensor->tempC);
}
// int main(void)
void setup()
{
    if (DEBUG)
    {
        Serial.begin(9600);
    }

    LCD0.begin(16, 2);
    // struct sensorTmp tmp36 = {A0, 500, 10, 0, 0, 0};
    struct sensorTmp tmp36;
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
        // return 0;
    }
}
void loop()
{
    //
}
