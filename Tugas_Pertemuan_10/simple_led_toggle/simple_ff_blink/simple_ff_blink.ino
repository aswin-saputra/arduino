/*
Tugas Pertemuan 10 
Aswin Saputra 3112210006
24 Nov 23
*/

/*
1.  Buatlah diagram skematik antarmuka 4 buah LED dengan arduino uno,
    sedemikian sehingga LED menyala jika output arduino diberi logika tinggi (HIGH).

2.  Buatlah program arduino untuk mengendalikan rangkaian di atas
    sedemikian sehingga 2 buah LED menyala dan 2 buah LED mati secara bergantian.
*/


/*
  202 bytes (1%) of program storage space
  Global variables use 0 bytes (0%) of dynamic memory
*/

#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 16000000
#endif

#include <util/delay.h>
#define DELAY_TIME 300

#define N_PIN 4

/*make data structur for led properties*/
struct led_patern {
  uint8_t patern[6];
  // uint8_t n_led;
  // volatile uint8_t *led_pin_ddr;
  // volatile uint8_t *led_pin_port;
} patern;


/*delay function*/
void wait(unsigned int ms) {
  for (unsigned int i = 0; i < ms; ++i) {
    _delay_ms(1);
  }
}
/*flip-flop blink function*/
void ff_blink(uint8_t array_patern, unsigned int ms = 100) {

  // turn LED on
  PORTD |= array_patern << N_PIN;
  wait(ms);

  // turn LED off
  PORTD &= ~(array_patern << N_PIN);
  wait(ms);

  // contra LED
  // turn LED on
  PORTD |= ~array_patern << N_PIN;
  wait(ms);

  // turn LED off
  PORTD &= (array_patern << N_PIN);
  wait(ms);
};

/*main function*/
int main(void) {
  DDRD |= 0xF0; /* Set Pin 4 5 6 7 as Output */
  /*
  kombinasi dari 4 buah LED yang menyala hanya 2 = 6 kombinasi
  nCr(4,2) = 6
  0011 dan ~(0011) 
  0101 dan ~(0101)
  0110 dan ~(0110)
   */
  struct led_patern mypatern1 = { { 3, 5, 9 } };


/* ***********************************************
**   PATERN 1 :  0011 --> 1100
**    ff_blink(mypatern1.patern[0]);
**    Equivalent to :
**
**    PORTD |= 0x30;    turn on led pin 5 4   PORTD
**    _delay_ms(100); 
**   
**    PORTD &= ~0x30;   turn off led pin 5 4  PORTD
**    _delay_ms(100);
**
**    PORTD |= 0xC0;    turn on led pin 7 6 PORTD
**    _delay_ms(100);
**
**    PORTD &= ~0xC0;   turn off led pin 7 6 PORTD
**    _delay_ms(100);
************************************************/ 

/* ***********************************************
**   PATERN 2 :  0101 --> 1010
**    ff_blink(mypatern1.patern[1],20);
**    Equivalent to :
**
**    PORTD |= 0x50;    turn on led pin 6 4  PORTD
**    _delay_ms(20); 
**   
**    PORTD &= ~0x50;   turn off led pin 6 4  PORTD
**    _delay_ms(20);
**
**    PORTD |= 0xA0;    turn on led pin 7 5 PORTD
**    _delay_ms(20);
**
**    PORTD &= ~0xA0;   turn off led pin 7 5 PORTD
**    _delay_ms(20);
************************************************/
 
/************************************************
**   PATERN 3 :  1001 --> 0110
**    ff_blink(mypatern1.patern[2],500);
**    Equivalent to :
**
**    PORTD |= 0x90;    turn on led pin 7 4  PORTD
**    _delay_ms(500)); 
**   
**    PORTD &= ~0x90;   turn off led pin 7 4  PORTD
**    _delay_ms(500));
**
**    PORTD |= 0x60;    turn on led pin 6 5 PORTD
**    _delay_ms(500));
**
**    PORTD &= ~0x60;   turn off led pin 6 5 PORTD
**    _delay_ms(500));
************************************************/

/************************************************
** Another Patern
    ff_blink(3);
    ff_blink(5);
    ff_blink(6);
    ff_blink(9);
    ff_blink(10);
    ff_blink(12);
************************************************/

  /*Make loop*/
  while (1) {
    ff_blink(mypatern1.patern[0]);
    // ff_blink(mypatern1.patern[1], 20);
    // ff_blink(mypatern1.patern[2], 500);
  }
  return 0;
}
