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
byte Mooglesp_RGBLed::getColorBlue()
{
    return m_colorBlue;
}

/**
 * gets the current green color value
 * @return current color value of the green led
 */
byte Mooglesp_RGBLed::getColorGreen()
{
    return m_colorGreen;
}

/**
 * gets the current red color value
 * @return current color value of the red led
 */
byte Mooglesp_RGBLed::getColorRed()
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
    writeColor(m_colorRed, m_colorGreen, m_colorBlue);
}

/**
 * fades the led in rainbow colors
 * @param delay the timeframe between any operation
 */
void Mooglesp_RGBLed::rainbow(uint32_t delay)
{
    for (uint8_t i = 0; i <= 255; i++)
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
    }
}

/**
 * sets the color of the led according to red, green and blue value
 * @param red color value of the red led
 * @param green color value of the green led
 * @param blue color value of the blue led
 */
void Mooglesp_RGBLed::setColor(byte red, byte green, byte blue)
{
    m_color = (uint8_t(red) << 16) | (uint8_t(green) << 8) | uint8_t(blue);
    m_colorBlue  = blue;
    m_colorGreen = green;
    m_colorRed   = red;

    writeColor(m_colorRed, m_colorGreen, m_colorBlue);
}

/**
 * sets the color of the led according to an rgb value
 * @param color color value of the led
 */
void Mooglesp_RGBLed::setColor(uint32_t color)
{
    m_color      = color;
    m_colorBlue  = color & 0xff;
    m_colorGreen = (color >>  8) & 0xff;
    m_colorRed   = (color >> 16) & 0xff;

    writeColor(m_colorRed, m_colorGreen, m_colorBlue);
}

/**
 * writes a color value to all leds
 * @param red color value of the red led
 * @param green color value of the green led
 * @param blue color value of the blue led
 */
void Mooglesp_RGBLed::writeColor(byte red, byte green, byte blue)
{
    m_ledRed.analogWrite(red);
    m_ledGreen.analogWrite(green);
    m_ledBlue.analogWrite(blue);
}
