int pin1 = 2;
int pin2 = 3;
int pin3 = 4;
int pin4 = 13;
int pin5 = 12;
int pin6 = 11;
int pin7 = 10;

void turn_on() {
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, HIGH);
  digitalWrite(pin5, HIGH);
  digitalWrite(pin6, HIGH);
  digitalWrite(pin7, HIGH);
}

void turn_off() {
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
  digitalWrite(pin5, LOW);
  digitalWrite(pin6, LOW);
  digitalWrite(pin7, LOW);
}

void display_digit(int digit) {
  turn_on();
  
  if(digit == 0) {
    digitalWrite(pin7, LOW);  
  }
  
  if(digit == 1) {
    digitalWrite(pin2, LOW);
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
    digitalWrite(pin5, LOW);
    digitalWrite(pin7, LOW);
  }
  
  if(digit == 2) {
    digitalWrite(pin3, LOW);
    digitalWrite(pin6, LOW);
  }
  
  if(digit == 3) {
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
  }
  
  if(digit == 4) {
    digitalWrite(pin2, LOW);
    digitalWrite(pin4, LOW);
    digitalWrite(pin5, LOW);
  }
  
  if(digit == 5) {
    digitalWrite(pin1, LOW);
    digitalWrite(pin4, LOW);
  }
  
  if(digit == 6) {
    digitalWrite(pin1, LOW);
  }
  
  if(digit == 7) {
    digitalWrite(pin3, LOW);
    digitalWrite(pin4, LOW);
    digitalWrite(pin5, LOW);
    digitalWrite(pin7, LOW);
  }
  
  if(digit == 8) {
      
  }
  
  if(digit == 9) {
    digitalWrite(pin4, LOW);
  }
}

//void setup() {
//  // put your setup code here, to run once:
//  pinMode(pin1, OUTPUT);
//  pinMode(pin2, OUTPUT);
//  pinMode(pin3, OUTPUT);
//  pinMode(pin4, OUTPUT);
//  pinMode(pin5, OUTPUT);
//  pinMode(pin6, OUTPUT);
//  pinMode(pin7, OUTPUT);
//}

//void loop() {
//  // put your main code here, to run repeatedly:
//  for(int i = 0; i <= 9; i++) {
//    display_digit(i);
//    delay(500);
//    turn_off();
//  }
//}


