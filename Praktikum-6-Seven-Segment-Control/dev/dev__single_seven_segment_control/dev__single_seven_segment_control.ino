// Seven Segment Led Configuration 
//                                      pin 
                           // DEC HEX abcdefgdl
#define SEV_SEG_ZERO 0xFC  //  0  FC  11111100
#define SEV_SEG_ONE 0x60   //  1  60  01100000
#define SEV_SEG_TWO 0xDA   //  2  DA  11011010
#define SEV_SEG_TREE 0xF2  //  3  F2  11110010
#define SEV_SEG_FOUR 0x66  //  4  66  01100110
#define SEV_SEG_FIVE 0xB6  //  5  B6  10100110
#define SEV_SEG_SIX 0xBE   //  6  BE  10101110
#define SEV_SEG_SEVEN 0xE0 //  7  E0  11100000
#define SEV_SEG_EIGHT 0xFE //  8  FE  11111110
#define SEV_SEG_NINE 0xF6  //  9  F6  11110110

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
#define VAL_CHECK(start_val,end_val) \
(((start_val <  MIN_VAL)||(start_val >  MAX_VAL)) ? \
MIN_VAL : (start_val < end_val) ? MAX_VAL: start_val )


// *********************************

// *********************************



// bool COM_ANODE = 0;
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

// #define NM[]
  // uint8_t SEGMENT_MAP[10];

// uint8_t pinSEGMENT_map[8];
// uint8_t pinSEGMENT_map[8];
bool comAnode(bool sst = 1) {
  return sst;
}

bool reveseCountDirection() {
  return 0;
}
uint8_t SPLIT_LSB(uint8_t n) {
  uint8_t sevsegNumbers[] = { SEVEN_SEGMENT_NUM_ELE };
  if (comAnode()) {
    return (~sevsegNumbers[n] & ~(3 << 6)) << 2;
  } else {
    return (sevsegNumbers[n] & ~(3 << 6)) << 2;
  }
}

uint8_t SPLIT_MSB(uint8_t n) {
  uint8_t sevsegNumbers[] = { SEVEN_SEGMENT_NUM_ELE };
  // uint8_t val = sevsegNumbers[n];
  if (comAnode()) {
    return (~sevsegNumbers[n] & 0xc0) >> 2;
    // val &= 0xc0 ;
    // val >>=2 ;
  } else {
    return (sevsegNumbers[n] >> 6) << 4;
  }
}

// void sevsegPin(a,b,c,d,e,f,g,dl);{

// }

// void setNumberSeq(uint8_t awal = 0, uint8_t akhir = 9, uint8_t speed = 10) {
//   if (speed == 0 || speed > 250) { speed = 10; }
//   if (awal > akhir || reveseCountDirection() != 0) {
//     for (uint8_t ii = awal; ii >= akhir; ii--) {
//       PORTB = SEGMENT_MAP[ii] >> 2;
//       PORTD = SEGMENT_MAP[ii] << 2;
//     Serial.println(SEGMENT_MAP[ii], HEX);
//       delay(5000 / speed);
//     }
//   } else {
//     for (uint8_t ii = awal; ii <= akhir; ii++) {
//       PORTB = SEGMENT_MAP[ii] >> 2;
//       PORTD = SEGMENT_MAP[ii] << 2;
//       delay(5000 / speed);
//     }
//   }
// }


void setNumberSeq(uint8_t awal = 0, uint8_t akhir = 9, uint8_t speed = 25) {
  if (speed == 0 || speed > 250) { speed = 10; }
  if (awal > akhir || reveseCountDirection() != 0) {
    for (uint8_t ii = awal; ii > akhir; ii--) {
      PORTB = SPLIT_MSB(ii);
      PORTD = SPLIT_LSB(ii);
      delay(5000 / speed);
    }
  } else {
    for (uint8_t ii = awal; ii <= akhir; ii++) {
      PORTB = SPLIT_MSB(ii);
      PORTD = SPLIT_LSB(ii);
      delay(5000 / speed);
    }
  }
}





// void setNumber(uint8_t num = 9 ){
// splitBin(num);
// }
// uint8_t storeNewSEGMENT_Map() {
//   uint8_t SEGMENT_mapVAR[10];
//   for (uint8_t ii = 0; ii <= 9; ii++) {
//     SEGMENT_mapVAR[ii] = (SPLIT_MSB(ii) << 2) | (SPLIT_LSB(ii) >> 2);
//     // Serial.println(SPLIT_MSB(ii) , BIN);
//     Serial.println(SPLIT_LSB(ii), HEX);
//     // Serial.println(SEGMENT_mapVAR[ii], BIN);
//   }
//   return SEGMENT_mapVAR;
// }


void setup() {
  // Serial.begin(9600);
  // DDRD |= 0b11111110;
  // DDRB |= 0b00110000;
  DDRD |= 0xFE;
  DDRB |= 0x30;
  PORTD |= 0x02;
  comAnode(1);
  // uint8_t SEGMENT_MAP = storeNewSEGMENT_Map();
  // Serial.println(SEGMENT_MAP, BIN);
}

void loop() {
  setNumberSeq();
  // delay(1000);
    // storeNewSEGMENT_Map();
  // Serial.println(SEGMENT_MAP, BIN);
  // Serial.println(storeNewSEGMENT_Map(), BIN);

}
