// Para mahasiswa yang berbahagia buatlah rangkaian hanya berupa arduino saja. Kemudian buatlah program arduino untuk:

// 1. Membangkitkan bilangan acak dari 0 sampai 1000 menggunakan fungsi random dan mengirimkannya ke serial monitor. Nilai bilangan acak tersebut juga digunakan untuk mengatur nyala LED_BUILTIN. Jika nilai bilangan acak lebih dari 500 LED menyala.

// 2. Modifikasi program no 1, dengan mengansumsikan nilai bilangan acak tersebut sebagai nilai cacahan pada suatu timer dengan frekuensi clock inputnya 10 KHz, kemudian menghitung durasi waktu yang ditempuh timer tersebut dan mengirimkannya ke serial monitor.

// 3. Modifikasi program no 1, dengan mengansumsikan nilai bilangan acak tersebut sebagai nilai cacahan pada suatu counter dengan input dari sensor kecepatan putar (piringan berlubang dan optocoupler), kemudian menghitung kecepatan putar jika banyak lubang pada piringan 10 lubang dan periode pengukuran setiap 500 ms, serta mengirimkannya ke serial monitor.

// Tugas dikerjakan dengan tinkercad dengan akun anda masing2 untuk mensimulasikannya. Setelah hasil sesuai dengan yang diharapkan lakukan praktik pada board arduino yang sesungguhnya di lab.

// Listing program diunggah di elinas paling lambat hari ini 21 Oktober 2023 jam 23.55 WIB

/*
Tugas Praktikum 3
Sistem Mikroprosesor dan Mikrokomtroler
Program LED sederhana
dengan aturan :
angka ganjil LED OFF dan sebaliknya
dengan rentang 1-20
13 oct 23
*/

int freq = 10000;
float period;
float RPM;
int time;
int randVal;
void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    period = 1 / freq;
}

void loop()
{
    randVal = random(0, 1000);
    if (randVal >= 500)
    {
        ledAct();
    };
    calcTimer();
    calcRPM();
}
void ledAct()
{
    Serial.print("Nilai ");
    Serial.print("\t");
    Serial.print(":");
    Serial.print("\t");
    Serial.print(randVal);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
}
void calcTimer()
{
    // jika nilai rnadom yang dihasilkan adalah timer maka waktu yang dibutuhkan untuk nilai ditampilkan pada serial monitor adalh nilai random / periode clock, atau randomvalue /1/T

    Serial.println("Memulai kalkulasi waktu timer");
    Serial.println("-----------------------------");
    time = randVal / period;
    Serial.println(period);
    Serial.println(randVal);
    Serial.println(time);
    Serial.println("-----------------------------");
    // Serial.print("\t");
}
void calcRPM()
{
    Serial.println("Memulai menghitung RPM");
    Serial.println("----------------------");
    RPM = randVal * 12;
    Serial.print("Revolution per Minute (RPM :)");
    Serial.print("\t");
    Serial.print(RPM);
    Serial.println("----------------------");
}