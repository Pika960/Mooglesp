//includes
#include <Arduino.h>
#include <Mooglesp_Button.h>
#include <Mooglesp_Led.h>

//global constants
const uint8_t pin_led    = 25;
const uint8_t pin_button =  5;

//global objects
Mooglesp_Button button(pin_button);
Mooglesp_Led    led(pin_led);

//global variables
bool state;

/**
 * initializes the current sketch
 */
void setup()
{
    //set the baud rate to 115200
    Serial.begin(115200);

    //get the current state of the led
    state = led.state();
}

/**
 * runs the main logic in an infinite loop
 */
void loop()
{
    //read data from button
    button.read();

    //check if button was released
    if (button.wasReleased())
    {
        //switch led from on to off
        if (state)
        {
            led.off();
            Serial.println("Led is now off");
        }

        //switch led from off to on
        else
        {
            led.on();
            Serial.println("Led is now on");
        }

        //invert the current state
        state = !state;
    }
}
