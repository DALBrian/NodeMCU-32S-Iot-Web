# NodeMCU-32S-Iot-Web

A complete IoT project using an ESP32 (NodeMCU-32S) development board to collect temperature and humidity data from a DHT22 temperature & humidity sensor and send it to a Flask-based web server. The data is stored in a SQLite database and visualized on a web dashboard using Chart.js.

---

## Features

- ESP32-based data acquisition using DHT22 sensor
- Send temperature and humidity data via HTTP POST to Flask server
- SQLite for simple and lightweight storage
- REST API endpoints for data access
- Chart.js front-end for real-time graph display

---

## Hardware Requirements

- NodeMCU-32S (ESP32 Dev Board)
- DHT22(or DHT11) sensor module
- Jumper wires
- Micro USB cable

---

## Software Requirements

- VSCode with PlatformIO IDE plugin(Version: 3.3.4)
- PlatformIO IDE library: DHT sensor library by Adafruit(Version: 1.4.6)
- Docker
---

## Project Structure

```
NodeMCU-32S-Iot-Web/
├── esp32/                  # Arduino code for ESP32 (PlatformIO compatible)
│   └── main.ino
├── server/                 # TBD: Flask web server and database
│   ├── app.py
│   ├── data.db             # (auto-generated)
│   ├── templates/
│   │   └── index.html
│   └── static/
│       └── script.js
├── README.md
└── platformio.ini
```

---

## Getting Started

### ESP32 (PlatformIO)
1. Open `esp32` folder with PlatformIO.
2. Modify `WiFiCredential.c` with your WiFi credentials and server IP.
3. Upload code to NodeMCU-32S via USB.
4. Use Serial Monitor to verify transmission.

### Flask Server
1. TBD

---

## API Endpoints
1. TBD

---

## To Be Done List:
### ESP-32
1. Seperate functions into libraries for better maintenance.
2. Use EEPROM for datastorage and recover.
3. Use watchdog for system monitoring.
4. Add recover mechaism when Wi-Fi failure or power lost.

### Flask
1. Dockerlized Flask server.
2. Implement frontend/backend.
3. Improve GUI.

---

## License

MIT License. Feel free to use and modify this project for your personal or academic purposes.
