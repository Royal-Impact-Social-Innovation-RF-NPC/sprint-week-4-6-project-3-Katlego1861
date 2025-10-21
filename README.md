# Health IoT Device – Pulse Wave Project  

## Overview  
This repository contains the design, code, and documentation for a Health IoT device that monitors pulse and temperature, sends data to the cloud, and enables visualization through ThingSpeak and MIT App Inventor.  

The project integrates hardware, IoT connectivity, and app development to create a portable health monitoring solution.  

---

## Repository Contents  

| File / Folder                          | Description                                              |
|----------------------------------------|----------------------------------------------------------|
| '3D casing.zip'                      | 3D casing design files for the device (all angles)       |
| 'Bill of Material - Sheet1.csv'      | Complete Bill of Materials (components list)             |
| 'Copy of Pulse wave Flowchart.drawio.png' | Flowchart showing the IoT data flow from sensors to app |
| 'Pulse_Wave_Schematic.png'         | Exported schematic diagram of hardware connections       |
| 'Pulse Wave.drawio'                  | Editable schematic file (source)                        |
| 'Pulse_Wave_code.ino'               | Arduino/ESP32 source code for the IoT device             |
| 'README.md'                         | Project overview and documentation (this file)           |

---

## Features  
- Heart rate measurement using a pulse sensor  
- Temperature measurement using MLX90614 sensor  
- Live data display on LCD  
- IoT connectivity via ESP32 to ThingSpeak  
- Cloud data retrieval and visualization in MIT App Inventor  

---


### Hardware Requirements 
- ESP32 
- Pulse Sensor  
- MLX90614 Temperature Sensor  
- I2C LCD Display  
- LiPo Battery and Charger Module  
- Arduino IDE with the following libraries:  
  - PulseSensor Playground  
  - ThingSpeak  
  - DFRobot_MLX90614  
  - Wire
---
### Software Requirements
- [Arduino IDE](https://www.arduino.cc/en/software)  
- (Optional) [TinkerCAD](https://www.tinkercad.com/) for simulation  
- Onshape (for CAD modifications) 
---


## Author
Katlego Legari
