# 🎮 MinecraftESP32

<div align="center">

![Minecraft + ESP32](https://img.shields.io/badge/Minecraft-ESP32-brightgreen)
![Python](https://img.shields.io/badge/Python-3.6+-blue)
![Arduino](https://img.shields.io/badge/Arduino-IDE-00979D)

A project that bridges the virtual world of Minecraft with physical reality using an ESP32 microcontroller.

</div>

## 📝 Description

This project demonstrates how to create an interactive bridge between the physical world and Minecraft using Python and an ESP32 microcontroller. It provides examples of how to manipulate the Minecraft world based on real-world inputs, like RFID cards.

## ⚙️ Requirements

### Hardware
- ESP32 Development Board
- RFID-RC522 Module
- RFID Cards/Tags
- LED
- Buzzer
- Jumper Wires
- Breadboard

## 📋 Software Requirements

- [Python 3.6+](https://www.python.org/downloads/)
- [Minecraft Java Edition](https://www.minecraft.net/en-us/store/minecraft-deluxe-collection-pc)
- [Minecraft Python API (mcpi)](https://github.com/martinohanlon/mcpi)
- [Minecraft Server](https://medium.com/@rodrigoka4/programando-em-python-e-transformando-o-mundo-de-minecraft-a-sua-maneira-3d94a275faec)
- [Arduino IDE](https://www.arduino.cc/en/software)
- Required Arduino Libraries:
  - [WiFi](https://docs.arduino.cc/libraries/wifi/)
  - [WebServer](https://github.com/esp8266/Arduino/tree/master/libraries/WebServer)
  - [SPI](https://www.arduino.cc/en/reference/SPI)
  - [MFRC522](https://github.com/miguelbalboa/rfid)

## 🔧 Setup and Installation

1. **Hardware Setup**
   - Connect the RFID-RC522 to ESP32:
     - RST -> GPIO22
     - SDA(SS) -> GPIO21
     - MOSI -> GPIO23
     - MISO -> GPIO19
     - SCK -> GPIO18
   - Connect LED to GPIO2
   - Connect Buzzer to GPIO13

2. **ESP32 Configuration**
   - Open `esp32.ino` in Arduino IDE
   - Update WiFi credentials:
     ```cpp
     const char* ssid = "YOUR_WIFI_SSID";
     const char* password = "YOUR_WIFI_PASSWORD";
     ```
   - Upload the code to ESP32

3. **Minecraft Setup**
   - Update `MinecraftESP32Comm.py` with your ESP32's IP address:
     ```python
     esp32_ip = "YOUR_ESP32_IP_ADDRESS"
     ```
   - Run the Python script while Minecraft is running

## 🎮 Usage

To test the project, you can use the following examples:

1. **LED Control**
   - Place a lever in Minecraft and update the coordinates in the Python script
   - Toggle the lever to control the physical LED

2. **RFID Door Control**
   - The first RFID card presented will be registered as the authorized card
   - Present the registered card to open the Minecraft door at the coordinates you set in the Python script
   - Door automatically closes after 3 seconds

## 🔊 Audio Feedback

- **Registration**: Long beep
- **Access Granted**: Single beep
- **Access Denied**: Double beep

### 🔗 Useful Links
- [Minecraft Block IDs Reference](https://www.minecraftinfo.com/idlist.htm)
- [Java Version Compatibility Fix](https://stackoverflow.com/questions/47112412/unrecognized-vm-option-maxpermsize-512m-when-running-zeppelin)
- [Minecraft Python API Documentation](https://www.stuffaboutcode.com/p/minecraft-api-reference.html)

## 🤝 Contributing

Contributions are welcome! Feel free to:
- Add new features
- Improve documentation
- Fix bugs
- Share your creative ideas

## 🙏 Acknowledgments

- Minecraft Python API developers
- ESP32 and RFID-RC522 library maintainers
- The Minecraft modding community

---

<div align="center">
Made with ❤️ for Minecraft and IoT enthusiasts
</div>
