
#define SAMPLE 512
// unsigned char rawData[128];
double rawData[SAMPLE];


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);


  // ADCSRA = 0xe5;  // set the adc to free running mode
  // ADMUX = 0x40;   // use adc0
  // DIDR0 = 0x01;   // turn off the digital input for adc0

  //   ADCSRA = 0;             // clear ADCSRA register
  //   ADCSRB = 0;             // clear ADCSRB register
  //   ADMUX |= (0 & 0x07);    // set A0 analog input pin
    // ADMUX |= (1 << REFS0);  // set reference voltage
  //   ADMUX |= (1 << ADLAR);  // left align ADC value to 8 bits from ADCH AREGISTER

    // // sampling rate is [ADC clock] / [prescaler] / [conversion clock cycles]
    // // for Arduino Uno ADC clock is 16 MHz and a conversion takes 13 clock cycles
  // ADCSRA |= (1 << ADPS2) | (1 << ADPS0);  // 32 prescaler for 38.5 KHz
    // ADCSRA |= (1 << ADPS2);  // 16 prescaler for 76.9 KHz
  // ADCSRA |= (1 << ADPS1) | (1 << ADPS0);  // 8 prescaler for 153.8 KHz
  // ADCSRA |= (1 << ADPS1); // Set prescaler ADC ke 2
  //   ADCSRA |= (1 << ADATE);  // enable auto trigger
  //   ADCSRA |= (1 << ADIE);   // enable interrupts when measurement complete
  //   ADCSRA |= (1 << ADEN);   // enable ADC
  //   ADCSRA |= (1 << ADSC);   // enable ADC measurement

  // ISR(ADC_vect) {
  //   byte x = ADCH;  // read 8 bit value from ADC
  // //   // Serial.println(ADCH);
  // }
  // }


  unsigned long mtime, beforetime = micros();

  for (int ii = 0; ii < SAMPLE; ii++) {

    rawData[ii] = analogRead(A0);
  }
  //   rawData[0] = analogRead(A0);
  //   rawData[1] = analogRead(A0);
  //   rawData[2] = analogRead(A0);
  //   rawData[3] = analogRead(A0);
    // rawData[4] = analogRead(A0);
    // rawData[5] = analogRead(A0);
    // rawData[6] = analogRead(A0);
    // rawData[7] = analogRead(A0);
    // rawData[0] = analogRead(A0);
    // rawData[1] = analogRead(A0);
    // rawData[2] = analogRead(A0);
    // rawData[3] = analogRead(A0);
    // rawData[4] = analogRead(A0);
    // rawData[5] = analogRead(A0);
    // rawData[6] = analogRead(A0);
    // rawData[7] = analogRead(A0);
  // unsigned char rawData[256];  // Ubah ukuran array sesuai kebutuhan
  // cli();  // Mematikan interrupt global
  // for (int i = 0; i < 512; i++) {
  //   while (!(ADCSRA & 0x10)); // Menunggu ADC siap
  //   ADCSRA = 0xf5; // Merestart ADC
  //   byte m = ADCL; // Mengambil data ADC
  //   byte j = ADCH;
  //   int k = (j << 8) | m; // Membentuk int
  //   k -= 0x0200; // Membentuk signed int
  //   k <<= 6;
  // k = constrain(k, 0, 255);
  //   rawData[i] = (unsigned char)(k & 0xFF);  // Menyimpan nilai dalam rawData
  // }
  // sei();  // Mengaktifkan kembali interrupt global setelah selesai


  mtime = micros() - beforetime;
  beforetime = mtime;
  Serial.println("MEASURMENT TIME us ");
  Serial.println(mtime);


  Serial.println("DATA : ");
  Serial.println(" ");
  //  int len = sizeof(rawData);
  Serial.print("DATA : ");
  for (int ii = 0; ii < SAMPLE-SAMPLE; ii++) {

    if (ii == SAMPLE-1) {
      Serial.print(rawData[ii]);
    }
    else{
    Serial.print(rawData[ii]);
    Serial.print(",");

    }
  }
  Serial.println("\n");
  Serial.println(" END ");
  // uint8_t ii;
  // while(1){cali();}
}


// the loop routine runs over and over again forever:
void loop() {
    unsigned long mtime, beforetime = micros();

  for (int ii = 0; ii < SAMPLE; ii++) {

    rawData[ii] = analogRead(A0);
  }
    mtime = micros() - beforetime;
  beforetime = mtime;
  Serial.println("MEASURMENT TIME us ");
  Serial.println(mtime);

  // read the input on analog pin 0:

  // int sensorValue = analogRead(A0);
  // Serial.println(sensorValue);

  // cali();
  // Serial.println("\b\b\b\b\b\b\b");
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  // float voltage = analogRead(A0)* (5.0 / 1023.0);
  // print out the value you read:
  // for (int ii = 0 ; ii< sizeof(rawData);ii++){

  // Serial.print(rawData[ii]);
  // }
}
void cali() {

  // ISR(ADC_vect) {
  //   byte x = ADCH;  // read 8 bit value from ADC
  //   numSamples++;
  // }
  // ADCSRA = 0xf5; // Merestart ADC
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
}