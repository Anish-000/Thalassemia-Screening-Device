//#include <Keypad.h>
//#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h> //Header file for LCD from https://www.arduino.cc/en/Reference/LiquidCrystal
#include <Keypad.h> 

const int ROW_NUM    = 4; // four rows
const int COLUMN_NUM = 4; // four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pin_rows[ROW_NUM] = {0,1,2,3}; // connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {4,5,6,7}; // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);
//LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13; //Pins to which LCD is connected
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16,2);
  lcd.setCursor(0, 0);
  lcd.print("WELCOME");
  lcd.setCursor(0, 1);
  lcd.print("Please Wait");
  delay(2000);

  lcd.setCursor(0, 0);
  lcd.print("Loading...");
  delay(2000);
  lcd.clear();
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Enter MCV:");
  float MCV = getKeypadInput();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter MCH:");
  float MCH = getKeypadInput();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter RBC:");
  float RBC = getKeypadInput();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter RDW:");
  float RDW = getKeypadInput();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Hb:");
  float Hb = getKeypadInput();
  
  lcd.clear();
  lcd.setCursor(0, 0);
  
  float result = (0.2815 * MCV) + (0.2015 * MCH) - (0.2641 * RBC) - (0.1693 * RDW) + (0.0835 * Hb);
  
  lcd.print("SCS_BIT:");
  lcd.setCursor(0, 1);
  lcd.print(result);
  if(result > 24.993)
  {
    lcd.print("suspected");
  }
  else{
    lcd.print("not suspected");
  }
  delay(7000); // Display result for 5 seconds
  lcd.clear();
}

float getKeypadInput() {
  char key = keypad.getKey();
  String input = "";
  
  while (key != '#') {
    if (key) {
      input += key;
      lcd.print(key);
    }
    key = keypad.getKey();
  }
  
  return input.toFloat();
}