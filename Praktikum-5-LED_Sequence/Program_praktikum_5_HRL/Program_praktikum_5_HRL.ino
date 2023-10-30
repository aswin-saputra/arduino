
/*
 * Praktikum 5
 * Aswin Saputra
 * 31 1221 000 6
 * LED SEquence dari Kanan --> kiri
 * LED menyala Berurutan
 * LED_4    LED_3   LED_2   LED_1
 * on       off     off     off
 * on       on      off     off
 * on       on      on      off
 * on       on      on      on
 * dan berulang
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
    // * Pin 2 -- 5 kanan --> kiri
    for (ledPin = firstPin; ledPin <= lastPin; ledPin++)
    {
        pinMode(ledPin, OUTPUT);
        digitalWrite(ledPin, LOW);
    }
}

void loop()
{
    Serial.println("Memulai Sequence");
    for (ledPin = lastPin; ledPin >= firstPin; ledPin--)
    {
        digitalWrite(ledPin, HIGH);
        Serial.print("LED\t");
        Serial.print(ledPin - 1);
        Serial.println("\tON");
        delay(myDelay);
        if (ledPin == firstPin)
        {
            // delay(myDelay);
            // digitalWrite(ledPin, LOW);
            ledOFF();
        }
    }
    delay(myDelay * 2);
}
void ledOFF()
{
    for (ledPin = lastPin; ledPin >= firstPin; ledPin--)
    {
        delay(1);
        Serial.print("LED Shutdown\t");
        Serial.print(ledPin);
        Serial.println("\tOFF");
        digitalWrite(ledPin, LOW);
    }
}
