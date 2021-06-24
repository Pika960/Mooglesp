# Mooglesp

Mooglesp (short for "Minimal object oriented gpio library (for) ESP32") is a
library for use with a ESP32 board and the Arduino IDE.

## Getting Started

These instructions will get you a copy of the project up and running on your
local machine for development and testing purposes.

### Prerequisites

* Arduino IDE (Version 1.8.10 or higher)
* ESP32 compatible board
* Git (only if you want to use it to install this library)

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

### Integration of the library with the Arduino IDE

There are several methods you can use to install this library. Each method has
its own advantages and disadvantages. Use "Method 1" if you do not like to use
a terminal or do not want to use Git. Use "Method 2" if you want to update the
library just with a "git pull" command or want to live on the edge by using
the master branch.

#### Method 1
1. Go to the [Releases page](https://github.com/Pika960/Mooglesp/releases)
2. Download the latest release from there
3. Extract/Unzip the zip file
4. Rename the folder to Mooglesp
5. In your Arduino IDE, go to Sketch->Include Library->Add .Zip Library and
select the extracted folder (or the zip file)
    - You can skip step 3 and 4 if you do not want to rename the folder

#### Method 2
1. In your Arduino IDE, go to File->Preferences->Sketchbook Location
2. Note this location and navigate with your terminal into this folder
3. Clone the repository into this folder
    - you can get the URL from the main project page
4. Restart your Arduino IDE
