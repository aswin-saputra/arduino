
/*
 * Pengukuran Jarak dengan sensor Ultrasonic dan memicu buzzer
 * pada jarak tertentu
 * Sistem ini bekerja mirip dengan sensor parkir mobil
 * dimana buzer akan mendeteksi dari jarak lebih dari 2m
 * dibawah 2 meter akan mempercepat dan memperbanyak durasi buzer
 * jika jarak dibawah 15 cm buzer akan berbunyi kontinyu
 * Perhitungan kecepatan suara juga di dasari pada faktor suhu untuk mendpatkan perhitungan yang akurat
 * kemudian Hasil di tampilkan pada LCD 162
 * program properties
 * Tested ON ARDUINO NANO V3
 * Sketch uses 6492 bytes (21%)
 * Global variables use 313 bytes (15%)
 */

#include <LiquidCrystal.h>

#define DEBUG 1

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

void tempInit(struct sensorTmp *sensor,
              int pin, int offset, int factor);
void getdata(struct sensorTmp *sensor);
void sendToDisplay(struct sensorTmp *sensor, float jarak);
float Distance_Calc(uint8_t Pin_Trigger, uint8_t Pin_Echo, struct sensorTmp *sensor);
void buzzer(uint8_t pin, int duration);

struct sensorTmp
{
    int pin;
    int voffset;
    int factor;
    unsigned int adcValue;
    double mV;
    float tempC;
};

// kalkulasi kecepatan suara m/s berdasarkan temperatur udara
// #define SOUND_SPEED(air_temp) 331.3 + (0.606 * air_temp)

#define pingTrig 11
#define pongEcho 12
#define buzzPin 8
#define PB 9

// menetapakan temperatur
// #define AIR_TEMP 24

void setup()
{
    if (DEBUG)
    {
        Serial.begin(115200);
    }
    pinMode(pingTrig, OUTPUT);
    pinMode(pongEcho, INPUT);
    pinMode(PB, INPUT_PULLUP);
    pinMode(buzzPin, OUTPUT);

    LCD0.begin(16, 2);
    struct sensorTmp tmp36;
    /*TMP36 pin A0 offset Increase Factor*/
    tempInit(&tmp36, A0, 500, 10);

    while (1)
    {
        getdata(&tmp36);
        if (DEBUG)
        {
            Serial.println(tmp36.mV);
            Serial.println(tmp36.tempC);
        }

        // float soundSpeed = 331.3 + (0.606 * tmp36.tempC);
        double jarak = Distance_Calc(pingTrig, pongEcho, &tmp36);
        sendToDisplay(&tmp36, jarak);

        if (jarak >= 200)
        { // jika jarak lebih dari 200 cm maka akan ada beep
            buzzer(buzzPin, 100);
            delay(1200);
        }
        else if (jarak >= 50 && jarak < 200)
        { // jika jarak  antara 50 -- 200 cm maka
          // akan beep yang semangkin cepat seiring jarak mendekat
            buzzer(buzzPin, 100);
            delay((2 * (jarak / 10) * (jarak / 10)) + 350);
        }
        else if (jarak >= 15 && jarak <= 50)
        {
            buzzer(buzzPin, 100);
            delay(((jarak * jarak) / 10) + 150);
        }

        else
        { // jika jarak  kurang dari 15 cm maka cuzer akan berbunyi kontinyu
            buzzer(buzzPin, 800);
            delay(100);
        }
        // print hasil pengukuran
        if (DEBUG)
        {
            Serial.print(", Jarak: ");
            Serial.println(jarak);
        }
    }
}

void loop() {}

#define MILLI_VOLT_REF 5000.0
#define ADC_BIT 1023.0

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

void getdata(struct sensorTmp *sensor)
{
    sensor->adcValue = analogRead(A0);
    if (DEBUG)
    {
        Serial.print("ANALOG READ : ");
        Serial.println(sensor->adcValue);
    }
    sensor->mV = double(sensor->adcValue) / ADC_BIT * MILLI_VOLT_REF;
    sensor->tempC = (sensor->mV - sensor->voffset) / sensor->factor;
}

float Distance_Calc(uint8_t Pin_Trigger, uint8_t Pin_Echo, struct sensorTmp *sensor)
{
    float soundSpeed = 331.3 + (0.606 * sensor->tempC);
    if (DEBUG)
    {
        Serial.print("SUHU: ");
        Serial.println(sensor->tempC);
        Serial.print("SOUND SPEED: ");
        Serial.println(soundSpeed);
    }
    // membuat pulsa 10 micro second
    digitalWrite(Pin_Trigger, HIGH);
    //   delayMicroseconds(500);
    delay(8);
    digitalWrite(Pin_Trigger, LOW);

    uint16_t durasi = pulseIn(Pin_Echo, HIGH); // hitung kalkulasi waktu durasi dalam us

    return double(durasi) / 20000.0 * soundSpeed; // hitung jarak dalam cm
}

void buzzer(uint8_t pin, int duration)
{
    int tonefreq = 1760; // A 6th octave
    tone(pin, tonefreq, duration);
    // delay(Time_delay);
}

#define DISPLAY_DISTANCE "Jarak"
#define DISPLAY_TEMP "Temp"
#define DELIMITER ":"
#define UPPER_POS strlen(DISPLAY_DISTANCE)
#define LOWER_POS strlen(DISPLAY_TEMP)
#define STR_COL_POS ((UPPER_POS) > (LOWER_POS) ? (UPPER_POS + 1) : (LOWER_POS + 1))
#define VAL_COL_POS ((UPPER_POS) > (LOWER_POS) ? (UPPER_POS + 3) : (LOWER_POS + 3))

void sendToDisplay(struct sensorTmp *sensor, float jarak)
{
    LCD0.setCursor(0, 0);
    LCD0.print(DISPLAY_DISTANCE);
    LCD0.setCursor(STR_COL_POS, 0);
    LCD0.print(DELIMITER);
    LCD0.setCursor(VAL_COL_POS, 0);
    LCD0.print(jarak);

    LCD0.setCursor(0, 1);
    LCD0.print(DISPLAY_TEMP);
    LCD0.setCursor(STR_COL_POS, 1);
    LCD0.print(DELIMITER);
    LCD0.setCursor(VAL_COL_POS, 1);
    LCD0.print(sensor->tempC);
}
