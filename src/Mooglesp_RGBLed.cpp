//includes
#include "Mooglesp_RGBLed.h"

/**
 * initializes the class instance
 */
Mooglesp_RGBLed::Mooglesp_RGBLed(uint8_t pinRed, uint8_t pinGreen,
    uint8_t pinBlue) : m_ledRed(pinRed), m_ledGreen(pinGreen),
    m_ledBlue(pinBlue), m_colorRed(255), m_colorGreen(255), m_colorBlue(255)
{
    m_color = 0;
}

/**
 * cleans up the class instance
 */
Mooglesp_RGBLed::~Mooglesp_RGBLed()
{
    //nothing to do here
}

/**
 * gets the current state of the led
 * @return true if an led is on, else false
 */
bool Mooglesp_RGBLed::state()
{
    if (m_ledBlue.state() || m_ledGreen.state() || m_ledRed.state())
    {
        return true;
    }

    return false;
}

/**
 * gets the current blue color value
 * @return current color value of the blue led
 */
uint8_t Mooglesp_RGBLed::getColorBlue()
{
    return m_colorBlue;
}

/**
 * gets the current green color value
 * @return current color value of the green led
 */
uint8_t Mooglesp_RGBLed::getColorGreen()
{
    return m_colorGreen;
}

/**
 * gets the current red color value
 * @return current color value of the red led
 */
uint8_t Mooglesp_RGBLed::getColorRed()
{
    return m_colorRed;
}

/**
 * gets the current color value
 * @return current color value of all leds
 */
uint32_t Mooglesp_RGBLed::getColor()
{
    return m_color;
}

/**
 * lets the led turn on and off (blink) a set number of times
 * @param cycles the number of times the led should blink
 * @param delay the timeframe between on and off
 * @param red color value of the red led
 * @param green color value of the green led
 * @param blue color value of the blue led
 */
void Mooglesp_RGBLed::blink(uint32_t cycles, uint32_t delay,
    uint8_t red, uint8_t green, uint8_t blue)
{
    setColor(red, green, blue, false);

    for (uint32_t i = 0; i < (cycles * 2); i++)
    {
        if (!state())
        {
            on();
        }

        else
        {
            off();
        }

        ::delay(delay);
    }
}

/**
 * lets the led turn on and off (blink) a set number of times
 * @param cycles the number of times the led should blink
 * @param delay the timeframe between on and off
 * @param color color value of the led (defaults to white)
 */
void Mooglesp_RGBLed::blink(uint32_t cycles, uint32_t delay, uint32_t color)
{
    setColor(color, false);

    for (uint32_t i = 0; i < (cycles * 2); i++)
    {
        if (!state())
        {
            on();
        }

        else
        {
            off();
        }

        ::delay(delay);
    }
}

/**
 * clears all color values and writes it to the led
 */
void Mooglesp_RGBLed::clear()
{
    m_color      = 0;
    m_colorBlue  = 0;
    m_colorGreen = 0;
    m_colorRed   = 0;

    writeColor(m_colorRed, m_colorGreen, m_colorBlue);
}

/**
 * fades the led from the current color to a new one
 * @param delay the timeframe between any operation
 * @param red color value of the red led
 * @param green color value of the green led
 * @param blue color value of the blue led
 */
void Mooglesp_RGBLed::fade(uint32_t delay, uint8_t red, uint8_t green,
    uint8_t blue)
{
    uint8_t backup_red   = m_colorRed;
    uint8_t backup_green = m_colorGreen;
    uint8_t backup_blue  = m_colorBlue;

    setColor(red, green, blue, false);

    int16_t diff_red   = (int16_t)m_colorRed   - (int16_t)backup_red;
    int16_t diff_green = (int16_t)m_colorGreen - (int16_t)backup_green;
    int16_t diff_blue  = (int16_t)m_colorBlue  - (int16_t)backup_blue;

    uint8_t i = 0;

    do
    {
        uint8_t r = backup_red   + i * diff_red   / 256;
        uint8_t g = backup_green + i * diff_green / 256;
        uint8_t b = backup_blue  + i * diff_blue  / 256;

        writeColor(r, g, b);
        ::delay(delay);
    } while (i++ != 255);

    writeColor(m_colorRed, m_colorGreen, m_colorBlue);
}

