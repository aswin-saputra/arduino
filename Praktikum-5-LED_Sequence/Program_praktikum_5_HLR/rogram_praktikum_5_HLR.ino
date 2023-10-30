
/*
 * Praktikum 5
 * Aswin Saputra
 * 31 1221 000 6
 * LED SEquence dari KIRI --> kanan
 * LED menyala Berurutan
 * LED_1    LED_2   LED_3   LED_4
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
    // * Pin 2 -- 5 kiri --> kanan
    for (ledPin = firstPin; ledPin <= lastPin; ledPin++)
    {
        pinMode(ledPin, OUTPUT);
        digitalWrite(ledPin, LOW);
    }
}

void loop()
{
    Serial.println("Memulai Sequence");
    for (ledPin = firstPin; ledPin <= lastPin; ledPin++)
    {
        digitalWrite(ledPin, HIGH);
        Serial.print("LED\t");
        Serial.print(ledPin - 1);
        Serial.println("\tON");
        delay(myDelay);
        if (ledPin == lastPin)
        {
            ledOFF();
        }
    }
    delay(myDelay * 2);
}
void ledOFF()
{
    for (ledPin = firstPin; ledPin <= lastPin; ledPin++)
    {
        Serial.print("LED Shutdown\t");
        Serial.print(ledPin);
        Serial.println("\tOFF");
        digitalWrite(ledPin, LOW);
    }
}
