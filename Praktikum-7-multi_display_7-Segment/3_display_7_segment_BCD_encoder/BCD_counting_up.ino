/*
    Praktikum 7
    Problem 7a
    Penampil 7 segmen Dengan BCD Counting UP
    Comm Cathode
*/

#include <avr/io.h>
#define DELAY_TIME 500
#include <util/delay.h>
int main(void)
{
    DDRB |= 0x0F;  /*PIN A B C D */
    PORTB |= 0x00; /*|->8 9 10 11 */

    while (1)
    {

        for (uint8_t ii = 0; ii <= 9; ++ii)
        {
            PORTB = ii;
            _delay_ms(DELAY_TIME);
            // if (ii > 9)
            // {
            //     PORTB & 0x00;
            // }
            ii > 9 ? PORTB & 0x00 : 0;
        }
    }
}