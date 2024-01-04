// main.c
#include <avr/io.h>
#include <util/atomic.h>
#include <avr/interrupt.h>

#define ACTIVE_HIGH 1
#define ACTIVE_LOW 0
#define LED_RED 2
#define LED_YELOW 3
#define LED_GREEN 0
#define LED_BLUE 1

void ledInit();
void ledSetup();
void ledBlink();

typedef struct led {
  volatile uint8_t *ddr;
  volatile uint8_t *port;
  uint8_t ledPIn;
  uint8_t ledPinConfig;
  unsigned int timeON;
  unsigned int timeOFF;
  unsigned long ledMillis;
} led;

void ledInit(
  struct led *led,
  volatile uint8_t *ddr,
  volatile uint8_t *port,
  uint8_t ledPIn,
  uint8_t ledPinConfig,
  unsigned int timeON,
  unsigned int timeOFF,
  unsigned long ledMillis) {
  led->ddr = ddr;
  led->port = port;
  led->ledPIn = ledPIn;
  led->timeON = timeON;
  led->timeOFF = timeOFF;
  led->ledPinConfig = ledPinConfig;
  led->ledMillis = ledMillis;
}

void ledSetup(struct led *led) {

  *(led->ddr) |= (1 << led->ledPIn);  // DDRx OUTPUT MODE

  ((led->ledPinConfig) == 0) ? *(led->port) |= (1 << led->ledPIn) : *(led->port) &= ~(1 << led->ledPIn);
  // *(led->port) |= (1 << led->ledPIn);// PORTx init State HIGH
  // *(led->port) &= ~(1 << led->ledPIn);// PORTx init State LOW
}

void ledBlink(struct led *led) {
  // *(led->ledMillis) = millis();
  // static unsigned long ledMillis = millis();

  if ((millis() - (led->ledMillis)) > led->timeON) {
    *(led->port) ^= (1 << led->ledPIn);
    (led->ledMillis) = millis();
  }
}


//NOTE: A unsigned long holds values from 0 to 4,294,967,295 (2^32 - 1). It will roll over to 0 after reaching its maximum value.
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

int main() {
  init_millis(16000000UL);
  struct led LEDRed0;
  struct led LEDYellow0;
  struct led LEDGreend0;
  struct led LEDBlue0;
  // led LEDRed1;
  // led LEDRed2;
  ledInit(&LEDRed0  ,     &DDRD, &PORTD, LED_RED,   ACTIVE_LOW, 500, 500,0);
  ledInit(&LEDYellow0 ,   &DDRD, &PORTD, LED_YELOW, ACTIVE_LOW, 500, 500,0);
  ledInit(&LEDGreend0 ,   &DDRB, &PORTB, LED_GREEN, ACTIVE_LOW, 800, 500,0);
  ledInit(&LEDBlue0 ,     &DDRB, &PORTB, LED_BLUE,  ACTIVE_LOW, 100, 500,0);

  ledSetup(&LEDRed0);
  ledSetup(&LEDYellow0);
  ledSetup(&LEDGreend0);
  ledSetup(&LEDBlue0);


  while (1) {

    ledBlink(&LEDRed0);
    ledBlink(&LEDYellow0);
    ledBlink(&LEDGreend0);
    ledBlink(&LEDBlue0);
  }
  return 0;
}