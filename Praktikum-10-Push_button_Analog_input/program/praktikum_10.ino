
#define NUM_ONE 0b01100000   /* b c */
#define NUM_TWO 0b11011010   /* a b  d e g*/
#define NUM_THREE 0b11110010 /* a b c d g */
#define NUM_FOUR 0b01100110  /* b c f g */

void setup()
{
    Serial.begin(115200);
    Serial.println("Ready To Reading PIN A0");
    DDRD |= 1 << 7; /*pin  7*/
    PORTD &= 0 << 7;
    DDRB |= 0x3F; /*Semua PORT B pin 8-13*/
    PORTB &= ~0x3F;
    uint8_t input;

    /*loop*/
    while (1)
    {
        input = analogRead(A0) >> 2; /*change to 8 Bit val */
        if (input > 10)
        {
            Serial.println(input);
            PORTD &= ~(1 << 7);
            PORTB &= ~0x3F;
            if (input >= 255)
            {
                PORTB |= NUM_ONE >> 2;
            }
            if (input > 124 && input < 130)
            {
                PORTB |= NUM_TWO >> 2;
                PORTD |= 1 << 7;
            }
            if (input > 82 && input < 88)
            {
                PORTB |= NUM_THREE >> 2;
                PORTD |= 1 << 7;
            }
            if (input > 61 && input < 67)
            {
                PORTB |= NUM_FOUR >> 2;
                PORTD |= 1 << 7;
            }
            delay(1);
        }
        else
        {
            Serial.print("Input < 10 :\t");
            Serial.println(input);
        }
    }
}

void loop() {}