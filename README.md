# Smart-Health-Tracking-System
![Project Status](https://img.shields.io/badge/status-Completed-brightgreen.svg)
![Platform](https://img.shields.io/badge/platform-ESP32%20%7C%20Arduino-blue.svg)
![Microcontroller](https://img.shields.io/badge/microcontroller-ESP32-yellowgreen.svg)
![Sensors](https://img.shields.io/badge/sensors-ECG%20%7C%20SpO2%20%7C%20Temp%20%7C%20MPU6050-orange.svg)
![Language](https://img.shields.io/badge/language-C%2FC%2B%2B-00599C.svg)
![IDE](https://img.shields.io/badge/IDE-Arduino%20IDE-success.svg)

---

## Project Description
The **Smart Health Tracking System** is a real-time, wearable IoT-based solution that monitors heart rate, temperature, and SpO2 levels using real-time sensors. Includes fall detection via MPU sensor—ideal for elderly or patient care. Health data is shown on a live dashboard, enabling remote monitoring, early alerts, and smart health management.


**It measures:**
-  ECG (heart activity)  
-  SpO₂ and Heart Rate  
-  Body Temperature  
-  Motion and Fall Detection  

**Key Features:**
- Built using **ESP32/Arduino** with embedded C/C++  
- Real-time data transmission via **Bluetooth or Wi-Fi**  
- Displays data on mobile, laptop, or serial plotter  
- Triggers alerts on abnormal readings  
- Validated through real-patient testing  

---

## Components Used

- **Arduino UNO**  
- **AD8232** – ECG sensor  
- **MAX30100** – Heart Rate & SpO₂  
- **DS18B20** – Temperature sensor  
- **MPU6050** – Motion & fall detection  
- **HC-05** – Wireless communication  

---

## Testing Summary

| Sensor       | Accuracy   | Validation                         |
|--------------|------------|------------------------------------|
| ECG          | ~98%       | Compared to clinical ECG monitor   |
| SpO₂ & HR    | ~97%       | Matched standard oximeter          |
| Temperature  | ±0.2°C     | Compared to digital thermometer    |
| Motion       | ~95%       | Fall detection tested manually     |
| Wireless     | Stable     | 10–20m range, ~200ms latency       |

---

## Future Work

- Cloud data logging and dashboard  
- AI-based health prediction (e.g., arrhythmia detection)  
- Battery optimization and wearable enclosure  
- Custom Android app development

---

## Conclusion

This system provides a practical, low-cost alternative to hospital-grade monitors. It is portable, multi-functional, and tested successfully on a real patient — bridging the gap between wearable tech and accessible healthcare.

---
