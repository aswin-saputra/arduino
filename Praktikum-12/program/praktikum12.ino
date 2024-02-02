#include <LiquidCrystal.h>

#define LCD_RS 7
#define LCD_EN 6
#define LCD0_D4 5
#define LCD0_D5 4
#define LCD0_D6 3
#define LCD0_D7 2

LiquidCrystal lcd(
    LCD_RS,
    LCD_EN,
    LCD0_D4,
    LCD0_D5,
    LCD0_D6,
    LCD0_D7);

String pass = "";
int i = 0;
int pjam, sjam, pmenit, smenit, pdetik, sdetik;

char jam = 0, menit = 0, detik = 0, tanggal = 1, kursor = 7;
char temp1[16];
unsigned long sekarang, lalu = 0;
bool jalan = true;

void setup()
{
    Serial.begin(9600);
    Serial.println("Coba Keypad");
    Serial.println("by Arif Basuki");
    // lcd.init();
    lcd.clear();
    // lcd.backlight();
    lcd.print("  Jam Digital");
    delay(2000);
    // lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Waktu: ");
    lcd.setCursor(7, 1);
    sprintf(temp1, "%02d%c%02d%c%02d%c", jam, ':', menit, ':', detik, ' ');
    lcd.print(temp1);
    delay(100);
}

void loop()
{
    pjam = jam / 10;
    sjam = jam % 10;
    pmenit = menit / 10;
    smenit = menit % 10;
    pdetik = detik / 10;
    sdetik = detik % 10;
    int tombol = deteksi_tombol();
    if (tombol == 4)
    {
        if (jalan == true)
        {
            jalan = false;
            setting();
        }
    }
    if (jalan)
    {
        // lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  Jam Digital ");
        lcd.setCursor(0, 1);
        lcd.print("Waktu: ");
        lcd.setCursor(7, 1);
        updatewaktu();
        sprintf(temp1, "%02d%c%02d%c%02d%c", jam, ':', menit, ':', detik, ' ');
        lcd.print(temp1);
        delay(100);
    }
}

void updatewaktu()
{
    sekarang = millis();
    if (sekarang - lalu >= 1000)
    {
        detik++;
        if (detik == 60)
        {
            menit++;
            detik = 0;
        }
        if (menit == 60)
        {
            jam++;
            menit = 0;
        }
        if (jam == 24)
        {
            tanggal++;
            jam = 0;
        }
    }
    // lalu=sekarang;
}

int deteksi_tombol()
{
    int n = -1;
    int data = analogRead(A0);
    if (data >= 50 && data < 250)
        n = 0;
    if (data >= 250 && data < 450)
        n = 1;
    if (data >= 450 && data < 650)
        n = 2;
    if (data >= 650 && data < 850)
        n = 3;
    if (data >= 850 && data <= 1023)
        n = 4;
    Serial.println(data);
    return n;
}

void setting()
{
    /* pjam=jam/10;
     sjam=jam%10;
     pmenit=menit/10;
     smenit=menit%10;
     pdetik=detik/10;
     sdetik=detik%10;*/
    //
    kursor = 7;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" Setting Waktu");

    while (jalan == false)
    {
        lcd.setCursor(kursor, 1);
        lcd.cursor();
        delay(200);
        lcd.noCursor();
        delay(200);
        int tombol = deteksi_tombol();
        if (tombol == 4)
        {
            jam = 10 * pjam + sjam;
            menit = 10 * pmenit + smenit;
            detik = 10 * pdetik + sdetik;
            jalan = true;
        }
        if (tombol == 0)
            naik();
        if (tombol == 1)
            kanan();
        if (tombol == 2)
            kiri();
        if (tombol == 3)
            turun();
        sprintf(temp1, "%d%d%c%d%d%c%d%d%c", pjam, sjam, ':', pmenit, smenit, ':', pdetik, sdetik, ' ');
        lcd.setCursor(7, 1);
        lcd.print(temp1);
        delay(100);
    }
}

void naik()
{
    if (kursor == 7)
    {
        pjam++;
        if (pjam > 2)
            pjam = 0;
    }
    if (kursor == 8)
    {
        sjam++;
        if (sjam > 9)
            sjam = 0;
    }
    if (kursor == 10)
    {
        pmenit++;
        if (pmenit > 6)
            pmenit = 0;
    }
    if (kursor == 11)
    {
        smenit++;
        if (smenit > 9)
            smenit = 0;
    }
    if (kursor == 13)
    {
        pdetik++;
        if (pdetik > 6)
            pdetik = 0;
    }
    if (kursor == 14)
    {
        sdetik++;
        if (sdetik > 9)
            sdetik = 0;
    }
}

void turun()
{
    if (kursor == 7)
    {
        pjam--;
        if (pjam < 0)
            pjam = 2;
    }
    if (kursor == 8)
    {
        sjam--;
        if (sjam < 0)
            sjam = 9;
    }
    if (kursor == 10)
    {
        pmenit--;
        if (pmenit < 0)
            pmenit = 6;
    }
    if (kursor == 11)
    {
        smenit--;
        if (smenit < 0)
            smenit = 9;
    }
    if (kursor == 13)
    {
        pdetik--;
        if (pdetik < 0)
            pdetik = 6;
    }
    if (kursor == 14)
    {
        sdetik--;
        if (sdetik < 0)
            sdetik = 9;
    }
}
void kanan()
{
    kursor++;
    if (kursor > 14)
        kursor = 7;
}

void kiri()
{
    kursor--;
    if (kursor < 7)
        kursor = 14;
}