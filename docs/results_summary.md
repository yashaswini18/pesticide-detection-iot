# Results & Discussion

---

## System Performance Summary

| Metric | Result |
|--------|--------|
| Pesticide Detection Rate | 95% |
| False Negatives | < 5% |
| False Positives | ~10% |
| Sorting Accuracy | 98% |
| Average Sorting Time per Fruit | 3–5 seconds |
| Temperature Monitoring Range | 20°C – 30°C |
| Humidity Monitoring Range | 50% – 70% |

---

## Sensor Reading Results (Table 5.1 from Report)

| S.No | Fruit/Vegetable | Gas Sensor (ppm) | Temp (°C) | Humidity (%) | Status |
|------|----------------|------------------|-----------|--------------|--------|
| 1 | Apple | 0.8 | 25 | 60 | ✅ Safe |
| 2 | Tomato | 2.5 | 28 | 65 | ❌ Contaminated |
| 3 | Cabbage | 1.0 | 26 | 62 | ✅ Safe |
| 4 | Grapes | 3.2 | 27 | 70 | ❌ Contaminated |
| 5 | Spinach | 2.0 | 24 | 58 | ❌ Contaminated |
| 6 | Mango | 0.5 | 29 | 55 | ✅ Safe |
| 7 | Potato | 1.5 | 22 | 50 | ✅ Safe |
| 8 | Carrot | 2.8 | 23 | 55 | ❌ Contaminated |

---

## Classification Logic

| Gas Sensor % Reading | Classification | Action |
|----------------------|----------------|--------|
| Below 30% | ✅ SAFE | Servo 1 → Safe Box |
| 30% – 50% | ⚠️ Normal Pesticide | Servo 1 → Safe Box + 1 beep |
| Above 55% | ❌ High Pesticide | Servo 2 → Reject Box + 3 beeps |

---

## Common Pesticides Detected

| Fruit/Vegetable | Common Pesticides | Type |
|----------------|-------------------|------|
| Orange | Sulfur, Tebuconazole | Fungicide |
| Apple | Sulfur, Captan | Fungicide |
| Banana | Paraquat, Sulfur | Herbicide |
| Carrot | Chlorpyrifos, Sulfur | Insecticide |
| Tomato | Malathion, Sulfur | Insecticide |
| Potato | Mancozeb, Sulfur | Fungicide |

---

## Discussion

### Strengths
- High sorting accuracy (98%) with minimal manual intervention
- Real-time feedback via LCD and Serial Monitor
- Cost-effective — Arduino + sensors total cost under ₹2,000
- Portable — suitable for farms, markets, and households

### Limitations
- Gas sensor sensitivity varies with humidity and temperature
- Threshold values need manual calibration for different pesticide types
- High false positive rate (~10%) needs improvement
- Currently limited to VOC-based detection only

### Future Improvements
- Add ESP8266/ESP32 for WiFi + cloud data logging
- Integrate machine learning for adaptive threshold tuning
- Add a camera module for visual inspection
- Expand sensor array to detect more pesticide types
- Develop a mobile app dashboard
