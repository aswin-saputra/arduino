/*
Tugas Praktikum 3 
Sistem Mikroprosesor dan Mikrokomtroler
Program LED sederhana 
dengan aturan : 
angka ganjil LED OFF dan sebaliknya
dengan rentang 1-20
13 oct 23
*/

int startValue = 1;
int endValue = 20;
int timeDelay = 250;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  for (int i = startValue; i <= endValue; i++) {

    Serial.print("Angka :");
    Serial.print("\t");
    Serial.print(i);
    Serial.print("\t");
    if !(i % 2 == 0 ) {
      // Number is Even
      Serial.print("Adalah Genap");
      Serial.print("\t");
      Serial.println("LED ON");
      digitalWrite(LED_BUILTIN, HIGH);
      delay(timeDelay);
    } else {
      // Number is Odd
      Serial.print("Adalah Ganjil");
      Serial.print("\t");
      Serial.println("LED OFF");
      digitalWrite(LED_BUILTIN, LOW);
      delay(timeDelay);
    }
  }
  Serial.println();
  delay(timeDelay * 2);
}
