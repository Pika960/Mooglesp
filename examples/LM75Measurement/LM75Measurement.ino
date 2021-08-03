//includes
#include <Arduino.h>
#include "Mooglesp_LM75.h"

//global constants
const uint8_t addr_lm75 = 0x48;
const uint8_t pin_sda   = 19;
const uint8_t pin_scl   = 23;

//global objects
Mooglesp_LM75 lm75(addr_lm75);

/**
 * initializes the current sketch
 */
void setup()
{
    //set the baud rate to 115200
    Serial.begin(115200);

    //initialize the I2C bus connection
    bool status = lm75.begin(pin_sda, pin_scl, 400000);

    //validate if connection is successfully established
    if (!status)
    {
        //if not, print an error message and terminate the program here
        Serial.println("Could not find a valid LM75 sensor, check wiring!");
        while (1);
    }
}

void loop()
{
    //print the data and print it to the serial monitor
    Serial.printf("Temperature:      %.3f°c\n",   lm75.getTemperature());
    Serial.printf("Hysteresis:       %.3f°c\n",   lm75.getHysteresis());
    Serial.printf("Over-Temperature: %.3f°c\n\n", lm75.getOverTemperature());

    //wait one seconds before reading again from sensor
    delay(1000);
}
