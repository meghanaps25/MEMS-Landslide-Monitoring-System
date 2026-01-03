# MEMS Based Distributed Sensor Network for Landslide Prediction and Alert Generation

##  Project Overview
Landslides are a major natural hazard in hilly and high-rainfall regions.  
This project presents a **MEMS-based distributed sensor network** that continuously monitors **soil pressure and rainfall conditions** to predict potential landslide events and generate early alerts.

The system uses **MEMS pressure sensors** and a **raindrop sensor** connected to an **Arduino microcontroller**. When predefined threshold values are exceeded, the system triggers a **local alert (buzzer)** and sends an **SMS notification via GSM module** to concerned authorities.

---

## Objectives
- Real-time monitoring of soil pressure and rainfall
- Early detection of landslide-prone conditions
- Automated alert generation using GSM
- Cost-effective and scalable embedded solution
- Reduce risk to life and infrastructure

---

## System Architecture
The system consists of multiple MEMS pressure sensors deployed in landslide-prone zones along with a rainfall sensor.  
Sensor data is processed by an Arduino microcontroller and compared with predefined thresholds.  
If abnormal conditions are detected, alerts are generated instantly.

---

## Hardware Components
- Arduino Uno  
- MEMS Pressure Sensors  
- Raindrop Sensor  
- GSM Module  
- LCD Display  
- Buzzer  
- Power Supply Unit  

---

## Software & Tools
- Embedded C  
- Arduino IDE  
- Serial Communication  
- GSM AT Commands  

---

## Working Principle
1. MEMS pressure sensors measure soil pressure continuously.  
2. Raindrop sensor monitors rainfall intensity.  
3. Arduino compares sensor data with threshold values.  
4. If thresholds are exceeded:
   - Local buzzer is activated  
   - SMS alert is sent via GSM module  
5. LCD displays real-time system status.

---

##  Repository Structure
MEMS-Landslide-Monitoring-System/
│
├── code/ # Arduino source code
│ └── landslide_monitoring.ino
│
├── documentation/ # Project documentation
│ └── Project_Report.pdf
│
├── circuit-diagram/ # Block / circuit diagrams
│ └── block_diagram.png
│
├── images/ # Hardware setup images
│ └── hardware_setup.jpg
│
└── README.md
