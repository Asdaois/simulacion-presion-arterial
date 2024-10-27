const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

#include <LiquidCrystal.h>
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
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
  lcd.println("Hello World!");
}

void loop() {
  char key = keypad.getKey();
  
  if (key){
    lcd.setCursor(0, 0);
    lcd.print(key);
  }
}