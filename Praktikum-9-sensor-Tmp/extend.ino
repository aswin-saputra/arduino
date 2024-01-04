
// Sketch uses 2076 bytes (6%) of program storage space. Maximum is 30720 bytes.
// Global variables use 101 bytes (4%)

#include <LiquidCrystal.h>
#include <Servo.h>
#define LCD_RS 8
#define LCD_EN 9
#define LCD0_D4 4
#define LCD0_D5 5
#define LCD0_D6 6
#define LCD0_D7 7
// #define OFFSET 500
#define OFFSET 0
#define SERVONG 2

LiquidCrystal LCD0(
    LCD_RS,
    LCD_EN,
    LCD0_D4,
    LCD0_D5,
    LCD0_D6,
    LCD0_D7);
#define MILLI_VOLT_REF 5000.0
#define ADC_BIT 1023.0


Servo myServo;
unsigned long MOVING_TIME = 10; // moving time is 3 seconds
unsigned long moveStartTime;
// int startAngle = 0; // 30°
// int stopAngle  = 180; // 90°


static int lastPos = 0;
void setup()
{
  LCD0.begin(16, 2);  
  myServo.attach(SERVOBANG);
  moveStartTime = millis(); // start moving

}

void loop()
{
    int adcValue = analogRead(A8);
    LCD0.setCursor(0, 0);
    float mV = adcValue / ADC_BIT * MILLI_VOLT_REF;
    LCD0.print("Mv : ");
    LCD0.setCursor(5, 0);
    LCD0.print(mV);
    delay(500);
    LCD0.setCursor(0, 1);
    LCD0.print("Temp : ");
    LCD0.setCursor(8, 1);
    float tempC = (mV - OFFSET) / 10.0;
    LCD0.print(tempC);
    delay(500);


if (tempC > 35){
muuuup(90);
delay(500);
}
else{
muuudown(0);
delay(500);

  }
}

  void muuuup(int stopAngle){
//   static unsigned long progress = millis() - moveStartTime;
//   if (progress <= MOVING_TIME) {
//     long angle = map(progress, 0, MOVING_TIME, lastpos, stopAngle);
//     myServo.write(angle); 
// lastPos = angle;
//   }
int pos;
  for (pos = 0; pos <= stopAngle; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}
  void muuudown(int stopAngle){
int pos;
//   static unsigned long progress = millis() - moveStartTime;
//   if (progress <= MOVING_TIME) {
//     long angle = map(progress, 0, MOVING_TIME, lastpos, stopAngle);
//     myServo.write(angle); 
// lastPos = angle;
//   }

  for (pos = 90; pos <= stopAngle; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
}