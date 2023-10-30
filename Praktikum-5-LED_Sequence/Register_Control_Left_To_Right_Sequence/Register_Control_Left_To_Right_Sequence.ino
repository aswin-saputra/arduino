
/*
 * Praktikum 5
 * Aswin Saputra
 * 31 1221 000 6
 * LED SEquence dari KIRI --> kanan
 * LED menyala Berurutan
 * LED_1    LED_2   LED_3   LED_4
 * on       off     off     off
 * on       on      off     off
 * on       on      on      off
 * on       on      on      on
 * dan berulang
 */

void setup() {
  DDRD |= B00111100;
  // PORTD |= 0x00;
}
void loop() {

  // PORTD |= 0x04;
  // delay(200);
  for (byte ii = 1; ii <= 4; ++ii) {
    // PORTD |= (PORTD << 1);
    if (ii == 4 || PORTD == 0x3C) {
        PORTD &= 0x00;
    delay(200);
  PORTD = 0x04;
      }
    else {
      PORTD |= (PORTD << 1);
    }
    delay(200);
  }
}