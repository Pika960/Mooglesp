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

### Integration of the library in your project
Integrating the library is a very simple process. Just add the header file
of the hardware component you want to use. To learn more about what you can
do with this library in your project, either read the following section for
information about the available classes and their functions, or go through
the examples provided.

## An overview over the provided classes
If you want to use a third party library in your project, you always need to
know what it offers and what it can do for you. This section provides a brief
overview of what this library will do for you.

### AnalogIO - The analog input and output handler
AnalogIO handles analog read and write operations. It follows the singleton
design pattern, which means that there can only be one instance of this class.

### Button - Reads data from a button
Button is derived from the base class. It can manage buttons with either
a pull-up or a pull-down resistor.

### DHT - Measures temperature and humidity over a single wire
Derived from the base class, DHT manages the DHTx sensor family. These sensors
can measure temperature and humidity. Although they are slower than comparable
sensors, they have the advantage that they require relatively little power and
offer good long-term stability. These sensors are quite cheap to buy, but give
good results.

### LM75 - The I²C based temperature sensor
LM75 covers the LM75x sensor family. These sensors offer digital temperature
measurement and can work as a thermal watchdog. These sensors work via the
I²C protocol. For this reason, this class uses the TwoWire interface, which
is part of the ESP32 SDK.

### Led - Let's make some light
Led is derived from the base class. It enables you to control a single LED.
The class offers common functionalities to bring your LED to life.

### MHZ19 - Measures the concentration of carbon dioxide in the air
MHZ19 deals with the MHZ19x sensor family. These sensors can measure both
carbon dioxide concentration and temperature, but be aware that the measured
temperature is not very accurate. The MHZ19x works over a serial connection.
In contrast to the standard Arduino runtime, the ESP32 Arduino core does not
offer a SoftwareSerial class. Therefore, an external library is used by this
class. You can download EspSoftwareSerial either with the Arduino Library
Manager or by visiting [this](https://github.com/plerup/espsoftwareserial)
GitHub repository.

### Pin - The base class that can be anything
Pin is the base class of this library. It offers both analog and digital read
and write functions and can be freely used for most of the components that can
be used with the ESP32.

### RGBLed - Brings more color into your life
RGBLed consists of three Led instances that are combined into a single class.
Since the full RGB color space is available compared to a single LED, this
class offers significantly expanded functionality.

## A note on compatibility

This library was tested with the WEMOS LOLIN32 lite (ESP32) board and
therefore I can only guarantee that this library will work as intended
on this board. Technically, it should work absolutely fine on any board
compatible with the ESP32 architecture.

Have fun developing, kupo.
