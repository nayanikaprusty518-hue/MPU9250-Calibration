# MPU9250 IMU Calibration and Orientation Estimation

## Overview
This project implements calibration and orientation estimation using the **MPU9250 IMU sensor**.  
The system reads accelerometer and gyroscope data, applies calibration offsets, and calculates the device orientation in terms of **Roll, Pitch, and Yaw**.

A **complementary filter** is used to fuse accelerometer and gyroscope data to obtain stable orientation estimates.

This project is useful for robotics systems such as **Autonomous Underwater Vehicles (AUVs), drones, and mobile robots** where accurate orientation estimation is required.

---
System Pipeline

MPU9250 Sensor
      │
      ▼
Raw Accelerometer & Gyroscope Data
      │
      ▼
Sensor Calibration (Bias Removal)
      │
      ▼
Complementary Filter
      │
      ▼
Orientation Estimation
(Roll, Pitch, Yaw)

## Hardware Used
- MPU9250 / MPU6500 IMU sensor
- Microcontroller (Arduino / ESP-based board)
- I2C communication

---

## Technologies Used
- Arduino C++
- I2C communication (Wire library)
- MPU9250_asukiaaa library
- Sensor calibration
- Complementary filter for sensor fusion

---

## Features
- Reads real-time accelerometer and gyroscope data
- Applies calibration offsets to remove sensor bias
- Calculates **Roll and Pitch using accelerometer measurements**
- Integrates gyroscope data for orientation tracking
- Implements **Complementary Filter** for stable orientation estimation
- Outputs **Roll, Pitch, and Yaw angles in degrees**
- Serial output for monitoring orientation in real time

---

## Orientation Estimation Method

### 1. Sensor Calibration
Offsets are applied to both accelerometer and gyroscope readings to remove bias:

- Accelerometer offsets correct gravity-based measurement errors
- Gyroscope offsets correct angular velocity drift

### 2. Accelerometer Angle Estimation
Roll and pitch are calculated from accelerometer values:

Roll  
atan2(ay, az)

Pitch  
atan2(-ax, sqrt(ay² + az²))

### 3. Gyroscope Integration
Gyroscope angular velocities are integrated over time to estimate motion.

### 4. Complementary Filter
The complementary filter combines accelerometer and gyroscope data:

roll = 0.98 × (roll + gyro × dt) + 0.02 × accel_angle

This approach provides:
- short-term accuracy from the gyroscope
- long-term stability from the accelerometer

### 5. Angle Wrapping
Angles are normalized between **-π and π** to prevent overflow during continuous rotation.

---

## Pin Configuration

| Sensor Pin | Controller Pin |
|-------------|---------------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 6 |
| SCL | GPIO 7 |

Communication uses the **I2C protocol**.

---

## How to Run

### 1. Install Required Library
Install the following Arduino library:

MPU9250_asukiaaa

### 2. Connect the MPU9250 Sensor
Connect the sensor using I2C as shown in the pin configuration table.

### 3. Upload the Code
Upload the Arduino sketch to your microcontroller.

### 4. Open Serial Monitor
Set baud rate to:

115200

You will see real-time output:

Roll: XX.X  Pitch: XX.X  Yaw: XX.X

---

## Applications
This system can be used in:

- Autonomous Underwater Vehicles (AUV)
- Drones and UAVs
- Robotics navigation systems
- Motion tracking systems
- Balance control systems

---

## Learning Outcomes
- Understanding IMU sensor calibration
- Implementing accelerometer and gyroscope bias correction
- Applying complementary filter for sensor fusion
- Real-time orientation estimation using IMU sensors
- Working with I2C communication in embedded systems

---

## Author
Nayanika Prusty  
Computer Engineering (AI & ML)  
SRM Institute of Science and Technology
