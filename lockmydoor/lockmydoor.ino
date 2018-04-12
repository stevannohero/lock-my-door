
#include <Servo.h> 
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

//PIN DECLARATION
byte rowPins[ROWS] = {4, 5, 6, 7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 9, 10}; //connect to the column pinouts of the keypad
int buttonPin = 3;
int servoPin = 2;
const int trigPin = A1;
const int echoPin = A2;
int LEDPin = 11;

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
Servo myservo;
LiquidCrystal_I2C lcd(0x3F,16,2);

// Initialize LCD pins
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int hasilSensorLDR; // Variable untuk sensor LDR
long duration, distance;

int pos = 0;
int state;
int stateMainMenu = 0;
int stateIsiPassword = 1;
int statePasswordBenar = 2;
int statePasswordSalah = 3;
int stateGembokTerbuka = 4;
int stateGantiPassword = 5;
int stateMengunciKembali = 6;

char password[4] = {'1','2','3','4'};
int fade = 0;
int deltaf = 1;
//state 0 adalah main menu
//state 1 adalah input password
//state 2 adalah password benar
//state 3 adalah password salah
//state 4 adalah gembok terbuka
//state 5 adalah edit password
//state 6 adalah mengunci kembali

void buka_servo() {
  for(pos = 0; pos < 90; pos += 1) {
    // pada posisi 1 derajat
    // memberitahu servo untuk pergi ke posisi  'pos'
    myservo.write(pos);
    // tunggu 15ms untuk pencapaian  posisi servo    
    delay(15);                  
 } 
}

void nyalainLampuKloGelap() {
  hasilSensorLDR=analogRead(0); // Hasil LDR = Hasil input pada pin A0
  if (hasilSensorLDR < 100) {
    fade += deltaf;
    if (fade >= 255) {
      fade = 255;
      deltaf *= -1;
    }
  
    if (fade <= 0) {
      fade = 0;
      deltaf *= -1;
    }
    analogWrite(LEDPin, fade);
  } else {
    analogWrite(LEDPin, LOW);
  }
}

void waitingForPerson() {
  int ada_orang = 0;
  while (ada_orang == 0) {
    nyalainLampuKloGelap();
    //kalau jarak kurang dari yg diinginkan, barub rubah jadi true
    //agar bisa melewati fungsi ini
    digitalWrite(trigPin, LOW); delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH); delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration*0.034/2;
    ada_orang = distance < 50;
//    Serial.print("distance : ");
//    Serial.println(distance);
    delay(100);
  }
}

void kunci_servo() {
  for(pos = 90; pos>=1; pos-=1) {
    // memberitahu servo untuk pergi ke posisi  'pos'                                
    myservo.write(pos);                 
    // tunggu 15ms untuk pencapaian  posisi servo    
    delay(15);
  }
}



char getInput() {
  char result = 'x';
  while (result == 'x') {
    nyalainLampuKloGelap();
    if (state == 4 || state == 0) {
      int buttonState = 0;
      buttonState = digitalRead(buttonPin);

//      Serial.println(buttonState);
  
      if (buttonState == 1){
          result = '*'; 
          delay(200);
      }
    }
    if (result == 'x') {
      char key = keypad.getKey();
      if (key != NO_KEY) {
        result = key;
      }
    }
  }
//  Serial.print("key : ");
//  Serial.println(result);
  return result;
}

void main_menu() {
//  Serial.println("main menu");
  lcd.clear();
  lcd.print("     LOCKED     ");
  lcd.setCursor(0,1);
  lcd.print("Press * to login");
 
  waitingForPerson();
  char fromKeypad = getInput();

  //transfer state jika input bintang
  if (fromKeypad == '*') {
    state = stateIsiPassword;
  }
}

void isi_password() {
//  Serial.println("isi password");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Input password ");
  lcd.setCursor(6,1);
  
  char fromKeypad;
  int length_correct;

  //cek kebenaran password
  for (int i = 0; i < 4; i++) {
    fromKeypad = getInput();
    if (fromKeypad == password[i]){
      length_correct += 1;
    }
    lcd.print("*");
  }

  //transfer state
  //kalau keempat password benar pindah state ke password benar
  if (length_correct == 4) {
    state = statePasswordBenar;
  } else {
    state = statePasswordSalah;
  }
}

void password_benar() {
//  Serial.println("password benar");

  lcd.clear();
  lcd.print("    WELCOME!    ");
  lcd.setCursor(0,1);
  lcd.print("HAVE A NICE DAY!");
  
  //GESER SERVO DISINI
  buka_servo();
  delay(1000);

  state = stateGembokTerbuka;
}

void gembok_terbuka() {
//  Serial.println("gembok sedang terbuka");
  Serial.println("LOG : Sistem dibuka");
  lcd.clear();
  lcd.print("      OPEN      ");
  lcd.setCursor(0,1);
  lcd.print("*: lock, #: edit");

  char fromKeypad = getInput();

  //terdapat dua opsi yaitu mengunci kembali, atau mengganti password
  if (fromKeypad == '*') {
    state = stateMengunciKembali;
  } else if (fromKeypad == '#') {
    state = stateGantiPassword;
  } 
}

void password_salah() {
//  Serial.println("password_salah");
  lcd.clear();
  lcd.print(" WRONG PASSWORD ");
  delay(2000);

  //jika password salah maka akan langsung ke main_menu
  state = stateMainMenu;
}

void ganti_password() {
  Serial.println("LOG : Password diganti");
  lcd.clear();
  lcd.print("  NEW PASSWORD  ");
  lcd.setCursor(6,1);
  
  //input empat buah karakter untuk menjadi password baru
  for(int i = 0; i < 4; i++) {
    char fromKeypad = getInput();
    password[i] = fromKeypad;
    lcd.print("*");
  }

  //pindah ke main menu setelah merubah password
  state = stateMengunciKembali;
}


void mengunci_kembali() {
//  Serial.println("mengunci kembali");
  Serial.println("LOG : Sistem dikunci");

  //GESER SERVO DISINI
  kunci_servo();

  state = stateMainMenu;
}

void setup() {
  state = stateMainMenu;
  Serial.begin(9600);
  myservo.attach(2);
  buka_servo();
  kunci_servo();
  lcd.init();
  lcd.backlight();
  lcd.begin(16,2); // set up the LCD's number of columns and rows
  lcd.print("STARTING...");
  delay(1000);
  lcd.clear();
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, OUTPUT);
  delay(1000);
}

void loop() {
//  Serial.print("state : ");
//  Serial.println(state);

  nyalainLampuKloGelap();

  if (state == stateMainMenu) {
    main_menu();
  } else if (state == stateIsiPassword) {
    isi_password();
  } else if (state == statePasswordBenar) {
    password_benar();
  } else if (state == statePasswordSalah) {
    password_salah();
  } else if (state == stateGembokTerbuka) {
    gembok_terbuka();
  } else if (state == stateGantiPassword) {
    ganti_password();
  } else if (state == stateMengunciKembali) {
    mengunci_kembali();
  }
}
