# 🚀 IMU-ToF Sensor Fusion for Tilt and Displacement Measurement

## 📌 Overview
This project implements a **real-time motion tracking system** using:
- **MPU6050 (IMU)** for tilt angle estimation  
- **VL53L0X (ToF Sensor)** for distance measurement  
- **ESP32** for processing  

The system calculates:
- 📐 Tilt Angle (degrees)  
- 📏 Height Difference (mm)  
- 📊 Linear Displacement (mm)  

---

## 🎯 Features
- Real-time tilt estimation using **sensor fusion**
- Complementary filter for **noise reduction & stability**
- Trigonometric height calculation
- Accurate distance measurement using ToF sensor
- Lightweight and efficient embedded implementation

---

## 🖼️ Project Images

### 🔹 Hardware Setup
![Hardware](Screenshot%202026-01-18%20231405.png)

### 🔹 Serial Output
![Output](Screenshot%202026-01-18%20231432.png)

### 🔹 Final Result
![Result](Screenshot%202026-01-18%20231507.png)

---

## 🧠 Working Principle

### 1. Sensor Fusion (Complementary Filter)

```cpp
angle = alpha * (angle + gyroRate * dt) + (1 - alpha) * accelAngle;
