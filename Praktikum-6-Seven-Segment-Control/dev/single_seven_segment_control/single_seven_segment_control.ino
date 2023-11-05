// #define
bool COM_ANODE = 0;
const uint8_t sevsegNumbers[10] = {
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
uint8_t SPLIT_LSB(uint8_t n = 9) {
  // val = (sevsegNumbers[n] & ~(3 << 6)) << 2;
  uint8_t val = sevsegNumbers[n];
  if (COM_ANODE) {
    val = (~val & ~(3 << 6)) << 2;
  } else {
    val = (val & ~(3 << 6)) << 2;
  }
  return val;
}

uint8_t SPLIT_MSB(uint8_t n = 9) {
  uint8_t val = sevsegNumbers[n];
  if (COM_ANODE==1) {
    val = ~val ;
    val &= 0xc0 ;
    val >>=2 ;
  } else {
    val = (val >> 6) << 4;
  }
  return val;
}

// void sevsegPin(a,b,c,d,e,f,g,dl);{

// }

void setNumberSeq(uint8_t awal = 0, uint8_t akhir = 9, uint8_t speed = 10) {
  // PORTB = (sevsegNumbers[ii-1] >> 6)<<4 ;//MSB
  if (speed == 0) { speed += 10; }
  for (uint8_t ii = awal; ii <= akhir; ii++) {
    PORTB = SPLIT_MSB(ii);
    // Serial.println(SPLIT_MSB(ii), HEX);
    PORTD = SPLIT_LSB(ii);
    // Serial.println(SPLIT_LSB(ii), HEX);
    delay(2000 / speed);
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
  // for (uint8_t ii = 1; ii <= 10; ii++) {
  //   PORTB |= 0x00;
  //   // delay(100*i*i);
  // }
  // // splitBin();
  // delay(1000);

  // setNumberSeq();
  // delay(100);
  // Serial.println(SPLIT_LSB(),HEX);
  // Serial.println(SPLIT_LSB());
  // SPLIT_LSB();
  // delay(1000);
  setNumberSeq();
  // delay(1000);
}
