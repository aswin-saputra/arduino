/*
! *INTRUKSI 2
!1. Membuat untai antarmuka mikrokontroler(Arduino) dengan 2 buah LED dan 2 buah tombol saklar, sedemikian LED menyala jika saluran output diberi logika 1 dan input berlogika 1 jika tombol ditekan.
 ! 2. Membuat program untuk mengendalikan untai pada no 1, sehingga LED mati jika tombol saklar ditekan */

/* PB use  External PULL DOWN RESISTOR */
#include <avr/io.h>
#include <util/atomic.h>
#include <avr/interrupt.h>
// #include <util/delay.h>

#define RED_LED 4           /*PIN 4*/
#define RED_PUSH_BUTTON 5   /*PIN 5*/
#define GREEN_LED 4         /*PIN 12 */
#define GREEN_PUSH_BUTTON 3 /*PIN 11*/

#define PRESSED 1 /* FOR PULL DOWN CONFIGURATION <pressed == 1>*/
#define PB_DEBOUNCE_DELAY 1
#define PB_HOLD_DELAY 500

#define PB_TOGGLE_MODE0 1
#define PB_HOLD_MODE0 2
// #define PB_HOLD_MODE1 2
// #define PB_HOLD_MODE2 3

// #define BLINK_INTERVAL 10

#define DEBUG 0
#define PB_DEBUG 0
#define LED_DEBUG 0

void ledInit(void);
void pbInit(void);
void PushButtonState(void);
void InputPushButtonToLED(void);
void ledBlink(void);
void ledAction(void);
void wait(void);

struct led {
  volatile uint8_t *ddr;
  volatile uint8_t *port;
  uint8_t ledPin;
  uint8_t ledState;
  uint8_t ledMode;
  unsigned long ledMillis;
};

struct pushButton {
  volatile uint8_t *ddr;
  volatile uint8_t *pinRead;        /*PINX*/
  volatile uint8_t *internalPullup; /*PORTX*/
  uint8_t pbPin;
  uint8_t pbState;
  uint8_t pbPrevState;
  uint8_t pbValue;
  unsigned int pbHoldDuration;
  unsigned int debDelay;
  unsigned long pbMillis;
};

void ledInit(
  struct led *led,
  volatile uint8_t *ddr,
  volatile uint8_t *port,
  uint8_t ledPin) {
  led->ddr = ddr;
  led->port = port;
  led->ledPin = ledPin;
  // led->ledState = 0;
  // led->ledMode = 0;
  // led->ledMillis = ledMillis;
  *(led->ddr) |= (1 << led->ledPin);
}

void pbInit(
  struct pushButton *pb,
  volatile uint8_t *ddr,
  volatile uint8_t *pinRead,
  uint8_t pbPin,
  uint8_t debDelay) {
  pb->ddr = ddr;
  pb->pinRead = pinRead;
  pb->pbPin = pbPin;
  pb->debDelay = debDelay;
  pb->pbState = 0;
  if (DEBUG) { pb->pbPrevState = 0; }
  pb->pbValue = 0;
  pb->pbHoldDuration = 0;
  *(pb->ddr) &= ~(1 << pb->pbPin);
}


/* BEGIN MILLIS DECLARE*/
/* 
https://github.com/monoclecat/avr-millis-function/tree/master
*/
volatile unsigned long timer1_millis;

ISR(TIMER1_COMPA_vect);
void init_millis(unsigned long f_cpu);
unsigned long millis(void);


ISR(TIMER1_COMPA_vect) {
  timer1_millis++;
}

void init_millis(unsigned long f_cpu) {
  unsigned long ctc_match_overflow;

  ctc_match_overflow = ((f_cpu / 1000) / 8);  //when timer1 is this value, 1ms has passed

  // (Set timer to clear when matching ctc_match_overflow) | (Set clock divisor to 8)
  TCCR1B |= (1 << WGM12) | (1 << CS11);

  // high byte first, then low byte
  OCR1AH = (ctc_match_overflow >> 8);
  OCR1AL = ctc_match_overflow;

  // Enable the compare match interrupt
  TIMSK1 |= (1 << OCIE1A);

  //REMEMBER TO ENABLE GLOBAL INTERRUPTS AFTER THIS WITH sei(); !!!
}

unsigned long millis(void) {
  unsigned long millis_return;

  // Ensure this cannot be disrupted
  ATOMIC_BLOCK(ATOMIC_FORCEON) {
    millis_return = timer1_millis;
  }
  return millis_return;
}

/* END MILLIS DECLARE*/


// DELAY FUNCTION
// void wait(unsigned int ms) {
//   for (unsigned int i = 0; i < ms; ++i) {
//     _delay_ms(1);
//   }
// }
// END DELAY FUNCTION

void ledBlink(struct led *led, int duration) {
  // (duration < 10) ? duration = 10 : ((duration > 2000) ? duration = 2000 : 0);
  if ((millis() - (led->ledMillis)) > (duration)) {
    *(led->port) ^= (1 << led->ledPin);
    (led->ledMillis) = millis();
  }
}

void ledAction(struct led *led) {

  *(led->port) ^= (1 << led->ledPin);
}


