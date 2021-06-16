//includes
#include "Mooglesp_Led.h"

/**
 * initializes the class instance
 */
Mooglesp_Led::Mooglesp_Led(uint8_t pinNumber) :
    Mooglesp_Pin(pinNumber, OUTPUT)
{
    //nothing to do here
}

/**
 * cleans up the class instance
 */
Mooglesp_Led::~Mooglesp_Led()
{
    //nothing to do here
}

/**
 * gets the current state of the led
 * @return true if led is on, else false
 */
bool Mooglesp_Led::state()
{
    return m_value > 0 ? true : false;
}

/**
 * lets the led turn on and off (blink) a set number of times
 * @param cycles the number of times the led should blink
 * @param delay the timeframe between on and off
 * @param brightness the brightness value of the led (defaults to 255)
 */
void Mooglesp_Led::blink(uint32_t cycles, uint32_t delay, uint8_t brightness)
{
    for (uint32_t i = 0; i < (cycles * 2); i++)
    {
        if (!state())
        {
            on(brightness);
        }

        else
        {
            off();
        }

        ::delay(delay);
    }
}

/**
 * lets the led fade within an interval
 * @param start the value you want to start with
 * @param end the value you want to end with
 * @param delay the timeframe between any operation
 */
void Mooglesp_Led::fade(uint8_t start, uint8_t end, uint32_t delay)
{
    uint8_t i = start;

    if (start < end)
    {
        do
        {
            analogWrite(i);
            ::delay(delay);
        } while (i++ != 255);
    }

    else
    {
        do
        {
            analogWrite(i);
            ::delay(delay);
        } while (i--);
    }
}

/**
 * turns the led off
 */
void Mooglesp_Led::off()
{
    analogWrite(0);
}

/**
 * turns the led on
 * @param brightness the brightness value of the led (defaults to 255)
 */
void Mooglesp_Led::on(uint8_t brightness)
{
    analogWrite(brightness);
}
