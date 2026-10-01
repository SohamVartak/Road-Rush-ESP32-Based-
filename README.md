# Road Rush - ESP32 🚗

A mini car-dodging game project made using an ESP32 and a 128x64 OLED display.

## Hardware

- ESP32 Dev Module
- 128x64 SH1106 OLED display
- Push button
- LED
- 220Ω / 330Ω resistor
- Breadboard
- Jumper wires

## Connections

| Component | ESP32 |
|---|---|
| OLED VCC | 3.3V |
| OLED GND | GND |
| OLED SDA | D21 |
| OLED SCL/SCK | D22 |
| Push Button | D5 |
| LED | D18 |
| LED GND | GND through resistor |

## Current Features

- ESP32-based project
- OLED display
- Push-button input
- LED output
- I2C communication

## Libraries

Install these libraries in Arduino IDE:

- Adafruit GFX Library
- Adafruit SH110X

## Board

Arduino IDE board:

`ESP32 Dev Module`

## OLED

Display:

`128x64 SH1106`

I2C address:

`0x3C`

## Author

Soham Vartak
