// Seven Segment Led Configuration
//                                      pin
//                             DIS HEX abcdefgdl
#define SEV_SEG_ZERO 0xFC   //  0  FC  11111100
#define SEV_SEG_ONE 0x60    //  1  60  01100000
#define SEV_SEG_TWO 0xDA    //  2  DA  11011010
#define SEV_SEG_TREE 0xF2   //  3  F2  11110010
#define SEV_SEG_FOUR 0x66   //  4  66  01100110
#define SEV_SEG_FIVE 0xB6   //  5  B6  10100110
#define SEV_SEG_SIX 0xBE    //  6  BE  10101110
#define SEV_SEG_SEVEN 0xE0  //  7  E0  11100000
#define SEV_SEG_EIGHT 0xFE  //  8  FE  11111110
#define SEV_SEG_NINE 0xF6   //  9  F6  11110110

#define SEVEN_SEGMENT_NUM_ELE SEV_SEG_ZERO, \
                              SEV_SEG_ONE, \
                              SEV_SEG_TWO, \
                              SEV_SEG_TREE, \
                              SEV_SEG_FOUR, \
                              SEV_SEG_FIVE, \
                              SEV_SEG_SIX, \
                              SEV_SEG_SEVEN, \
                              SEV_SEG_EIGHT, \
                              SEV_SEG_NINE
#define MIN_VAL 0
#define MAX_VAL 9

#ifndef DIGIT_CHECK
#define DIGIT_CHECK(a, b) (((a >= MIN_VAL) && (a <= MAX_VAL)) && ((b >= MIN_VAL) && (b <= MAX_VAL))) ? 1 : 0
#endif

/*

Smentara untuk PIN diset tetap::
a  b  c d e f g dl
13 12 7 6 5 4 3 2

*/

// const uint8_t sevsegNumbers[10] = {
//   0xFC,  // Angka 0
//   0x60,  // Angka 1
//   0xDA,  // Angka 2
//   0xF2,  // Angka 3
//   0x66,  // Angka 4
//   0xB6,  // Angka 5
//   0xBE,  // Angka 6
//   0xE0,  // Angka 7
//   0xFE,  // Angka 8
//   0xF6,  // Angka 9
// };
// const uint8_t PROGMEM sevsegNumbers[10] = {SEVEN_SEGMENT_NUM_ELE };
const uint8_t sevsegNumbers[10] = { SEVEN_SEGMENT_NUM_ELE };

bool comAnodeToggle = 1;
void comAnode(bool sst) {
  if (sst == 0) {
    comAnodeToggle = 0;
  } else if (sst == 1) {
    comAnodeToggle = 1;
  }
  /* nilai 1 untuk tipe common anoda dan 0 untuk com Chatode*/
}

uint8_t SPLIT_LSB(uint8_t n) {
  // uint8_t sevsegNumbers[] = { SEVEN_SEGMENT_NUM_ELE };
  if (comAnodeToggle) {
    return (~sevsegNumbers[n] & ~(3 << 6)) << 2;
  } else {
    return (sevsegNumbers[n] & ~(3 << 6)) << 2;
  }
}

uint8_t SPLIT_MSB(uint8_t n) {
  // uint8_t sevsegNumbers[] = { SEVEN_SEGMENT_NUM_ELE };
  if (comAnodeToggle) {
    return (~sevsegNumbers[n] & 0xc0) >> 2;
  } else {
    return (sevsegNumbers[n] >> 6) << 4;
  }
}


void segmentBlink(uint8_t num, uint8_t ms = 100) {
  PORTB = SPLIT_MSB(num);
  PORTD = SPLIT_LSB(num);
  delay(ms);
}


void dotBlink(uint8_t ms) {
  if (comAnodeToggle) {
    PORTD |= 0xF8;
    PORTB |= 0x30;
    delay(ms);
    PORTD ^= 0x0D;
    delay(ms);
  } else {
    PORTD &= 0x00;
    PORTD |= 0x05;
    PORTB &= 0x00;
    delay(ms * 2);
    PORTD ^= 0x0D;
    delay(ms);
  }
}


void dash(uint8_t n = 5) {
  uint8_t ii = 0;
  do {
    dotBlink(50);
    // setNumberSeq(10, 10, 1000);
    delay(n);
    ii++;
  } while (ii < n);
}

void setNumberSeq(uint8_t awal = 0, uint8_t akhir = 9, uint8_t speed = 25) {
  if (speed == 0 || speed > 250) { speed = 10; }
  // bool valChk = 0;
  bool valChk = DIGIT_CHECK(awal, akhir);

  //   if ((awal >= 0) && (awal <= 9) && (akhir <= 9) && (akhir >= 0)) {
  //     valChk = 1;
  //   } else {
  //     valChk = 0;
  //   }
  // }
  // else {
  //   valChk = 0;
  // }


  if ((awal > akhir) && valChk) {
    for (uint8_t ii = awal + 1; ii > akhir; ii--) {
      PORTB = SPLIT_MSB(ii - 1);
      PORTD = SPLIT_LSB(ii - 1);
      delay(5000 / speed);
    }
  } else if ((awal < akhir) && valChk) {
    for (uint8_t ii = awal; ii <= akhir; ii++) {
      PORTB = SPLIT_MSB(ii);
      PORTD = SPLIT_LSB(ii);
      delay(5000 / speed);
    }
  } else if (!valChk) {
    dotBlink(50);
  } else {
    segmentBlink(awal);
  }
}


void setup() {
  DDRD |= 0xFE;
  DDRB |= 0x30;
  PORTD |= 0x02;
  // comAnode(1);  // Set 1 unutk com anode dan set 0 jika com cathode
  comAnode(0);  // Set 1 unutk com anode dan set 0 jika com cathode
  dotBlink(200);
}

void loop() {

  /* tambahan dari fungsi < dotBlink() > Menampilkan Dash */
  // dash();

  /*  setNumberSeq(0,9,10); <nilai awal, nilai akhir , delay 500 ms>
      counting Naik dari o sampai 9 dan berulang */
  // setNumberSeq(0,9,20);
  // delay(1000);

  /*  setNumberSeq(9,0,10);
      counting turun dari 9 sampai 0 dan berulang */
  // setNumberSeq(9,0,5);
  // delay(1000);

  /*  jika awal == akhir maka akan display angka tersebut */
  // setNumberSeq(6,6);
  // delay(1000);

  /*  jika nilai masukan diluar 0-9 maka akan menampilkan "dash" */
  // setNumberSeq(90,99,10);
  // delay(1000);

  setNumberSeq();
  delay(100);
  setNumberSeq(0, 9, 20);
  delay(100);
  setNumberSeq(9, 0, 30);
  delay(100);
  setNumberSeq(0, 5, 200);
  dash(10);
  setNumberSeq(7, 6, 100);
  delay(100);

  for (int ii = 0; ii < 10; ++ii) {
    for (int jj =10; jj > 0; --jj) {
      setNumberSeq(jj == ii ? --jj:ii, jj == ii ? ++ii:jj, 50);
      setNumberSeq(jj == ii ? --jj:jj, jj == ii ? ++ii:ii, 50);
    }}
  delay(100);
  }