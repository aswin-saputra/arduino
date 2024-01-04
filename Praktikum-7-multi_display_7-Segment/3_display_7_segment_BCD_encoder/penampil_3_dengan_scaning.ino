/*

Penampil 7 segmen Dengan SCANING
comm chatode 
*/

#include <avr/io.h>
#include <util/atomic.h>
#include <avr/interrupt.h>
// #include <util/delay.h>

#define pina 2
#define pinb 3
#define pinc 4
#define pind 5
#define coma 10
#define comb 9
#define comc 8
#define timedelay 50
#define NIM 006

/*active High*/
const uint8_t sevsegNumbersMap[10] = {
  0xFC,  // Angka 0
  0x60,  // Angka 1
  0xDA,  // Angka 2
  0xF2,  // Angka 3
  0x66,  // Angka 4
  0xB6,  // Angka 5
  0xBE,  // Angka 6
  0xE0,  // Angka 7
  0xFE,  // Angka 8
  0xF6,  // Angka 9
};

void displaynum(int);
void sevSeginit();
void sevPinConfig();

    struct sevSegPlain
{
    volatile uint8_t *ddr;
    volatile uint8_t *port;
    uint8_t sevSegPin[8];
    uint8_t segPinA; 
    uint8_t segPinB; 
    uint8_t segPinC; 
    uint8_t segPinD; 
    uint8_t segPinE; 
    uint8_t segPinF; 
    uint8_t segPinG; 
    uint8_t segComm; 
    unsigned long sevSegMillis;
};

struct pushButton
{
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

void pbInit(
    struct pushButton *pb,
    volatile uint8_t *ddr,
    volatile uint8_t *pinRead,
    uint8_t pbPin,
    uint8_t debDelay)
{
    pb->ddr = ddr;
    pb->pinRead = pinRead;
    pb->pbPin = pbPin;
    pb->debDelay = debDelay;
    pb->pbState = 0;
    if (DEBUG)
    {
        pb->pbPrevState = 0;
    }
    pb->pbValue = 0;
    pb->pbHoldDuration = 0;
    *(pb->ddr) &= ~(1 << pb->pbPin);
}

void numbersToDDR(){

}
void sevPinConfig(//* pin,com,Segmenttype
    struct sevSegPlain *,
    volatile uint8_t *ddr,

){

}



void sevSeginit(){
    // set pin to output
    *(led->ddr) |= (1 << led->ledPin);
}

void displaynum(int num)
{
    uint8_t digit1 = num / 100;
    uint8_t digit2 = (num / 10) - (10 * digit1);
    uint8_t digit3 = num - (100 * digit1 + 10 * digit2);
}
