#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define BUZZER_PIN 3
#define BUTTON_PIN 11
#define TRIG_PIN 9
#define ECHO_PIN 10

long T = 0;
float S = 0;

void buzzer_off() {
  noTone(BUZZER_PIN);
  delay(500);
}

void buzzer_on() {
  tone(BUZZER_PIN, 1000);  
  delay(500);        
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  T = pulseIn(ECHO_PIN, HIGH);
  S = (T * 0.0343) / 2;

  if (S > 400 || S <= 0) {
    S = 400;
  }

  int columnsToFill = map(S, 20, 400, 16, 0);
  if (columnsToFill > 16) columnsToFill = 16;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(S);
  lcd.print("cm");

  lcd.setCursor(0, 1);
  for (int i = 0; i < columnsToFill; i++) {
    lcd.print("\xFF");  // \xFF aris blokis gamosatanad mocemuli kodi
  }

  if (S <= 15) {
    buzzer_on();             
  } 
  else if (S >= 15){
    buzzer_off();
  }
  while (digitalRead(11) == LOW){
    buzzer_off();
  }

  Serial.print("Distance: ");
  Serial.print(S);
  Serial.println(" cm");

  delay(1000);
}
