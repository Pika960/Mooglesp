//includes
#include <Arduino.h>
#include <Mooglesp_LM75.h>

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

    //wait one second before using the serial monitor in the setup function
    delay(1000);

    //initialize the I2C bus connection
    bool status = lm75.begin(pin_sda, pin_scl, 400000);

    //validate if connection is successfully established
    if (!status)
    {
        //if not, print an error message and terminate the program here
        Serial.println("Could not find a valid LM75 sensor, check wiring!");
        while (1);
    }

    //store the default configuration
    float hysteresis      = lm75.getHysteresis();
    float overTemperature = lm75.getOverTemperature();

    //print the default configuration to the serial monitor
    Serial.println("Default configuration:");
    Serial.printf("Hysteresis:       %.3f°c\n",   lm75.getHysteresis());
    Serial.printf("Over-Temperature: %.3f°c\n\n", lm75.getOverTemperature());

    //increase the register by 5 degrees
    lm75.setHysteresis(hysteresis + 5);
    lm75.setOverTemperature(overTemperature + 5);

    //get the new data from the sensor and print it to the serial monitor
    Serial.println("Updated configuration:");
    Serial.printf("Hysteresis:       %.3f°c\n",   lm75.getHysteresis());
    Serial.printf("Over-Temperature: %.3f°c\n\n", lm75.getOverTemperature());

    //reset the configuration back to the defaults
    lm75.setHysteresis(hysteresis);
    lm75.setOverTemperature(overTemperature);

    //print the default configuration to the serial monitor
    Serial.println("Configuration reset:");
    Serial.printf("Hysteresis:       %.3f°c\n",   lm75.getHysteresis());
    Serial.printf("Over-Temperature: %.3f°c\n\n", lm75.getOverTemperature());
}

void loop()
{
    //nothing to do here
}
