// #define
bool COM_ANODE = 0;
const byte sevsegNumbers[10] = {
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

bool comAnode(bool sst = 1) {
  return COM_ANODE = sst;
}

bool reveseCountDirection()
{
return 0;
}

byte SPLIT_LSB(byte n) {
  if (COM_ANODE) {
    return (~sevsegNumbers[n] & ~(3 << 6)) << 2;
  } else {
    return (sevsegNumbers[n] & ~(3 << 6)) << 2;
  }
}

byte SPLIT_MSB(byte n) {
  // uint8_t val = sevsegNumbers[n];
  if (COM_ANODE) {
    return (~sevsegNumbers[n] & 0xc0) >> 2;
    // val &= 0xc0 ;
    // val >>=2 ;
  } else {
    return (sevsegNumbers[n] >> 6) << 4;
  }
}

// void sevsegPin(a,b,c,d,e,f,g,dl);{

// }

void setNumberSeq(byte awal = 0, byte akhir = 9, byte speed = 10) {
  if (speed == 0 || speed > 255) { speed = 10; }
  if (awal > akhir || reveseCountDirection()!= 0) {
    for (byte ii = awal; ii >= akhir; ii--) {
      PORTB = SPLIT_MSB(ii);
      PORTD = SPLIT_LSB(ii);
      delay(5000 / speed);
    }
  } else {
    for (byte ii = awal; ii <= akhir; ii++) {
      PORTB = SPLIT_MSB(ii);
      PORTD = SPLIT_LSB(ii);
      delay(5000 / speed);
    }
  }
}
// void setNumber(uint8_t num = 9 ){
// splitBin(num);
// }

void setup() {
  // Serial.begin(9600);
  // DDRD |= 0b11111110;
  // DDRB |= 0b00110000;
  DDRD |= 0xFE;
  DDRB |= 0x30;
  PORTD |= 0x02;
  comAnode(1);
  // Serial.println(SPLIT_LSB(4), BIN);
}

void loop() {
  setNumberSeq();
  delay(1000);
}
