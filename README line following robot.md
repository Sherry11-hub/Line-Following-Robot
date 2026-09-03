# 🤖 Line Following Robot

An Arduino-based robot that follows a black line on the floor using a 4-channel IR sensor array and a dual DC motor driver.

## How it works

Four IR sensors are mounted across the front of the robot, spaced left-to-right (`Left`, `Middle-Left`, `Middle-Right`, `Right`). Each sensor reads `0` when it's over a black line and `1` when it's over a lighter surface. On every loop, the robot reads all four sensors and decides how to steer:

| Sensor pattern | Meaning | Action |
|---|---|---|
| Only the two middle sensors see the line | Line is centered | Move forward |
| Middle-left sensor sees the line | Line has drifted slightly left | Slight right turn |
| Middle-right sensor sees the line | Line has drifted slightly right | Slight left turn |
| Only the far-left sensor sees the line | Sharp turn needed | Sharp right turn |
| Only the far-right sensor sees the line | Sharp turn needed | Sharp left turn |
| All four sensors see black | Junction, wide line, or stop marker | Stop motors |
| No sensor sees the line | Line lost | Stop motors |

Motor speed is set via `analogWrite()` (PWM) on the enable pins, and direction is set via `digitalWrite()` on the motor driver's input pins.

## Hardware

- Arduino board (Uno/Nano or similar)
- Dual DC motor driver (2-motor H-bridge, e.g. L298N-style)
- 2x DC gear motors + wheels + chassis
- 4-channel IR line sensor array
- Battery pack for motors

## Pin configuration

| Function | Arduino Pin |
|---|---|
| Right Motor MA1 | 7 |
| Right Motor MA2 | 8 |
| Left Motor MB1 | 9 |
| Left Motor MB2 | 10 |
| Right Motor Enable (PWM) | 6 |
| Left Motor Enable (PWM) | 5 |
| Left IR Sensor | A1 |
| Middle-Left IR Sensor | A2 |
| Middle-Right IR Sensor | A3 |
| Right IR Sensor | A4 |

Rewire `#define` values at the top of `sketch_mar18a.ino` if your setup uses different pins.

## Getting started

1. Wire up the motor driver and IR sensor array according to the pin table above.
2. Open `sketch_mar18a.ino` in the [Arduino IDE](https://www.arduino.cc/en/software).
3. Select your board and port under **Tools**.
4. Click **Upload**.
5. Place the robot on a track with a black line on a lighter background and power it on.

## Tuning

- **Speed**: adjust the values passed to `moveForward()`, `turnRight()`, and `turnLeft()` (currently `120` for normal driving, `80` for sharp turns).
- **Line lost / junction behavior**: both currently call `stopMotors()`. You can replace these with a search routine (e.g. rotate in place until the line is reacquired) if needed.

## Project structure

```
.
└── sketch_mar18a.ino   # Full robot logic: sensor reading, decision logic, motor control
```
