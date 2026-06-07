# Libraries & Software Requirements

## Arduino IDE

Download and install the Arduino IDE from the official website:
- **Download:** https://www.arduino.cc/en/software
- **Minimum version:** Arduino IDE 1.8.5
- **Compatible OS:** Windows 7/8/10/11, macOS 10.8+, Linux (32/64-bit)

---

## Required Arduino Libraries

### 1. LiquidCrystal.h
- **Purpose:** Controls the 16x2 LCD display
- **Status:** ✅ Built-in — no installation needed
- **Included with:** Arduino IDE by default

### 2. Servo.h
- **Purpose:** Controls Servo Motor 1 and Servo Motor 2
- **Status:** ✅ Built-in — no installation needed
- **Included with:** Arduino IDE by default

### 3. dht.h (DHT Sensor Library)
- **Purpose:** Reads temperature and humidity from the DHT11 sensor
- **Status:** ⚠️ Must be installed manually

#### How to Install dht.h

**Method 1 — Arduino Library Manager (Recommended):**
1. Open Arduino IDE
2. Go to **Sketch → Include Library → Manage Libraries**
3. In the search box, type: `DHT sensor library`
4. Find **"DHT sensor library" by Adafruit**
5. Click **Install**
6. Also install **"Adafruit Unified Sensor"** if prompted

**Method 2 — Manual ZIP Install:**
1. Download from: https://github.com/adafruit/DHT-sensor-library/archive/refs/heads/master.zip
2. Open Arduino IDE
3. Go to **Sketch → Include Library → Add .ZIP Library**
4. Select the downloaded ZIP file
5. Click OK

---

## Hardware Requirements

| Item | Specification |
|------|--------------|
| Microcontroller | Arduino UNO R3 (ATmega328P, 16 MHz) |
| Operating Voltage | 5V |
| Flash Memory | 32 KB |
| SRAM | 2 KB |
| EEPROM | 1 KB |
| Digital I/O Pins | 14 (6 PWM) |
| Analog Input Pins | 6 |
| USB Connection | USB-A to USB-B cable |
| Computer | Windows/Mac/Linux with USB port |

---

## Software Setup Checklist

- [ ] Arduino IDE installed
- [ ] LiquidCrystal.h available (built-in)
- [ ] Servo.h available (built-in)
- [ ] dht.h installed via Library Manager
- [ ] Arduino UNO connected via USB
- [ ] Correct COM port selected in Arduino IDE
- [ ] Board set to **Arduino UNO** in Tools menu
- [ ] Code uploaded successfully
- [ ] Serial Monitor set to **9600 baud**

---

## Verifying the Setup

After uploading the code:
1. Open **Tools → Serial Monitor** in Arduino IDE
2. Set baud rate to **9600**
3. You should see:
```
=== Pesticide Detection System Started ===
Humidity: 55.00 %  |  Temp: 27.00 C
Gas Sensor Value: 312  |  Pesticide %: 30.50
```
4. Place a fruit near the IR sensor — the LCD should display **"Fruit Detected!"**
