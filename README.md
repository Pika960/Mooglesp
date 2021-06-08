# Mooglesp

Mooglesp (short for "Minimal object oriented gpio library (for) ESP32") is a
library for use with a ESP32 board and the Arduino IDE.

## Getting Started

These instructions will get you a copy of the project up and running on your
local machine for development and testing purposes.

### Prerequisites

* Arduino IDE (Version 1.8.10 or higher)
* ESP32 compatible board

### Integration of the ESP32 with the Arduino IDE
1. In your Arduino IDE, go to File->Preferences
2. Enter "https://dl.espressif.com/dl/package_esp32_index.json" into the
"Additional Board Manager URLs" field and click the "OK" button
    - if you already have a URL there, you can separate them with a comma
3. Open the Boards Manager. Go to Tools->Board->Boards Manager
4. Search for "ESP32", select the entry "ESP32 by Espressif Systems",
select a version and press the "Install" button
5. Select your Board in Tools->Board and configure your Port
6. Now you should be ready to flash software to your board
