/*
 * Praktikum 5
 * Aswin Saputra
 * 31 1221 000 6
 * LED SEquence dari KIRI --> kanan
 * LED menyala Bergatian
 * LED_1    LED_2   LED_3   LED_4
 * ON       OFF     OFF     OFF
 * OFF      ON      OFF     OFF
 * OFF      OFF     ON      OFF
 * OFF      OFF     OFF     ON
 * dan berulang
 */

void setup() {
  // Sett PORT D menjadi input untuk 
  // DDRD |= B00111100;
  // pin 2, 3, 4, 5
  DDRD |= 0x3E;
  // set nilai awal di PORT D menjadi 0
  PORTD = 0x0;
}

void loop() {
  PORTD = 0x04;
  for (byte ii = 1; ii <= 4; ++ii) {
    delay(250);
    PORTD <<= 1;
  }
}
