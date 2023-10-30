
/*
 * Praktikum 5
 * Aswin Saputra
 * 31 1221 000 6
 * LED SEquence dari KANAN --> KIRI
 * LED menyala Berurutan
 * LED_4    LED_3   LED_2   LED_1
 * on       off     off     off
 * on       on      off     off
 * on       on      on      off
 * on       on      on      on
 * dan berulang
 */

void setup() {
  DDRD |= 0x3E;
}
void loop() {
  for (byte ii = 1; ii <= 4; ++ii) {
    PORTD |= 0x04 <<3;
    delay(200);
    PORTD |= (PORTD >> 1);
    if (ii == 4) {
      PORTD &= 0x00;
      delay(200);
    }
  }
}