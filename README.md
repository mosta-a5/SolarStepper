
# SolarStepper

SolarStepper is a stepper motor-based solar tracking system that uses two LDR sensors to detect sunlight direction and rotate a solar panel accordingly. It includes limit switches to prevent over-rotation and supports microstepping for smooth motor control.

## 🌞 Features
- Dual LDR-based sunlight detection
- Stepper motor control with microstepping
- Limit switch protection for east and west boundaries
- Adjustable motor speed via delay control
- Serial monitoring of sensor values and motor status

## 🛠 Hardware Components
- Arduino Uno
- Stepper Motor + Driver (e.g., A4988 or DRV8825)
- 2 LDR sensors
- 2 Limit switches
- Resistors, jumper wires, breadboard

## 🔌 Wiring Connections
| Component           | Arduino Pin |
|--------------------|-------------|
| East Limit Switch  | 12          |
| West Limit Switch  | 11          |
| Enable             | 10          |
| MS1                | 9           |
| MS2                | 8           |
| MS3                | 7           |
| Reset              | 6           |
| Sleep              | 5           |
| Step               | 4           |
| Direction          | 3           |
| LDR1               | A0          |
| LDR2               | A1          |

## ⚙️ How It Works
- The system reads values from two LDRs.
- If the light difference exceeds a threshold, the motor rotates toward the brighter side.
- Limit switches stop movement at boundaries.
- Microstepping settings can be adjusted via MS1, MS2, MS3 pins.

## 📋 Usage Instructions
1. Assemble the hardware as per the wiring table.
2. Upload the Arduino sketch to your board.
3. Open the Serial Monitor to observe sensor readings and motor actions.
4. Adjust `stepDelay` to control motor speed.

## 📜 License
This project is licensed under the **Creative Commons Attribution 4.0 International (CC BY 4.0)**.

You are free to:
- Share — copy and redistribute the material in any medium or format
- Adapt — remix, transform, and build upon the material for any purpose, even commercially.

Under the following terms:
- Attribution — You must give appropriate credit, provide a link to the license, and indicate if changes were made.

License details: [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/)

## 🙌 Credits
Created by Mostafa Zakaria. Please credit the original author when using or modifying this project.
