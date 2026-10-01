# 🚗 Road Rush — ESP32 OLED Game

A compact embedded gaming project built using an ESP32, 128×64 OLED display, push button, and LED.

## 📌 Project Overview

Road Rush is an ESP32-based mini gaming project developed to demonstrate embedded programming, OLED graphics, digital input/output, I2C communication, and hardware-software integration.

## 🛠️ Hardware Components

- ESP32 Dev Module
- 128×64 SH1106 OLED Display
- Push Button
- LED
- 220Ω / 330Ω Resistor
- Breadboard
- Jumper Wires

## 🔌 Circuit Connections

### OLED Display

| OLED Pin | ESP32 Pin |
|---|---|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL / SCK | GPIO 22 |

### Push Button

| Button | ESP32 |
|---|---|
| Signal | GPIO 5 |
| Other Side | GND |

The button uses the ESP32 internal pull-up resistor with `INPUT_PULLUP`.

### LED

| LED | Connection |
|---|---|
| Long Leg (+) | GPIO 18 through 220Ω / 330Ω resistor |
| Short Leg (-) | GND |

## 🖥️ OLED Display

Display: 128×64 SH1106 OLED
Communication: I2C
I2C Address: `0x3C`

## 📚 Libraries

- Adafruit GFX Library
- Adafruit SH110X

The project uses:

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

## ⚙️ Current Functionality

The current prototype demonstrates:

- ESP32 initialization
- OLED initialization
- OLED text rendering
- Push-button input
- Button press detection
- LED control
- I2C communication
- Interactive OLED feedback

## 🎮 Road Rush Game

The hardware setup is designed for the Road Rush car-dodging game.

Planned game features include:

- 🚗 Player car
- 🛣️ Moving road
- 🚘 Enemy vehicles
- ↔️ Lane changing
- 💥 Collision detection
- 🏆 Score system
- 💡 LED indicators
- 🔄 Game restart functionality

## 📂 Project Structure

Road-Rush-ESP32/
├── Road-Rush-ESP32.ino
└── README.md

## 🚀 Getting Started

1. Install Arduino IDE.
2. Install ESP32 board support.
3. Select `ESP32 Dev Module`.
4. Install `Adafruit GFX Library`.
5. Install `Adafruit SH110X`.
6. Connect the hardware according to the wiring table.
7. Select the correct COM port.
8. Upload `Road-Rush-ESP32.ino`.

## 🔧 Pin Configuration

#define BUTTON_PIN 5
#define LED_PIN 18

OLED:

SDA → GPIO 21
SCL → GPIO 22

## 🔮 Future Improvements

- Multiple difficulty levels
- Increasing game speed
- High-score storage
- Better car graphics
- Animated road markings
- Sound effects
- Speaker or buzzer support
- Multiple control buttons
- Start menu
- Pause system
- Game-over screen
- Wi-Fi/Bluetooth features

## 🎯 Learning Objectives

This project demonstrates:

- Embedded C/C++ programming
- ESP32 GPIO programming
- I2C communication
- OLED graphics
- Digital input and output
- Game logic
- Hardware-software integration

## 👨‍💻 Author

Soham Vartak

Engineering Student

## 📜 License

This project is intended for educational and personal development purposes.
