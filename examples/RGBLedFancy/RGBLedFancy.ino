//includes
#include <Arduino.h>
#include <Mooglesp_RGBLed.h>

//global constants
const uint8_t blinks        =  5;
const uint8_t pin_led_red   = 25;
const uint8_t pin_led_green = 26;
const uint8_t pin_led_blue  = 27;

//global objects
Mooglesp_RGBLed rgbled(pin_led_red, pin_led_green, pin_led_blue);

//global variables
uint8_t nextState;

//prototypes
void turnOff(uint32_t delay);

/**
 * initializes the current sketch
 */
void setup()
{
    //set the baud rate to 115200
    Serial.begin(115200);

    //wait 1 second before starting
    delay(1000);
}

/**
 * runs the main logic in an infinite loop
 */
void loop()
{
    //generate a random state
    nextState = random(0, 7);

    //let the led blink according to nextState
    switch (nextState)
    {
        case 0:
        {
            Serial.printf("RGBLed will blink %d times in red\n", blinks);
            rgbled.blink(blinks, 500, MOOGLESP_RGBLED_COLOR_RED);
            Serial.printf("RGBLed blinked %d times in red\n", blinks);
        } break;

        case 1:
        {
            Serial.printf("RGBLed will blink %d times in green\n", blinks);
            rgbled.blink(blinks, 500, MOOGLESP_RGBLED_COLOR_GREEN);
            Serial.printf("RGBLed blinked %d times in green\n", blinks);
        } break;

        case 2:
        {
            Serial.printf("RGBLed will blink %d times in blue\n", blinks);
            rgbled.blink(blinks, 500, MOOGLESP_RGBLED_COLOR_BLUE);
            Serial.printf("RGBLed blinked %d times in blue\n", blinks);
        } break;

        case 3:
        {
            Serial.printf("RGBLed will blink %d times in cyan\n", blinks);
            rgbled.blink(blinks, 500, MOOGLESP_RGBLED_COLOR_CYAN);
            Serial.printf("RGBLed blinked %d times in cyan\n", blinks);
        } break;

        case 4:
        {
            Serial.printf("RGBLed will blink %d times in magenta\n", blinks);
            rgbled.blink(blinks, 500, MOOGLESP_RGBLED_COLOR_MAGENTA);
            Serial.printf("RGBLed blinked %d times in magenta\n", blinks);
        } break;

        case 5:
        {
            Serial.printf("RGBLed will blink %d times in yellow\n", blinks);
            rgbled.blink(blinks, 500, MOOGLESP_RGBLED_COLOR_YELLOW);
            Serial.printf("RGBLed blinked %d times in yellow\n", blinks);
        } break;

        default:
        {
            Serial.printf("RGBLed will blink %d times in white\n", blinks);
            rgbled.blink(blinks, 500, MOOGLESP_RGBLED_COLOR_WHITE);
            Serial.printf("RGBLed blinked %d times in white\n", blinks);
        } break;
    }

    //turn rgbled off for a second
    turnOff(1000);

    //fade rgbled in rainbow colors
    Serial.println("Take a moment and look at all those colors");
    rgbled.rainbow(150);

    //turn rgbled off for a second
    turnOff(1000);

    //create a random color
    uint8_t red   = random(0, 256);
    uint8_t green = random(0, 256);
    uint8_t blue  = random(0, 256);

    Serial.printf("The random color this time is %d, %d, %d (r,g,b)\n",
        red, green, blue);
    rgbled.setColor(red, green, blue);
    delay(2000);

    //turn rgbled off for a second
    turnOff(1000);
}

void turnOff(uint32_t delay)
{
    rgbled.clear();
    Serial.printf("RGBLed is now off for %.2f second(s)\n", delay / 1000.0f);
    ::delay(delay);
}
