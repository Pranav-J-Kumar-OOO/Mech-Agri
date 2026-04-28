# Mech-Agri 🌱
IoT-based smart irrigation system with real-time soil and environment monitoring.

Built at 15 for a science expo. A two-board system that monitors soil conditions
across 3 independent zones and automatically triggers irrigation when moisture
drops below threshold — no manual input needed.

---

## The Problem
Traditional farming relies on manual irrigation scheduling, which wastes water
and leads to either overwatering or crop stress. Mech-Agri solves this by
continuously monitoring soil conditions and triggering irrigation automatically,
zone by zone — with live data visible on both a local OLED display and a cloud
dashboard from anywhere.

---

## Hardware Photos

<p align="center">
  <img src="docs/v1_top.jpg" width="45%" alt="Mech-Agri v1 top view"/>
  &nbsp;&nbsp;
  <img src="docs/v1_expo.jpg" width="45%" alt="Mech-Agri at expo"/>
</p>

> Handmade octagonal cardboard enclosure with Arduino, ESP32, breadboard,
> relay module, and soil probes. Built and presented at a South India
> inter-school science expo.

---

## Architecture

Two-board split design:

```
[Arduino Uno]                              [ESP32]
  DHT22 → temp & humidity          Serial → Receives all sensor data
  3x moisture sensors    ────────►         Pushes to Blynk cloud
  4x relay outputs                         Live update every 1 second
  SSD1306 OLED display                     Accessible from any device
```

---

## Auto Irrigation Logic

Each of the 3 zones has an independent relay. A master relay (relay 4) acts
as a global trigger.

```
Zone moisture < 20%  →  Zone relay ON   →  Irrigation triggered
Zone moisture ≥ 20%  →  Zone relay OFF  →  Irrigation stopped

Any zone dry         →  Master relay ON
All zones OK         →  Master relay OFF
```

---

## What It Monitors

| Sensor | Measurement | Output |
|--------|-------------|--------|
| DHT22 | Temperature | °C |
| DHT22 | Humidity | % |
| Moisture sensor — Zone 1 | Soil moisture | % |
| Moisture sensor — Zone 2 | Soil moisture | % |
| Moisture sensor — Zone 3 | Soil moisture | % |

All values displayed on the onboard OLED and streamed live to the
Blynk cloud dashboard.

---

## Hardware

- Arduino Uno — sensor reading, relay control, OLED display
- ESP32 — WiFi connectivity, Blynk cloud integration
- DHT22 — temperature & humidity sensor
- 3x soil moisture sensors
- 4x relay module (3 zone relays + 1 master relay)
- SSD1306 OLED display (128x32)
- Handmade octagonal cardboard enclosure

---

## Hardware Iterations

**v1** — Resistive soil moisture sensors *(pictured above)*

**v2 (final expo version)** — Upgraded to capacitive sensors for improved
accuracy and longevity. Resistive sensors corrode over time and give
inconsistent readings in wet soil — capacitive sensors resolved both issues.

---

## Stack

- **Arduino (C++)** — sensor reading, relay logic, OLED display driver
- **ESP32 + Blynk** — WiFi bridge, live cloud dashboard
- **Fritzing** — circuit diagrams (`.fzz` files included)

---

## Dependencies

```
Arduino libraries:
- DHT sensor library (Adafruit)
- Adafruit GFX Library
- Adafruit SSD1306
- BlynkSimpleEsp32
```

---

## Project Structure

```
Mech-Agri/
├── Mech-Agri.ino                  # Arduino main sketch
├── ESP32_prototype/
│   ├── ESP32_prototype.ino        # ESP32 Blynk bridge
│   ├── BlynkEdgent.h
│   └── ...                        # Blynk config headers
├── Mech-Agri Blueprint.pdf        # Circuit diagram (PDF)
├── Mech-Agri Blueprint1.fzz       # Fritzing schematic
└── docs/
    ├── v1_top.jpg                 # Hardware photo — top view
    └── v1_expo.jpg                # Hardware photo — expo
```

---

## Setup

1. Flash `Mech-Agri.ino` to Arduino Uno
2. Create a Blynk project and add your auth token to `ESP32_prototype.ino`
3. Add your WiFi credentials to `ESP32_prototype.ino`
4. Flash `ESP32_prototype.ino` to ESP32
5. Connect Arduino Serial TX/RX to ESP32 pins 16/17
6. Power up — data streams to Blynk dashboard automatically

> ⚠️ Never commit real credentials. Use placeholders and add a `.gitignore`
> for any config files containing tokens or passwords.

---

## Built

2023 · Science Expo · Age 15

---

## Note

Code preserved from expo build. The final expo version used capacitive
moisture sensors; this code reflects an earlier resistive-sensor iteration.
Circuit diagrams and hardware photos included.
