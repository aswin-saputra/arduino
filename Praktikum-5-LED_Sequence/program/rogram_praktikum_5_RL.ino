
/*
 * Praktikum 5
 * Aswin Saputra
 * 31 1221 000 6
 * LED SEquence dari Kanan --> Kiri
 * LED menyala Bergantian
 */

int myDelay = 200;
int firstPin = 2;
int lastPin = 5;
int ledPin;

void setup()

{
    Serial.begin(9600);
    // * Menginisiasi Pin LED dengan mengunakan for loop
    // * Inisiasi dimulai dari pin 2 sampai 5
    // * Pin 2 -- 5 kiri --> kanan
    for (ledPin = firstPin; ledPin <= lastPin; ledPin++)
    {
        pinMode(ledPin, OUTPUT);
        digitalWrite(ledPin, LOW);
    }
}
void loop()
{
    Serial.println("Memulai Sequence Menyala Dari Kiri -->> kanan secara bergantian");
    for (ledPin = lastPin; ledPin >= firstPin; ledPin--)
    {
        digitalWrite(ledPin, HIGH);
        Serial.print("LED\t");
        Serial.print(ledPin - 1);
        Serial.println("\tON");
        delay(myDelay);
        Serial.print("LED\t");
        Serial.print(ledPin - 1);
        Serial.println("\tOFF");
        digitalWrite(ledPin, LOW);
    }
    delay(myDelay * 2);
}