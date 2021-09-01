#include <Mooglesp_MHZ19.h>

//global constants
const uint8_t pin_rx = 16; //connect this one to the tx pin of the sensor
const uint8_t pin_tx = 17; //connect this one to the rx pin of the sensor

//global objects
Mooglesp_MHZ19 mhz19(pin_rx, pin_tx);

/**
 * initializes the current sketch
 */
void setup()
{
    //set the baud rate to 115200
    Serial.begin(115200);

    //configure auto calibration of the sensor
    mhz19.configureAutoCalibration(true);

    //wait one second before using the serial monitor in the setup function
    delay(1000);

    //check if sensor is ready
    while (mhz19.isWarmingUp())
    {
        Serial.print("MH-Z19 is currently warming up. Please wait.\n");
        delay(1000);
    }

    //print an empty line
    Serial.print("\n");

    //get the current sensor configuration
    bool abc         = mhz19.getAutoCalibrationStatus();
    char firmware[5] = "";

    mhz19.getFirmwareVersion(firmware);

    //print the data to the serial monitor
    Serial.println("Current sensor configuration:");
    Serial.printf("Auto-Calibration: %s\n", (abc ? "enabled" : "disabled"));
    Serial.printf("Firmware-Version: %s\n\n", firmware);
}

/**
 * runs the main logic in an infinite loop
 */
void loop()
{
    //get the current data and print it to the serial monitor
    Serial.printf("Temperature:    %4d°c\n",  mhz19.getTemperature());
    Serial.printf("Carbon dioxide: %4dppm\n", mhz19.getCO2());

    //wait one second before reading again from sensor
    delay(1000);
}
