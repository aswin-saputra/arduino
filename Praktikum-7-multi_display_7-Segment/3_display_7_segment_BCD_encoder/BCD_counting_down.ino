/*
    Praktikum 7
    Problem 7b
    Penampil 7 segmen Dengan BCD Counting down
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

        for (uint8_t ii = 9; ii >= 0; --ii)
        {
            PORTB = ii;
            _delay_ms(DELAY_TIME);
            if (!ii)
            {
                break;
            }
        }
    }
}