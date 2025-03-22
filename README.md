# Ultrasonic Distance Meter with LCD & Buzzer 🚀

## 📌 Overview
This project is an **Ultrasonic Distance Meter** that displays distance readings on an LCD screen and triggers a buzzer when an object comes too close. It uses an **HC-SR04 ultrasonic sensor**, a **16x2 LCD with I2C**, and a **passive buzzer** for alerts.

![Project Image](WhatsApp%20Image%202025-03-21%20at%2020.06.47_77750526.jpg)

## 🛠️ Components Used
- **Arduino Board**
- **HC-SR04 Ultrasonic Sensor**
- **16x2 LCD with I2C Module**
- **Passive Buzzer**
- **Push Button**
- **Jumper Wires**
- **Breadboard**

## 📜 Code
```cpp
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
    lcd.print("\xFF");
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
```

## 🔍 How It Works
1. The **ultrasonic sensor** measures distance by sending a pulse and waiting for its echo.
2. The **LCD** displays the measured distance.
3. A **bar graph** is drawn on the LCD to visualize proximity.
4. If the distance is **15 cm or less**, the **buzzer sounds an alert**.
5. The **push button** stops the buzzer when pressed.

## 🎯 Applications
- **Obstacle detection** 🚧
- **Parking assistance systems** 🚗
- **Security distance monitoring** 🛡️

## 📌 Future Improvements
- Add a **relay module** to control external devices.
- Implement **adjustable threshold values** via a potentiometer.
- Display **custom warning messages** on the LCD.

📢 Feel free to **contribute** or **modify** the project! 🛠️✨

