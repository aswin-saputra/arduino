/*
 * Tugas Praktikum 4
 * 19 oct 23
 */

/*
1. 	Membangkitkan bilangan acak dari 0 sampai 1000
    menggunakan fungsi random dan mengirimkannya ke serial monitor.
    Nilai bilangan acak tersebut juga digunakan untuk mengatur nyala LED_BUILTIN.
    Jika nilai bilangan acak lebih dari 500 LED menyala.

2. 	Modifikasi program no 1, dengan mengansumsikan nilai bilangan acak tersebut
    sebagai nilai cacahan pada suatu timer dengan frekuensi clock inputnya 10 KHz,
    kemudian menghitung durasi waktu yang ditempuh timer tersebut dan mengirimkannya ke serial monitor.

3. 	Modifikasi program no 1, dengan mengansumsikan nilai bilangan acak tersebut sebagai nilai cacahan
    pada suatu counter dengan input dari sensor kecepatan putar (piringan berlubang dan optocoupler),
    kemudian menghitung kecepatan putar jika banyak lubang pada piringan 10 lubang
    dan periode pengukuran setiap 500 ms, serta mengirimkannya ke serial monitor.

*/

unsigned long randomNumber;
const int freqClock = 10000;
float durasi;
float RPs;
float RPM;

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    // Membuat psudo random Generator
    randomSeed(analogRead(0));
}

// Membuat Scope Untuk memisahkan tiap fungsi
void numGen()
{
    randomNumber = random(1000);
    Serial.print("** Angka acak\t\t: ");
    Serial.println(randomNumber);
}

void ledAction()
{
    // Bagian LED

    Serial.print("LED Status\t\t: ");
    if (randomNumber > 500)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("LED ON");
    }
    else
    {
        digitalWrite(LED_BUILTIN, LOW);
        Serial.println("LED OFF");
    }
}

void timerCalculation()
{
    // Bagian 2 (Timer)
    durasi = (float)randomNumber / freqClock;
    Serial.println("** Durasi Timer ke Serial Monitor");
    Serial.print("Durasi TImer (s)\t: ");
    Serial.print(durasi, 5);
    Serial.print(" ");
    Serial.println("s");
    // Durasi Timer dalam milli detik
    Serial.print("Durasi Timer (ms)\t: ");
    Serial.print(durasi * 1000);
    Serial.print(" ");
    Serial.println("ms");
}

void rpmCalculation()
{
    /* Bagian 3
   Menghitung RPM BIla Bilangan Acak adalah Counter dari sensor misal
   Optocoupler sensor
   ***
   RPM = (((float)n/ holes)/samplingPeriode) *60;
   RPM = banyaknya putran/detik * 60
   ***
   1 putaran / detik --> bila nilai counter membaca adalah 5 dalam periode 500ms,
   artinya bila counter bernilai 10 kecepatan adalah 2 putaran per detik
   reduksi model matematisnya menjadi
       (n/holes)/1/2
       (n/5) --> putaran / detik
       (n/5)  * 60  --> putaran / menit
   reduksi menjadi
       12 * n
   dimana ::
       n = randomNumber;
       holes = 10
       samplingPeriode 500 ms
 */

    // RPM = (((float)n/ holes)/samplingPeriode) *60;

    RPs = (float)randomNumber / 5;
    RPM = 12 * randomNumber;

    Serial.println("** Menghitung Putaran");
    Serial.print("Jummlah Putaran (rad/s)\t: ");
    Serial.print(RPs);
    Serial.println(" Revolution / second");
    // Putaran per menit
    Serial.print("Jumlah Putaran (RPM)\t: ");
    Serial.print(RPM);
    Serial.println(" RPM");
}

void loop()
{
    Serial.println("------------------\\o0o/\\^c^/\\o0o/------------------");

    numGen();
    delay(10);
    ledAction();
    delay(10);
    timerCalculation();
    delay(10);
    rpmCalculation();
    Serial.println("-------------------------*0*--------------------------");
    Serial.println("\n\n");
    delay(1000);
}
