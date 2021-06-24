//includes
#include <Arduino.h>
#include <Mooglesp_Led.h>
#include <Mooglesp_Pin.h>

//global constants
const uint8_t pin_led           = 25;
const uint8_t pin_potentiometer = 34;

//global objects
Mooglesp_Led led(pin_led);
Mooglesp_Pin potentiometer(pin_potentiometer, INPUT);

/**
 * initializes the current sketch
 */
void setup()
{
    //set the baud rate to 115200
    Serial.begin(115200);
}

/**
 * runs the main logic in an infinite loop
 */
void loop()
{
    //get data from potentiometer
    int value = potentiometer.analogRead();

    //convert the value from the potentiometer for use with the led
    int data = value >> 4;

    //print the data to the serial monitor
    Serial.printf("Raw input: %4d\n", value);
    Serial.printf("Led data:  %4d\n", data);
    Serial.printf("Electric potential: %2.2f volts\n\n", 3.3/4096 * value);

    //set the led brightness according to the data
    led.on(data);

    //wait a half second before next reading
    delay(500);
}