/**
 * fades the led from the current color to a new one
 * @param delay the timeframe between any operation
 * @param color color value of the led
 */
void Mooglesp_RGBLed::fade(uint32_t delay, uint32_t color)
{
    uint8_t backup_red   = m_colorRed;
    uint8_t backup_green = m_colorGreen;
    uint8_t backup_blue  = m_colorBlue;

    setColor(color, false);

    int16_t diff_red   = (int16_t)m_colorRed   - (int16_t)backup_red;
    int16_t diff_green = (int16_t)m_colorGreen - (int16_t)backup_green;
    int16_t diff_blue  = (int16_t)m_colorBlue  - (int16_t)backup_blue;

    uint8_t i = 0;

    do
    {
        uint8_t r = backup_red   + i * diff_red   / 256;
        uint8_t g = backup_green + i * diff_green / 256;
        uint8_t b = backup_blue  + i * diff_blue  / 256;

        writeColor(r, g, b);
        ::delay(delay);
    } while (i++ != 255);

    writeColor(m_colorRed, m_colorGreen, m_colorBlue);
}

/**
 * turns the led off
 */
void Mooglesp_RGBLed::off()
{
    writeColor(0, 0, 0);
}

/**
 * turns the led on
 */
void Mooglesp_RGBLed::on()
{
    if (m_colorRed == 0 && m_colorGreen == 0 && m_colorBlue == 0)
    {
        writeColor(255, 255, 255);
    }

    else
    {
        writeColor(m_colorRed, m_colorGreen, m_colorBlue);
    }
}

/**
 * fades the led in rainbow colors
 * @param delay the timeframe between any operation
 */
void Mooglesp_RGBLed::rainbow(uint32_t delay)
{
    uint8_t i = 0;

    do
    {
        uint8_t position = 255 - i;

        if (position < 85)
        {
            setColor(255 - position * 3, 0, position * 3);
        }

        else if (position < 170)
        {
            position -= 85;
            setColor(0, position * 3, 255 - position * 3);
        }

        else
        {
            position -= 170;
            setColor(position * 3, 255 - position * 3, 0);
        }

        ::delay(delay);
    } while (i++ != 255);
}

/**
 * sets the color of the led according to red, green and blue value
 * @param red color value of the red led
 * @param green color value of the green led
 * @param blue color value of the blue led
 * @param write if set the color will be written to the led (defaults to true)
 */
void Mooglesp_RGBLed::setColor(uint8_t red, uint8_t green, uint8_t blue,
    bool write)
{
    m_color = (uint8_t(red) << 16) | (uint8_t(green) << 8) | uint8_t(blue);
    m_colorBlue  = blue;
    m_colorGreen = green;
    m_colorRed   = red;

    if (write)
    {
        writeColor(m_colorRed, m_colorGreen, m_colorBlue);
    }
}

/**
 * sets the color of the led according to an rgb value
 * @param color color value of the led
 * @param write if set the color will be written to the led (defaults to true)
 */
void Mooglesp_RGBLed::setColor(uint32_t color, bool write)
{
    m_color      = color;
    m_colorBlue  = color & 0xff;
    m_colorGreen = (color >>  8) & 0xff;
    m_colorRed   = (color >> 16) & 0xff;

    if (write)
    {
        writeColor(m_colorRed, m_colorGreen, m_colorBlue);
    }
}

/**
 * writes a color value to all leds
 * @param red color value of the red led
 * @param green color value of the green led
 * @param blue color value of the blue led
 */
void Mooglesp_RGBLed::writeColor(uint8_t red, uint8_t green, uint8_t blue)
{
    m_ledRed.analogWrite(red);
    m_ledGreen.analogWrite(green);
    m_ledBlue.analogWrite(blue);
}
