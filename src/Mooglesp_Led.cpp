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
 */
void Mooglesp_Led::blink(uint32_t cycles, uint32_t delay)
{
    for (int i = 0; i < cycles; i++)
    {
        on();
        ::delay(delay);
        off();
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
    if (start < end)
    {
        for (uint i = start; i <= end; ++i)
        {
            analogWrite(i);
            ::delay(delay);
        }
    }

    else
    {
        for (uint i = start; i+1 > end; --i)
        {
            analogWrite(i);
            ::delay(delay);
        }
    }
}

/**
 * turns the led off
 */
void Mooglesp_Led::off()
{
    m_value = LOW;
    digitalWrite(m_value);
}

/**
 * turns the led on
 */
void Mooglesp_Led::on()
{
    m_value = HIGH;
    digitalWrite(m_value);
}