void InputPushButtonToLED(struct pushButton *pb, struct led *led) {
  // if ((pb->pbValue != led->ledState) && (((pb->pbValue >> 2) & 1 ) == 0)) {
  if ((pb->pbValue != (*(led->port) >> led->ledPin)) && !(pb->pbValue >> PB_HOLD_MODE0)) {
    ledAction(led);
    // led->ledState = pb->pbValue;

    // if (DEBUG && LED_DEBUG) {
    //   Serial.println("---------------------------------------");
    //   Serial.print("NORMAL MODE * ");
    //   Serial.print((unsigned long)led, HEX);
    //   Serial.print(" -->> LED STATE -->> ");
    //   Serial.print(led->ledState);
    //   Serial.print(" -->> LED PORT STATE -->> ");
    //   Serial.println(*(led->port) >> led->ledPin);
    //   Serial.println("---------------------------------------");
    // } // debug endl
  }

  if (pb->pbValue >> PB_HOLD_MODE0) {
    ledBlink(led, pb->pbHoldDuration);

    // if (DEBUG && LED_DEBUG) {
    //   Serial.println("---------------------------------------");
    //   Serial.print("BLINK MODE * ");
    //   Serial.print((unsigned long)led, HEX);
    //   Serial.print(" -->> LED PORT STATE -->> ");
    //   Serial.println(*(led->port) >> led->ledPin);
    //   Serial.println("---------------------------------------");
    // } // debug endl
  }
}


void PushButtonState(struct pushButton *pb) {

  uint8_t pushButton = ((*(pb->pinRead) & (1 << pb->pbPin)) >> pb->pbPin);
  // if (DEBUG) { pb->pbPrevState = pb->pbState; }
  // if (DEBUG && PB_DEBUG) { Serial.print(" |--> PUSH BUTTON * |--->"); }
  // if (DEBUG && PB_DEBUG) { Serial.print((unsigned long)pb, HEX); }
  // if (DEBUG && PB_DEBUG) { Serial.print(" :--->"); }
  // if (DEBUG && PB_DEBUG) { Serial.println(pushButton); }

  switch (pb->pbState) {
    case 0: pb->pbState = 1; break; /*RESET STATE*/
    case 1:
      if (pushButton == PRESSED) { pb->pbState = 2; }
      break; /*Start reading PB PIN*/
    case 2:
      pb->pbMillis = millis();
      pb->pbState = 3;
      break;
    case 3:
      if (millis() - pb->pbMillis > pb->debDelay) { pb->pbState = 4; }
      if (pushButton == !PRESSED) { pb->pbState = 0; }
      break;
    case 4:
      // testting hold
      // pb->pbMillis = millis();
      if (pushButton == !PRESSED) { pb->pbState = 5; }
      if (millis() - pb->pbMillis > PB_HOLD_DELAY) { pb->pbState = 6; }
      break;
    case 5:
      // pb->pbValue = !(pb->pbValue);
      /*
        pb->pbValue = !(pb->pbValue & 1); 
          !(pb->pbValue & 1) NOT EQUAL to ~(pb->pbValue & 1)
          since pbValue = 0 --> !(pb->pbValue & 1) --> pbValue = 1 
          since pbValue = 0 --> ~(pb->pbValue & 1) --> pbValue = 255
        Alternative
          !(pb->pbValue & 1) EQUAL to (~pb->pbValue & 1)
          since pbValue = 0 --> (~pb->pbValue & 1) --> pbValue = 1
      */
      pb->pbValue = !(pb->pbValue & PB_TOGGLE_MODE0); /*MODE 0 in bit 0 */
      pb->pbState = 0;
      // if (DEBUG && PB_DEBUG) { Serial.println("** PUSH BUTTON TRIGGER **"); }
      // if (DEBUG && PB_DEBUG) { Serial.println(pb->pbValue); }
      break;
    case 6:
      if (pushButton == !PRESSED) { pb->pbState = 7; }
      // pb->pbMillis = millis();
      break;
    case 7:
      pb->pbHoldDuration = millis() - (pb->pbMillis + PB_HOLD_DELAY);
      // pb->pbValue ^= (1 << PB_HOLD_MODE0)  ;
      // pb->pbValue |= (1 << PB_HOLD_MODE0)  ; /*MODE 1 FLAG  in bit  3 */
      /*Keep value bit 0 == 1 in this Mode !! for transition to case 5 and then  pbValue goes to 0 when PB push */
      pb->pbValue = 5; /*MODE 1 FLAG  in bit 3  and + 1 */
      pb->pbState = 0;
      // Serial.println("---------------------------------------");
      // if (DEBUG && PB_DEBUG) { Serial.println("** PUSH BUTTON HOLD **"); }
      // if (DEBUG && PB_DEBUG) { Serial.println("** HOLD DURATION ms **"); }
      // if (DEBUG && PB_DEBUG) { Serial.println(pb->pbHoldDuration); }
      // Serial.println("---------------------------------------");
      break;
  }

  // if (DEBUG && PB_DEBUG) {
  //   if (pb->pbPrevState != pb->pbState) {
  //     // Serial.print(*pb);
  //     Serial.print((unsigned long)pb, HEX);
  //     Serial.print(" --> PUSH BUTTON STATE :  ");
  //     Serial.println(pb->pbState);
  //   }
  // } // debug endl
}

int main() {
  init_millis(16000000UL);
  if (DEBUG) {
    Serial.begin(115200);
    Serial.println("Debugging System Is ON !! ");
  }
  struct led ledred;
  struct led ledgreen;
  ledInit(&ledred, &DDRD, &PORTD, RED_LED);
  ledInit(&ledgreen, &DDRB, &PORTB, GREEN_LED);

  struct pushButton pbred;
  struct pushButton pbgreen;
  pbInit(&pbred, &DDRD, &PIND, RED_PUSH_BUTTON, PB_DEBOUNCE_DELAY);
  pbInit(&pbgreen, &DDRB, &PINB, GREEN_PUSH_BUTTON, PB_DEBOUNCE_DELAY);

  while (1) {
    PushButtonState(&pbred);
    PushButtonState(&pbgreen);
    InputPushButtonToLED(&pbred, &ledred);
    InputPushButtonToLED(&pbgreen, &ledgreen);
  }
  return 0;
}
