# Fire Fighting Robot

This repository contains code for an Arduino-based Fire Fighting Robot. The robot is designed to detect flames and gas, navigate toward the fire, and extinguish it using a water pump and servo mechanism.

## Features

- **Flame Detection:** Uses three flame sensors to detect fire direction (left, middle, right).
- **Gas Detection:** Monitors air quality using a gas sensor.
- **Obstacle Avoidance:** Utilizes four IR sensors (front, back, left, right) for navigation.
- **Movement Control:** Controls two motors (left and right) for movement and turning.
- **Automatic Fire Extinguishing:** Activates a water pump and sweeps the servo to spray water on fire.
- **Serial Communication:** Outputs status via Serial for debugging.

## Hardware Connections

| Pin   | Component                  |
|-------|----------------------------|
| 0     | IR Sensor Right            |
| 1     | IR Sensor Left             |
| 2     | IR Sensor Front            |
| 3     | IR Sensor Back             |
| 4, 5  | Left Motor (LM1, LM2)      |
| 6, 7  | Right Motor (RM1, RM2)     |
| 8     | Flame Sensor Right (RF)    |
| 9     | Flame Sensor Middle (MF)   |
| 10    | Flame Sensor Left (LF)     |
| 11    | Gas Sensor                 |
| 12    | Servo Motor                |
| 13    | Water Pump                 |

## How It Works

1. The robot continuously checks for fire or gas detection.
2. When fire or gas is detected, it navigates toward the source using IR and flame sensors.
3. Once the fire is reached, it activates the water pump and sweeps the servo to extinguish the fire.
4. Obstacle avoidance logic allows the robot to maneuver around objects in its path.

## Getting Started

1. Wire the hardware according to the table above.
2. Upload the `Fire_Fighting_Robot.ino` code to your Arduino board.
3. Open the Serial Monitor for status updates.

## Dependencies

- Arduino Servo library

## Usage

Simply power up the robot. It will automatically begin scanning for fire and gas, navigating and extinguishing as needed.
