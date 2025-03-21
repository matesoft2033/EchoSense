# EchoSense: Ultrasonic Distance Meter with LCD Display 🚀

![Project Preview](WhatsApp%20Image%202025-03-21%20at%2020.06.47_77750526.jpg)

## 📌 Project Overview
EchoSense is an **ultrasonic distance measurement system** that uses an **HC-SR04 sensor** to detect distances and displays the result on a **16x2 LCD screen**. Additionally, a **passive buzzer** provides feedback based on the measured distance.

## 🔧 Features
- 📏 **Accurate Distance Measurement** (30 cm - 400 cm)
- 📟 **Real-time LCD Display**
- 🔊 **Buzzer Alerts for Close Objects**
- 🎛️ **User-friendly Interface**
- ⚡ **Compact and Efficient Design**

## 🛠️ Components Used
- **Arduino Board** 🖥️
- **HC-SR04 Ultrasonic Sensor** 📡
- **16x2 I2C LCD Display** 🖥️
- **Passive Buzzer** 🔊
- **Push Button** 🔘
- **Jumper Wires** 🔌
- **Breadboard** 🛠️

## 📝 Code Explanation
```cpp
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define BUZZER_PIN 3
#define BUTTON_PIN 11
#define TRIG_PIN 9
#define ECHO_PIN 10

long T = 0;
float S = 0;

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
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  T = pulseIn(ECHO_PIN, HIGH);
  S = (T * 0.0343) / 2;

  if (S > 400 || S < 30) {
    S = 30; 
  }

  int columnsToFill = map(S, 30, 400, 16, 0);
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

  Serial.print("Distance: ");
  Serial.print(S);
  Serial.println(" cm");

  if (S <= 50) {
    tone(BUZZER_PIN, 1000);
  } else {
    noTone(BUZZER_PIN);
  }

  delay(1000);
}
```

## 🏗️ How to Build
1. **Connect the HC-SR04 sensor** to the Arduino:
   - VCC → 5V
   - Trig → Pin 9
   - Echo → Pin 10
   - GND → GND
2. **Connect the LCD display** using I2C:
   - VCC → 5V
   - GND → GND
   - SDA → A4
   - SCL → A5
3. **Connect the passive buzzer** to Pin 3.
4. **Upload the code** to your Arduino board.
5. **Power it on and test the distance measurement!**

## 🚀 Future Improvements
- 📊 **OLED Display Integration** for better visuals
- 📱 **Bluetooth or Wi-Fi connectivity** for remote monitoring
- 🔋 **Battery-powered version** for portability

## 🤝 Contributing
Feel free to **fork** this repository and contribute! PRs are welcome. 😊

## 📜 License
This project is open-source under the **MIT License**.

---
🔹 *Developed with passion by Mates!* 💡

