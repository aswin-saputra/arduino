


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



pinMode(12,INPUT)
PinMode()

DDRB |= _BV(DDB5)

_BV(DDB0)
_BV(DDB1)
_BV(DDB2)
_BV(DDB3)
_BV(DDB4)
_BV(DDB5)
_BV(DDB6)
_BV(DDB7)

_BV(DDD0)
_BV(DDD1)
_BV(DDD2)
_BV(DDD3)
_BV(DDD4)
_BV(DDD5)
_BV(DDD6)
_BV(DDD7)

 _delay_ms()

B00000000
DDRB
DDD1
#define SET_PIN_TO_PORT (port,ddr_bit) (DDR ## port |= (1 << pin))
// #define SET_PORT_D(ddr_bit) (DDRD |= (1 << pin))

#define SEV_SEG_PIN_SET uint8_t SSPIN_ARRAY[8]


#ifdef SET_PIN_PORT_C
switch(PIN_S ){
 case A0:
 SET_PIN_TO_PORT(C,0); // do something if i is 0
 break;
 case A1: // do something if i is 0
 SET_PIN_TO_PORT(C,1); // do something if i is 0
 break;
 case A2: // do something if i is 1
 SET_PIN_TO_PORT(C,2); // do something if i is 0
 break;
 case A3: // do something if i is 0
 SET_PIN_TO_PORT(C,3); // do something if i is 0
 break;
 case A4: // do something if i is 1
 SET_PIN_TO_PORT(C,4); // do something if i is 0
 break;
 case A5: // do something if i is 0
 SET_PIN_TO_PORT(C,5); // do something if i is 0
 break;
 default: // if no case matched run code in default
 break;
}

#endif


#ifdef SET_PIN_PORT_B
switch(PIN_S ){
 case 8:
 SET_PIN_TO_PORT(B,0); // do something if i is 0
 break;
 case 9: // do something if i is 0
 SET_PIN_TO_PORT(B,1); // do something if i is 0
 break;
 case 10: // do something if i is 1
 SET_PIN_TO_PORT(B,2); // do something if i is 0
 break;
 case 11: // do something if i is 0
 SET_PIN_TO_PORT(B,3); // do something if i is 0
 break;
 case 12: // do something if i is 1
 SET_PIN_TO_PORT(B,4); // do something if i is 0
 break;
 case 13: // do something if i is 0
 SET_PIN_TO_PORT(B,5); // do something if i is 0
 break;
 default: // if no case matched run code in default
 break;
}
#endif


#ifdef SET_PIN_PORT_D
switch(PIN_S ){
 case 0:
 SET_PIN_TO_PORT(D,0); // do something if i is 0
 break;
 case 1: // do something if i is 0
 SET_PIN_TO_PORT(D,1); // do something if i is 0
 break;
 case 2: // do something if i is 1
 SET_PIN_TO_PORT(D,2); // do something if i is 0
 break;
 case 3: // do something if i is 0
 SET_PIN_TO_PORT(D,3); // do something if i is 0
 break;
 case 4: // do something if i is 1
 SET_PIN_TO_PORT(D,4); // do something if i is 0
 break;
 case 5: // do something if i is 0
 SET_PIN_TO_PORT(D,5); // do something if i is 0
 break;
 case 6: // do something if i is 1
 SET_PIN_TO_PORT(D,6); // do something if i is 0
 break;
 case 7: // do something if i is 1
 SET_PIN_TO_PORT(D,7); // do something if i is 0
 break;
 default: // if no case matched run code in default
 break;
}
#endif


#define PIN_S uint8_t SSPIN_ARRAY[ii]
#define BEGIN_SET_PIN (\
for (uint8_t ii=0;ii<=8;ii++){\
if(PIN_S  <= 7 && PIN_S  >= 0 ){\
  // SET PIN To PORT D 
  SET_PIN_PORT_D (PIN_S);}\
else if { PIN_S >=8 && PIN_S <= 13}{\
// SET PIN To PORT B 
  SET_PIN_PORT_B (PIN_S);\
}\
else if { PIN_S >=8 && PIN_S <= 13}{\
  SET_PIN_PORT_B (PIN_S);\
// SET PIN To PORT C 
// #warning " analog Pin Set to output"
}\
else {\
// #warning "Maybe Problem With Seven Segment Pin Configuration"
// #warning "Please Check Again Pin configuratiion"
}\
}\

// PIN SELECTION

// void sevSegPin( uint8_t PIN_A
//                 uint8_t PINB_B,
//                 uint8_t PINA_C,
//                 uint8_t PINB_D,
//                 uint8_t PINB_E,
//                 uint8_t PINA_F,
//                 uint8_t PINB_G,
                // uint8_t PINA_DL){
void sevSegPin( SEV_SEG_PIN_SET){
BEGIN_SET_PIN();
}
