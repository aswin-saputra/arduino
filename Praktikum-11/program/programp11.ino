
#include <Keypad.h>
#include <LiquidCrystal.h>

#define LCD_RS 7
#define LCD_EN 6
#define LCD0_D4 5
#define LCD0_D5 4
#define LCD0_D6 3
#define LCD0_D7 2

LiquidCrystal LCD0(
    LCD_RS,
    LCD_EN,
    LCD0_D4,
    LCD0_D5,
    LCD0_D6,
    LCD0_D7);

#define COL 4
#define ROW 4

unsigned char keymap[ROW][ROW] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};
byte rowPins[ROW] = {8, 9, 10, 11};
byte colPins[COL] = {A5, A4, A3, A2};
Keypad customKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, ROW, COL);
int pos = 0;
void setup()
{
    Serial.begin(115200);
    Serial.println("Ready to Read key");
}
void loop()
{
    char customKey = customKeypad.getKey();
    // int pos=0;
    if (customKey)
    {
        Serial.println(customKey);
        LCD0.setCursor(pos, 0);
        LCD0.print(customKey);
        if (pos == 16)
        {
            pos = 0;
            LCD0.clear();
        }
        else
        {
            pos++;
        }
    }
}