
/*
INTRUKSI 1
a.  Membuat untai antarmuka mikrokontroler (Arduino) dengan 4 buah LED sedemikian
    LED menyala jika saluran output diberi logika 0.
b.  Membuat program untuk mengendalikan untai pada no 1,
    sehingga LED menyala bergantian dan berulang secara terus menerus
*/

/* Progrma Properties
  * Sketch uses 280 bytes (0%) of program storage space
  * Global variables use 0 bytes (0%) of dynamic memory
*/
#include <util/delay.h>
#define DELAY 50
void wait();

void wait(unsigned int ms) {
    for (unsigned int i = 0; i < ms; ++i) {
        _delay_ms(1);
    }
}
int main(){

    DDRD |= 0xC; /*PIN 2 & 3*/
    DDRB |= 0x03; /*PIN 8 & 9*/
    PORTD |= 0x0C;
    PORTB |= 0x03;

for (;;){
    PORTD |= 0x0C;
    PORTB |= 0x03;

	PORTB ^= 1 << 1;
    wait(DELAY);
	PORTB ^= 1 << 1;
    wait(DELAY);
    PORTB ^= 1 << 0;
    wait(DELAY);
    PORTB ^= 1 << 0;
    wait(DELAY);
    PORTD ^= 1 << 3;
    wait(DELAY);
    PORTD ^= 1 << 3;
    wait(DELAY);
    PORTD ^= 1 << 2;
    wait(DELAY);
    PORTD ^= 1 << 2;
    wait(DELAY);
}
}