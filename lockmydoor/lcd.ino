//#include <Wire.h> 
//#include <LiquidCrystal_I2C.h>
//
//char wordtodisplay[]="GERCEP LOCK MY DOOR             ";
//LiquidCrystal_I2C lcd(0x3F,16,2);
//
//void setup() {
//  Serial.begin(9600);
//  lcd.init();
//  lcd.backlight();
//}
//
//void loop() {
//  lcd.setCursor(15,0);
//  for (int pos = 0; pos < 32; pos++) {
//    lcd.scrollDisplayLeft();
//    lcd.print(wordtodisplay[pos]);
//    delay(400);
//  }
//  lcd.setCursor(15,1);
//  for (int pos = 0; pos < 32; pos++) {
//    lcd.scrollDisplayLeft();
//    lcd.print(wordtodisplay[pos]);
//    delay(400);
//  }
//  lcd.clear();
// }
