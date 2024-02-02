
#include "arduinoFFT.h"

arduinoFFT FFT;

// void getData(char pin, int rawSample, int s, char fac);
void getData(char pin, int rawSample);
double getFFT(double vReal[], double vImag[], int s, int fs);

#define CHANNEL A0
#define RAW_SAMPLE 512
#define SAMPLE 128
// #define FACTOR 2
#define FACTOR (RAW_SAMPLE / SAMPLE) /* Doenscale Factor*/

// const uint16_t samples = 128;  //This value MUST ALWAYS be a power of 2
// const uint16_t samples = 128; //This value MUST ALWAYS be a power of 2

// const double samplingFrequency = 100; //Hz, must be less than 10000 due to ADC
// const double samplingFrequency = 8064; //Hz, must be less than 10000 due to ADC
// const double samplingFrequency = 7812; //Hz, must be less than 10000 due to ADC
// const double samplingFrequency = 8000.00; //Hz, must be less than 10000 due to ADC
// const double samplingFrequency = 9009.01; //Hz, must be less than 10000 due to ADC
// const double samplingFrequency = 8620.69; //Hz, must be less than 10000 due to ADC
// const double samplingFrequency = 8771.93;  //Hz, must be less than 10000 due to ADC + 6
// const double samplingFrequency = 8547;  //Hz, must be less than 10000 due to ADC + 6
// const double samplingFrequency = 8889.24 ; //Hz, must be less than 10000 due to ADC DIFF -(0.01-.44)
// const double samplingFrequency = 8945;  //Hz, must be less than 10000 due to ADC DIFF


// #define F_SAMPLING 8945.0  //Hz, must be less than 10000 due to ADC DIFF
// #define BASE_FS 8923.28 // F Measument at sample 512
#define BASE_FS 8922.34 // F Measument at sample 512 with tuning 
#define F_SAMPLING (BASE_FS / FACTOR)   // F Measument at sample 512
// #define F_SAMPLING (8945.0 / FACTOR)  

double vReal[SAMPLE];
double vImag[SAMPLE];
double peakFreq;

#define TONE_TARGET 440 // A4
void setup() {
  Serial.begin(115200);
  // while (!Serial);
  Serial.println("Ready");

  // ADCSRA = 0xe5;  // set the adc to free running mode
  // ADMUX = 0x40;   // use adc0
  // DIDR0 = 0x01;   // turn off the digital input for adc0
  //   //   // // sampling rate is [ADC clock] / [prescaler] / [conversion clock cycles]
  // //   // // for Arduino Uno ADC clock is 16 MHz and a conversion takes 13 clock cycles
  // // ADCSRA |= (1 << ADPS2) | (1 << ADPS0);  // 32 prescaler for 38.5 KHz
  // //   // ADCSRA |= (1 << ADPS2);  // 16 prescaler for 76.9 KHz
  // ADCSRA |= (1 << ADPS1) | (1 << ADPS0);  // 8 prescaler for 153.8 KHz
  //                                         // ADCSRA |= (1 << ADPS1); // Set prescaler ADC ke 2

  // ADCSRA |= (1 << ADATE);  // enable auto trigger
  // ADCSRA |= (1 << ADIE);   // enable interrupts when measurement complete
  // ADCSRA |= (1 << ADEN);   // enable ADC
  // ADCSRA |= (1 << ADSC);   // enable ADC measurement
  getData(CHANNEL, RAW_SAMPLE);
    Serial.println("\n");
    for (int i = 0; i < 128; i++) {
    Serial.print(vReal[i]);
    Serial.print(",");
  }

  while (1) {
    getData(CHANNEL, RAW_SAMPLE);
    peakFreq = getFFT(vReal, vImag, SAMPLE, F_SAMPLING);

    Serial.print("F :\t");
    Serial.print(peakFreq);  //Print out what frequency is the most dominant.
    Serial.print("\tDiff :\t");
    Serial.println(TONE_TARGET - peakFreq);  //Print out what frequency is the most dominant.
    // while(1); /* Run Once */
    // delay(200); /* Repeat after delay */
  }
}

void getData(char pin, int rawSample) {
  /*SAMPLING*/
  char rawInput[RAW_SAMPLE];
  // double vReal[s];
  // double vImag[s];
  /*f merupakan factor downscaling 
  normalnya 2 4 8
  gunakan 4 bila sample 512 
  gunakan 2 bila sample 256
  */
  for (int i = 0; i < rawSample; i++) {
    rawInput[i] = analogRead(pin);
  }

  // for (int i = 0; i < 512; i++) {
  //   Serial.print(rawInput[i]);
  //   Serial.print(",");
  // }

  for (int i = 0, j = 0; i < rawSample; i += FACTOR, j++) {
    vReal[j] = rawInput[i];
    vImag[j] = 0;
  }

  // Serial.println("get data");
}

double getFFT(double vReal[], double vImag[], int s, int fs) {
  FFT = arduinoFFT(vReal, vImag, s, fs);           /* Create FFT object */
  FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD); /* Weigh data */
  FFT.Compute(FFT_FORWARD);                        /* Compute FFT */
  FFT.ComplexToMagnitude();                        /* Compute magnitudes */
  // double fhz = FFT.MajorPeak() * (fs / s);
  // Serial.println("getfft");
  // return fhz;
  return FFT.MajorPeak();
}


void loop() {
  // FFT = arduinoFFT(vReal, vImag, samples, samplingFrequency); /* Create FFT object */
  // // FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD); /* Weigh data */
  // FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD); /* Weigh data */
  // FFT.Compute(FFT_FORWARD); /* Compute FFT */
  // FFT.ComplexToMagnitude(); /* Compute magnitudes */
  // float x = FFT.MajorPeak();

  // getData(CHANNEL, RAW_SAMPLE, SAMPLE, FACTOR);
  // peakFreq = getFFT(vReal, vImag, SAMPLE, F_SAMPLING);

  // Serial.print("Frequncy :\t");
  // Serial.print(peakFreq);  //Print out what frequency is the most dominant.
  // Serial.print("\tDiff :\t");
  // Serial.println(TONE_TARGET - peakFreq);  //Print out what frequency is the most dominant.
  // // while(1); /* Run Once */
  // delay(200); /* Repeat after delay */
}
