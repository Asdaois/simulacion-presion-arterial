const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

const int col1 = 10, col2 = 11, col3 = 12, col4 = 13;
const int row1 = A0, row2 = A1, row3 = 8, row4 =  9;

#include <LiquidCrystal.h>
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include <Keypad.h>
#define ROWS 4 //four rows
#define COLS 4 //three columns

char keys[ROWS][COLS] = {
  {'1','2','3','4'},
  {'5','6','7','8'},
  {'9','T','J','Q'},
  {'*','0','#','K'}
};
byte rowPins[ROWS] = {6,7,8,9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A2,A3,A4,A5}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  lcd.begin(16, 4);
  lcd.print("Funcionando!");
}

void loop() {
  char key = keypad.getKey();
  
  if (key){
    lcd.setCursor(0, 0);
    lcd.print(key);
  }
}