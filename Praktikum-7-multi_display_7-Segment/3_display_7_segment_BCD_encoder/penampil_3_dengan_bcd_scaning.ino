/*

Penampil 7 segmen Dengan BCD dan SCANING

*/

/* 3 display Common cathode
   encoder BCD to 7segment  CD 4511
*/
#define pina 2
#define pinb 3
#define pinc 4
#define pind 5
#define coma 10
#define comb 9
#define comc 8
#define timedelay 50
#define NIM 006

void setup()
{
    pinMode(pina, OUTPUT);
    pinMode(pinb, OUTPUT);
    pinMode(pinc, OUTPUT);
    pinMode(pind, OUTPUT);
    pinMode(coma, OUTPUT);
    pinMode(comb, OUTPUT);
    pinMode(comc, OUTPUT);
    digitalWrite(coma, HIGH);
    digitalWrite(comb, HIGH);
    digitalWrite(comc, HIGH);
}
void displaynum(int num)
{
    uint8_t digit1 = num / 100;
    uint8_t digit2 = (num / 10) - (10 * digit1);
    uint8_t digit3 = num - (100 * digit1 + 10 * digit2);

    int kk = 0;
    do
    {
        PORTD &= 0x00;
        PORTD |= (digit1 << 2);
        PORTB &= 0x03;
        delay(timedelay);

        // PORTD &= 0x00;
        PORTD ^= (digit1 << 2);
        PORTD |= (digit2 << 2);
        PORTB ^= 0x06;
        delay(timedelay);

        // PORTD &= 0x00;
        PORTD ^= (digit2 << 2);
        PORTD |= (digit3 << 2);
        PORTB ^= 0x03;
        delay(timedelay);

        PORTD ^= (digit3 << 2);
        PORTB += 0x01;
        kk++;
    } while (kk < 6);
}
void loop()
{

    for(int ii = 0 ; ii < NIM; ++ii )
    {
    displaynum(ii);
        delay(1);
    }
    for(;;){displaynum(NIM);}
    
}