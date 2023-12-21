
// Sketch uses 2076 bytes (6%) of program storage space. Maximum is 30720 bytes.
// Global variables use 101 bytes (4%) 

#include <LiquidCrystal.h>
#define LCD_RS 7
#define LCD_EN 6
#define LCD0_D4 5
#define LCD0_D5 4
#define LCD0_D6 3
#define LCD0_D7 2
#define MYNAME "Aswin Saputra"
#define MYID "3112210006"
#define TEXT "Saya akan selalu rajin belajar"

LiquidCrystal LCD0(
  LCD_RS,
  LCD_EN,
  LCD0_D4,
  LCD0_D5,
  LCD0_D6,
  LCD0_D7);

void setup() {
  LCD0.begin(16, 2);
}

void loop() {
  
    LCD0.setCursor(0, 0);
    LCD0.print(MYNAME);
    LCD0.setCursor(0, 1);
    LCD0.print(MYID);
    delay(500); /*display text 500 ms*/
    LCD0.clear();
    delay(500); /*Blank 500 ms*/

/* Display another text*/

    LCD0.setCursor(0, 0);
    LCD0.print(TEXT);
  delay(500);
    for(int ii = 0 ; ii <= (strlen(TEXT)-16) ; ++ii){
    LCD0.scrollDisplayLeft();
    delay(200); 
    }
    LCD0.clear();
    delay(10); 

}