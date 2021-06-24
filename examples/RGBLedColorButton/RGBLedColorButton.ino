//includes
#include <Arduino.h>
#include <Mooglesp_Button.h>
#include <Mooglesp_RGBLed.h>

//global constants
const uint8_t pin_led_red   = 25;
const uint8_t pin_led_green = 26;
const uint8_t pin_led_blue  = 27;
const uint8_t pin_button    =  5;

//global objects
Mooglesp_Button button(pin_button);
Mooglesp_RGBLed rgbled(pin_led_red, pin_led_green, pin_led_blue);

//global variables
uint8_t nextState;

/**
 * initializes the current sketch
 */
void setup()
{
    //set the baud rate to 115200
    Serial.begin(115200);

    //set nextState to zero
    nextState = 0;
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
        //cycle from one color to next one
        switch (nextState)
        {
            case 0:
            {
                nextState = 1;
                rgbled.setColor(MOOGLESP_RGBLED_COLOR_RED);
                Serial.println("Color is now red");
            } break;

            case 1:
            {
                nextState = 2;
                rgbled.setColor(MOOGLESP_RGBLED_COLOR_GREEN);
                Serial.println("Color is now green");
            } break;

            case 2:
            {
                nextState = 3;
                rgbled.setColor(MOOGLESP_RGBLED_COLOR_BLUE);
                Serial.println("Color is now blue");
            } break;

            case 3:
            {
                nextState = 4;
                rgbled.setColor(MOOGLESP_RGBLED_COLOR_CYAN);
                Serial.println("Color is now cyan");
            } break;

            case 4:
            {
                nextState = 5;
                rgbled.setColor(MOOGLESP_RGBLED_COLOR_MAGENTA);
                Serial.println("Color is now magenta");
            } break;

            case 5:
            {
                nextState = 6;
                rgbled.setColor(MOOGLESP_RGBLED_COLOR_YELLOW);
                Serial.println("Color is now yellow");
            } break;

            case 6:
            {
                nextState = 7;
                rgbled.setColor(MOOGLESP_RGBLED_COLOR_WHITE);
                Serial.println("Color is now white");
            } break;

            default:
            {
                nextState = 0;
                rgbled.setColor(MOOGLESP_RGBLED_COLOR_BLACK);
                Serial.println("Color is now black");
            } break;
        }
    }
}
