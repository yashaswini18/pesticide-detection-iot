/*
 * Monitoring of Pesticide Detection in Fresh Fruits and Vegetables
 * AMC Engineering College, Bengaluru
 * Department of Electronics & Communication Engineering
 * 
 * Authors:
 *   Suraj Pawar       (1AM21EC086)
 *   Syed Al Hameed    (1AM21EC088)
 *   Varsha B R        (1AM21EC095)
 *   Yashaswini R      (1AM21EC101)
 * 
 * Guide: Dr. R Aruna, Associate Professor
 * Academic Year: 2024-25
 * 
 * Components Used:
 *   - Arduino UNO R3
 *   - MQ-135 Gas Sensor (Analog Pin A0)
 *   - DHT11 Temperature & Humidity Sensor (Pin 6)
 *   - IR Sensor (Pin 7)
 *   - 16x2 LCD Display (Pins 8-13)
 *   - Servo Motor 1 - Good Fruit (Pin 3)
 *   - Servo Motor 2 - Bad Fruit  (Pin 5)
 *   - H-Bridge DC Motor IN1 (Pin A1), IN2 (Pin A2)
 *   - Buzzer (Pin A5)
 */

// ─── Libraries ───────────────────────────────────────────────────────────────
#include <LiquidCrystal.h>
#include <Servo.h>
#include <dht.h>

// ─── LCD Pin Configuration ────────────────────────────────────────────────────
// LCD(RS, EN, D4, D5, D6, D7)
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// ─── Servo Motors ─────────────────────────────────────────────────────────────
Servo servo1;   // Controls sorting for GOOD (safe) fruit
Servo servo2;   // Controls sorting for BAD (contaminated) fruit

// ─── DHT11 Sensor ─────────────────────────────────────────────────────────────
#define dht_dpin 6
dht DHT;

// ─── Pin Definitions ──────────────────────────────────────────────────────────
int IN1    = 15;   // H-Bridge Motor pin 1 (A1)
int IN2    = 16;   // H-Bridge Motor pin 2 (A2)
int Buzzer = 19;   // Buzzer pin (A5)
int IR     = 7;    // IR Sensor pin

// ─── Global Variables ─────────────────────────────────────────────────────────
int   a          = 0;      // Fruit detection flag
float Gas_val    = 0;      // Raw analog gas sensor reading
float percentage = 0;      // Pesticide level as percentage
float tempc      = 0;      // Temperature in Celsius
float Humidity   = 0;      // Humidity percentage

