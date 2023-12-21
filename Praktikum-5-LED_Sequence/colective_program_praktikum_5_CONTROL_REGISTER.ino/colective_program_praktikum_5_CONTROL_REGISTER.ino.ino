
/*
Mode :
  1 --> Menyala Dari Kiri --> kanan
  2 --> Menyala Dari kanan --> Kiri
  3 --> Sequence Dari Kiri --> kanan
  4 --> Sequence Dari kanan --> Kiri
*/
void setup() {
  DDRD |= 0x3E;
}

byte Runing_LED_Mode(byte mode = 1, byte speed = 200, byte loop = 2) {
  //   default mode == 1
  // 1 --> Menyala Dari Kiri --> kanan
  // 2 --> Menyala Dari kanan --> Kiri
  // 3 --> Sequence Dari Kiri --> kanan
  // 4 --> Sequence Dari kanan --> Kiri
  //   default speed == 50 ms 0.05 second

  byte sp = speed;
  byte lp = loop;
  byte mo = mode;
  // PORTD = 0x04;

      if (mo == 1 || mo ==3) {
      PORTD |= 0x04;
      }
      else if (mo == 2 || mo == 4) {
      PORTD |= 0x04 << 3;
      }
      else{PORTD |= 0x0c << 1;}

  for (byte ii = 1; ii <= 4; ++ii) {
    if (mo == 1) {
      // PORTD = 0x04;
      delay(sp);
      PORTD <<= 1;
    }

    else if (mo == 2) {
      // PORTD |= 0x04 << 3;
      delay(sp);
      PORTD >>= 1;
    }

    else if (mo == 3) {
      // PORTD |= 0x04;
      delay(sp);
      PORTD |= (PORTD << 1);
      if (ii == 4) {
        PORTD &= 0x00;
        delay(sp);
      }
    }

    else if (mo == 4) {
      // PORTD |= 0x04 << 3;
      delay(sp);
      PORTD |= (PORTD >> 1);
      if (ii == 4) {
        PORTD &= 0x00;
        delay(sp);
      }
    }
    else {
      Runing_LED_Mode(1, 50, 2);
      Runing_LED_Mode(2, 10, 2);
      Runing_LED_Mode(3, 20, 2);
      Runing_LED_Mode(4, 20, 2);
            delay(sp);
      PORTD |= (PORTD >> 1)^(PORTD << 1);
      if (ii == 4) {
        PORTD &= 0x00;
        delay(sp);
        PORTD |= 0x0c;

      }
    }
    }
  }

  void loop() {
    Runing_LED_Mode(1,20);
    delay(100);
    Runing_LED_Mode(2,50);
    delay(100);
    Runing_LED_Mode(3,20);
    delay(100);
    Runing_LED_Mode(4,20);
    delay(100);
    Runing_LED_Mode(5,20); // chaos MODE 
    // delay(1000);
  }
