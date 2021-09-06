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

//prototypes
void doTask(uint8_t color, uint8_t task);
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
    //turn the led with a random color on
    doTask(random(0, 7), 0);

    //fade to a random color
    doTask(random(0, 7), 1);

    //blink in a random color
    doTask(random(0, 7), 2);

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

/**
 * performs an action
 * @param color the color value of the led
 * @param task the task to be done
 */
void doTask(uint8_t color, uint8_t task)
{
    char     colorName[8] = "";
    uint32_t colorCode    = 0;

    switch (color)
    {
        case 0:
        {
            colorCode = MOOGLESP_RGBLED_COLOR_RED;
            strcpy(colorName, "red");
        } break;

        case 1:
        {
            colorCode = MOOGLESP_RGBLED_COLOR_GREEN;
            strcpy(colorName, "green");
        } break;

        case 2:
        {
            colorCode = MOOGLESP_RGBLED_COLOR_BLUE;
            strcpy(colorName, "blue");
        } break;

        case 3:
        {
            colorCode = MOOGLESP_RGBLED_COLOR_CYAN;
            strcpy(colorName, "cyan");
        } break;

        case 4:
        {
            colorCode = MOOGLESP_RGBLED_COLOR_MAGENTA;
            strcpy(colorName, "magenta");
        } break;

        case 5:
        {
            colorCode = MOOGLESP_RGBLED_COLOR_YELLOW;
            strcpy(colorName, "yellow");
        } break;

        default:
        {
            colorCode = MOOGLESP_RGBLED_COLOR_WHITE;
            strcpy(colorName, "white");
        } break;
    }

    switch (task)
    {
        case 0:
        {
            Serial.printf("RGBLed turned on with color %s\n", colorName);
            rgbled.setColor(colorCode);
            delay(1000);
        } break;

        case 1:
        {
            Serial.printf("RGBLed will now fade to color %s\n", colorName);
            rgbled.fade(20, colorCode);
            delay(1000);
        } break;

        case 2:
        {
            Serial.printf("RGBLed will blink %d times in %s\n", blinks, colorName);
            rgbled.blink(blinks, 500, colorCode);
            Serial.printf("RGBLed blinked %d times in %s\n", blinks, colorName);
        } break;
    }
}

/**
 * turns the led off
 * @param delay the timeframe to wait after the operation
 */
void turnOff(uint32_t delay)
{
    rgbled.clear();
    Serial.printf("RGBLed is now off for %.2f second(s)\n", delay / 1000.0f);
    ::delay(delay);
}
