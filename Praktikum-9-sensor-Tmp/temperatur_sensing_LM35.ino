/*  Praktikum 9 Sensor TMP 36 dean LCD 162
    Lab
    Bord TEST : Anduino MEGA
    Temperature Sensor LM35
    Dislpay : 162 with sheild
    SERVO : micro Servo C90
    Nama : Aswin Saputra
    */

#include <LiquidCrystal.h>
#include <Servo.h>

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

/*Creat Object Servo*/
Servo servoOne;

void setup()
{
    if (DEBUG)
    {
        Serial.begin(9600);
    }
    LCD0.begin(16, 2);
    servoOne.attach(11);
    struct sensorTmp lm35;
    /*lm35 pin A0 offset Increase Factor*/
    tempInit(&tmp36, A1, 500, 10);
    tempInit(&lm35, A0, 0, 10);
    getdata(&lm35);
    servoOne.write(0);

    /*Run Foerver Ini This LOOP*/
    while (1)
    {
        getdata(&lm35);
        sendToDisplay(&lm35);
        servoSet(&lm35);

        if (DEBUG)
        {
            Serial.println(lm35.adcValue);
            Serial.println(lm35.mV);
            Serial.println(lm35.tempC);
        }
    }
}

// +++++++++++++++++++++
void loop()
{ /*do nothing*/
}
// +++++++++++++++++++++
/*  Defenition
    : sensor :: &stucture_name
    getData(stuct SensorTmp *sensor ){
      sensor->adcValue = analogRead(sensor->pin);
      sensor->mV = float(sensor->adcValue) / ADC_BIT * MILLI_VOLT_REF;
      sensor->tempC = (sensor->mV - sensor->voffset) / sensor->factor;
    }
    Function Usage examples
    you must be create Instace of Sensor Structur
    i.e getData(&lm35);
    feel free to to naming stuct of struct sensor

    Sensor TMP 36
    Vout = 500mV + 10* Temperatur
    TmpC = vout- 500 / 10

    Sensor LM35
    Vout = 10 * Temperatur
    TmpC = vout/10
    */
void getdata(struct sensorTmp *sensor)
{
    sensor->adcValue = analogRead(sensor->pin);
    sensor->mV = float(sensor->adcValue) / ADC_BIT * MILLI_VOLT_REF;
    sensor->tempC = (sensor->mV - sensor->voffset) / sensor->factor;
}

/*
tempInit(&struct, INPUT_PIN, milli_Volt_Offset,Inc_Factor);
::: arg 1 --> stuct
::: arg 2 --> uint8_t
::: arg 3 --> int
::: arg 4 --> uint8_t
i.e:
tempInit(&my_temp_sensor,500,10)
*/
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
    // Print Data
    LCD0.setCursor(strlen(DISPLAY_MV) + 2, 0);
    LCD0.print(sensor->mV);

    LCD0.setCursor(0, 1);
    LCD0.print(DISPLAY_TEMP);
    LCD0.setCursor(strlen(DISPLAY_TEMP) + 2, 1);
    LCD0.print(DELIMITER);
    // Print Data
    LCD0.setCursor(strlen(DISPLAY_TEMP) + 3, 1);
    LCD0.print(sensor->tempC);
}
void servoSet(struct sensorTmp *sensor)
{
    /*
    Init Pos Ref
    LM35
    ADC 2 --> 0 deg C LM35
    ADC 306 --> 150 deg C LM35
    TMP36
    ADC 102 --> 0 deg C TMP36
    ADC 20 --> -40 deg C TMP36
    ADC 358 --> 125 deg C TMP36
    */
    int currentPos, lastPos;
    int pos;
    currentPos = sensor->adcValue;
    if (lastPos != currentPos)
    {
        if (sensor->tempC > 60)
        {
            servoOne.write(180);
            lastPos = currentPos;
        }
        else
        {
            /* range servo unutk suhu 16 C sampai 100 C*/
            pos = map(sensor->adcValue, 32, 205, 0, 180);
            servoOne.write(pos);
            lastPos = currentPos;
        }
    }

    if (DEBUG)
    {
        Serial.print("Servo");
        Serial.println(pos);
    }
}
