# Hardware Connections

## Arduino UNO R3 — Complete Pin Wiring

---

### LCD Display (16x2) → Arduino UNO

| LCD Pin | Symbol | Arduino Pin | Notes |
|---------|--------|-------------|-------|
| Pin 1 | VSS | GND | Ground |
| Pin 2 | VCC | 5V | Power |
| Pin 3 | VEE | Middle of 10kΩ pot | Contrast control |
| Pin 4 | RS | Pin 13 | Register Select |
| Pin 5 | R/W | GND | Always Write mode |
| Pin 6 | EN | Pin 12 | Enable |
| Pin 11 | D4 | Pin 11 | Data |
| Pin 12 | D5 | Pin 10 | Data |
| Pin 13 | D6 | Pin 9 | Data |
| Pin 14 | D7 | Pin 8 | Data |
| Pin 15 | A (LED+) | 5V via 220Ω resistor | Backlight |
| Pin 16 | K (LED-) | GND | Backlight GND |

---

### DHT11 Sensor → Arduino UNO

| DHT11 Pin | Arduino Pin | Notes |
|-----------|-------------|-------|
| VCC | 5V | Power |
| DATA | Pin 6 | Digital signal |
| GND | GND | Ground |

> **Tip:** Place a 10kΩ pull-up resistor between DATA and VCC.

---

### IR Sensor Module → Arduino UNO

| IR Sensor Pin | Arduino Pin | Notes |
|---------------|-------------|-------|
| VCC | 5V | Power |
| GND | GND | Ground |
| OUT | Pin 7 | Digital output (LOW = fruit detected) |

---

### MQ-135 Gas Sensor → Arduino UNO

| MQ-135 Pin | Arduino Pin | Notes |
|------------|-------------|-------|
| VCC | 5V | Power |
| GND | GND | Ground |
| AOUT | A0 | Analog output (0–1023) |
| DOUT | Not connected | (Digital threshold, unused) |

> **Tip:** Allow 2–3 minutes warm-up time after powering on for accurate readings.

---

### H-Bridge Motor Driver (L298N) → Arduino UNO

| L298N Pin | Arduino Pin | Notes |
|-----------|-------------|-------|
| IN1 | Pin A1 (15) | Motor direction control |
| IN2 | Pin A2 (16) | Motor direction control |
| VCC | 5V–12V | Motor power supply |
| GND | GND | Common ground |
| OUT1 | DC Motor terminal 1 | Conveyor belt motor |
| OUT2 | DC Motor terminal 2 | Conveyor belt motor |

---

### Servo Motor 1 (Good/Safe Fruit) → Arduino UNO

| Servo Wire | Arduino Pin | Notes |
|------------|-------------|-------|
| Red (VCC) | 5V | Power |
| Brown (GND) | GND | Ground |
| Orange (Signal) | Pin 3 (PWM) | Control signal |

---

### Servo Motor 2 (Bad/Contaminated Fruit) → Arduino UNO

| Servo Wire | Arduino Pin | Notes |
|------------|-------------|-------|
| Red (VCC) | 5V | Power |
| Brown (GND) | GND | Ground |
| Orange (Signal) | Pin 5 (PWM) | Control signal |

---

### Buzzer → Arduino UNO

| Buzzer Pin | Arduino Pin | Notes |
|------------|-------------|-------|
| + (Positive) | Pin A5 (19) | Signal |
| - (Negative) | GND | Ground |

---

## Complete Pin Summary (Quick Reference)

| Component | Arduino Pin | Mode |
|-----------|-------------|------|
| Gas Sensor (MQ-135) | A0 | Analog Input |
| DHT11 Data | 6 | Digital Input |
| IR Sensor Output | 7 | Digital Input |
| LCD D7 | 8 | Digital Output |
| LCD D6 | 9 | Digital Output |
| LCD D5 | 10 | Digital Output |
| LCD D4 | 11 | Digital Output |
| LCD EN | 12 | Digital Output |
| LCD RS | 13 | Digital Output |
| H-Bridge IN1 | A1 (15) | Digital Output |
| H-Bridge IN2 | A2 (16) | Digital Output |
| Buzzer | A5 (19) | Digital Output |
| Servo 1 (Safe) | 3 | PWM Output |
| Servo 2 (Reject) | 5 | PWM Output |

---

## Power Supply Notes

- The Arduino UNO is powered via **USB (5V)** or external **7–12V DC** jack.
- The DC motor should ideally be powered from a **separate 5V–12V supply** through the L298N to avoid browning out the Arduino.
- All grounds must be **connected together (common GND)**.

---

## Important Notes

1. Do not exceed **40mA** per Arduino digital pin.
2. The MQ-135 sensor requires **pre-heating for 2–3 minutes** for stable readings.
3. IR sensor sensitivity can be adjusted using the **onboard potentiometer**.
4. Servo motors draw significant current — if the system resets, power servos from a **separate 5V supply**.