// ─────────────────────────────────────────────────────────────────────────────
// SETUP
// ─────────────────────────────────────────────────────────────────────────────
void setup() {
  // Pin modes
  pinMode(IR,     INPUT);
  pinMode(IN1,    OUTPUT);
  pinMode(IN2,    OUTPUT);
  pinMode(Buzzer, OUTPUT);

  // Attach servos and set to neutral position (90°)
  servo1.attach(3);
  servo2.attach(5);
  servo1.write(90);
  servo2.write(90);

  // Ensure motor and buzzer are OFF at start
  digitalWrite(IN1,    LOW);
  digitalWrite(IN2,    LOW);
  digitalWrite(Buzzer, LOW);

  // Initialize Serial Monitor
  Serial.begin(9600);
  Serial.println("=== Pesticide Detection System Started ===");

  // Initialize LCD and show welcome message
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vegetable Quality");
  lcd.setCursor(0, 1);
  lcd.print("    System      ");
  delay(3000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Ready...");
  delay(2000);
}

// ─────────────────────────────────────────────────────────────────────────────
// MAIN LOOP
// ─────────────────────────────────────────────────────────────────────────────
void loop() {
  Start();
}

// ─────────────────────────────────────────────────────────────────────────────
// START — Main workflow loop
// ─────────────────────────────────────────────────────────────────────────────
void Start() {
  while (1) {
    Sensor_Check();
    Humidity_Check();

    // Check IR sensor for fruit presence
    if (digitalRead(IR) == LOW) {
      a = 1;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Fruit Detected!");
      Serial.println(">> Fruit detected on conveyor.");
      delay(1000);
    }
  }
}

// ─────────────────────────────────────────────────────────────────────────────
// HUMIDITY CHECK — Reads and displays temperature & humidity from DHT11
// ─────────────────────────────────────────────────────────────────────────────
void Humidity_Check(void) {
  DHT.read11(dht_dpin);
  Humidity = DHT.humidity;
  tempc    = DHT.temperature;

  // Display on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity: ");
  lcd.print(Humidity);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(tempc);
  lcd.print(" C");

  // Print to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(Humidity);
  Serial.print(" %  |  Temp: ");
  Serial.print(tempc);
  Serial.println(" C");

  delay(2000);
}

// ─────────────────────────────────────────────────────────────────────────────
// SENSOR CHECK — Reads gas sensor and classifies pesticide level
// Classification:
//   percentage 30–50% → Normal Pesticide → Safe box
//   percentage > 55%  → High Pesticide   → Reject box
// ─────────────────────────────────────────────────────────────────────────────
void Sensor_Check() {
  Gas_val    = analogRead(A0);
  percentage = (Gas_val - 0) / (1023.0 - 0) * 100;

  // Display gas reading on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gas Level:");
  lcd.setCursor(0, 1);
  lcd.print(percentage);
  lcd.print(" %");

  // Print to Serial Monitor
  Serial.print("Gas Sensor Value: ");
  Serial.print(Gas_val);
  Serial.print("  |  Pesticide %: ");
  Serial.println(percentage);

  delay(1000);

  // ── NORMAL PESTICIDE (30% – 50%) ──────────────────────────────────────────
  if ((percentage > 30) && (percentage < 50) && (a == 1)) {
    a = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Normal Pesticide");
    lcd.setCursor(0, 1);
    lcd.print("Sorting: Safe...");
    Serial.println(">> Classification: Normal Pesticide → Safe Box");
    delay(1000);

    Move();                 // Move conveyor forward
    Seperate_Good_Fruit();  // Sort to good/safe box

    digitalWrite(Buzzer, HIGH);
    delay(500);
    digitalWrite(Buzzer, LOW);
  }

  // ── HIGH PESTICIDE (> 55%) ─────────────────────────────────────────────────
  if ((percentage > 55) && (a == 1)) {
    a = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("High Pesticide!");
    lcd.setCursor(0, 1);
    lcd.print("Sulfur Detected");
    Serial.println(">> Classification: HIGH Pesticide → Reject Box");
    delay(2000);

    Move_1();               // Move conveyor further
    Seperate_Bad_Fruit();   // Sort to contaminated/reject box

    // Alert buzzer — 3 beeps
    for (int i = 0; i < 3; i++) {
      digitalWrite(Buzzer, HIGH);
      delay(300);
      digitalWrite(Buzzer, LOW);
      delay(200);
    }
  }

  // ── SAFE (Below 30%) ───────────────────────────────────────────────────────
  if ((percentage < 30) && (a == 1)) {
    a = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Fruit is SAFE ");
    lcd.setCursor(0, 1);
    lcd.print("No Pesticide :) ");
    Serial.println(">> Classification: SAFE → Safe Box");
    delay(1000);

    Move();
    Seperate_Good_Fruit();
  }
}

// ─────────────────────────────────────────────────────────────────────────────
// MOVE — Runs conveyor belt for a short distance (good fruit position)
// ─────────────────────────────────────────────────────────────────────────────
void Move() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moving Conveyor.");
  Serial.println(">> Conveyor moving (short)...");

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(700);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  delay(1000);
}

// ─────────────────────────────────────────────────────────────────────────────
// MOVE_1 — Runs conveyor belt for a longer distance (bad fruit position)
// ─────────────────────────────────────────────────────────────────────────────
void Move_1() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moving Conveyor.");
  Serial.println(">> Conveyor moving (long)...");

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  delay(1600);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  delay(1000);
}

// ─────────────────────────────────────────────────────────────────────────────
// SEPERATE GOOD FRUIT — Servo 1 sorts fruit into safe box
// ─────────────────────────────────────────────────────────────────────────────
void Seperate_Good_Fruit() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  Safe Fruit    ");
  lcd.setCursor(0, 1);
  lcd.print("Sorting to Box 1");
  Serial.println(">> Servo 1 → Safe Box.");

  servo1.write(0);    // Rotate servo to sort fruit
  delay(2000);
  servo1.write(90);   // Return to neutral
  delay(1000);

  // Reset and restart
  Start();
}

// ─────────────────────────────────────────────────────────────────────────────
// SEPERATE BAD FRUIT — Servo 2 sorts fruit into reject/contaminated box
// ─────────────────────────────────────────────────────────────────────────────
void Seperate_Bad_Fruit() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Contaminated!   ");
  lcd.setCursor(0, 1);
  lcd.print("Sorting to Box 2");
  Serial.println(">> Servo 2 → Reject Box.");

  servo2.write(0);    // Rotate servo to sort fruit
  delay(2000);
  servo2.write(90);   // Return to neutral
  delay(1000);

  // Reset and restart
  Start();
}

// ─────────────────────────────────────────────────────────────────────────────
// WAITING — Waits for manual Serial command ('G' = Good, 'B' = Bad)
// Useful for testing without a physical fruit
// ─────────────────────────────────────────────────────────────────────────────
void Waiting() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Waiting for cmd.");
  Serial.println(">> Waiting... Send 'G' for Good, 'B' for Bad.");

  while (1) {
    if (Serial.available() > 0) {
      char ch = Serial.read();

      if (ch == 'G') {
        lcd.clear();
        lcd.print("Manual: GOOD");
        Serial.println(">> Manual override: GOOD fruit.");
        Move();
        Seperate_Good_Fruit();
      }

      if (ch == 'B') {
        lcd.clear();
        lcd.print("Manual: BAD");
        Serial.println(">> Manual override: BAD fruit.");
        Move_1();
        Seperate_Bad_Fruit();
      }
    }
  }
}