# Robotic Rover Arm

A gesture-controlled wireless robotic rover arm developed using ESP32, MPU6050 gyroscope and accelerometer sensor, HC-12 wireless communication, servo motors, Bluetooth communication, and an L293D motor driver. The system enables intuitive robotic arm manipulation and rover movement using hand gestures, with optional manual Bluetooth control.

---

## Overview

The Robotic Rover Arm is an embedded robotics project designed to provide intuitive gesture-based control of a robotic arm mounted on a mobile rover platform. The system uses hand motion sensing through an MPU6050 gyroscope and accelerometer sensor to capture user gestures, which are wirelessly transmitted to the receiver unit using HC-12 communication modules.

The receiver interprets these commands to control the robotic arm's servo motors and rover movement. Bluetooth communication is also integrated for manual control and flexibility.

This project demonstrates practical implementation of:

- Embedded Systems
- Wireless Communication
- Sensor Interfacing
- Motor Control
- Robotics
- Human-Machine Interaction
- Gesture Recognition

---

## Features

- Gesture-based robotic arm control
- Gyroscope-based motion detection
- Accelerometer-based gesture sensing
- Wireless communication using HC-12
- ESP32-based control system
- Bluetooth manual override control
- Real-time robotic arm movement
- Rover locomotion control
- Servo motor-based robotic arm
- Wireless camera integration
- Low-cost implementation

---

## Hardware Components

- ESP32 Development Board (2x)
- MPU6050 Gyroscope + Accelerometer Sensor
- HC-12 Wireless Communication Modules
- Servo Motors
- L293D Motor Driver
- DC Motors
- Wireless Camera
- DC-DC Buck Converter
- Battery Power Supply
- Robotic Arm Chassis
- Rover Platform
- Connecting Wires

---

## Software Used

- Arduino IDE
- Proteus
- CAD Design Software

---

## System Architecture

### Transmitter Section

The transmitter unit captures the user's hand movements using the MPU6050 gyroscope and accelerometer sensor. The ESP32 processes this motion data and sends corresponding control commands wirelessly via the HC-12 module.

**Functions:**
- Motion sensing
- Gesture detection
- Sensor data processing
- Wireless command transmission

---

### Receiver Section

The receiver unit receives the transmitted control commands through the HC-12 module. The ESP32 interprets the incoming data and controls the robotic arm servos and rover motors accordingly. Bluetooth communication allows optional manual operation.

**Functions:**
- Wireless data reception
- Servo motor control
- Rover motor control
- Bluetooth manual control

---

## Working Principle

1. User hand orientation and motion are detected using the MPU6050 sensor.
2. Sensor data is processed by the ESP32 transmitter.
3. Control commands are sent wirelessly through the HC-12 module.
4. The receiver ESP32 receives and interprets the commands.
5. Servo motors move the robotic arm based on the received gesture commands.
6. The L293D motor driver controls rover movement.
7. Bluetooth communication allows manual control when required.
8. The wireless camera provides remote visual monitoring.

---

## Circuit Diagrams

### Transmitter Section
Located in:
```bash
circuit_diagrams/transmitter_schematic.pdf
```

### Receiver Section
Located in:
```bash
circuit_diagrams/receiver_schematic.pdf
```


## Applications

- Space exploration
- Bomb disposal
- Hazardous environment operations
- Industrial automation
- Military reconnaissance
- Remote inspection
- Assistive robotics
- Search and rescue
- Educational robotics research

---

## Future Improvements

- AI-based object detection
- Autonomous navigation
- Obstacle avoidance
- IoT remote monitoring
- Voice control integration
- Live video streaming enhancement
- Improved gesture filtering algorithms
- More degrees of freedom in robotic arm
- Battery optimization

---

## Advantages

- Intuitive gesture-based control
- Wireless operation
- Real-time response
- Flexible design
- Easy scalability
- Low-cost implementation
- Suitable for remote operations

