//includes
#include "Mooglesp_Pin.h"

/**
 * initializes the class instance
 */
Mooglesp_Pin::Mooglesp_Pin(uint8_t pinNumber, uint8_t mode)
{
    //store variables in instance
    m_pinNumber = pinNumber;
    m_mode      = mode;
    m_value     = LOW;

    //check if pin number is greater then zero
    if (m_pinNumber < 0)
    {
        //if not, set pin number to zero
        m_pinNumber = 0;
    }

    //check if mode is valid
    if (!validateMode())
    {
        //if not, set mode to INPUT
        m_mode = INPUT;
    }

    //set the pin
    pinMode(m_pinNumber, m_mode);
}

/**
 * cleans up the class instance
 */
Mooglesp_Pin::~Mooglesp_Pin()
{
    //nothing to do here
}

/**
 * checks if the requested mode is valid
 * @return true if mode is valid, else false
 */
bool Mooglesp_Pin::validateMode()
{
    if (m_mode == INPUT        || m_mode == INPUT_PULLDOWN ||
        m_mode == INPUT_PULLUP || m_mode == OUTPUT)
    {
        return true;
    }

    return false;
}

/**
 * reads the value from the analog pin
 * @return the analog reading on the pin
 */
int Mooglesp_Pin::analogRead()
{
    if (m_mode == INPUT || m_mode == INPUT_PULLDOWN || m_mode == INPUT_PULLUP)
    {
        m_analogIO.setPinNumber(m_pinNumber);
        m_value = m_analogIO.analogRead();
        return m_value;
    }

    return -1;
}

/**
 * reads the value from the analog pin and smooths the data
 * @return the analog reading on the pin
 */
int Mooglesp_Pin::analogReadSmooth()
{
    if (m_mode == INPUT || m_mode == INPUT_PULLDOWN || m_mode == INPUT_PULLUP)
    {
        m_analogIO.setPinNumber(m_pinNumber);
        m_value = m_analogIO.analogReadSmooth();
        return m_value;
    }

    return -1;
}

/**
 * reads the value from the digital pin
 * @return the digital reading on the pin
 */
int Mooglesp_Pin::digitalRead()
{
    if (m_mode == INPUT || m_mode == INPUT_PULLDOWN || m_mode == INPUT_PULLUP)
    {
        m_value = ::digitalRead(m_pinNumber);
        return m_value;
    }

    return -1;
}

/**
 * gets the current mode of the pin
 * @return the current mode
 */
uint8_t Mooglesp_Pin::getMode()
{
    return m_mode;
}

/**
 * gets the current number of the pin
 * @return the current pin number
 */
uint8_t Mooglesp_Pin::getPinNumber()
{
    return m_pinNumber;
}

/**
 * gets the last data value of the pin
 * @return the last data value
 */
uint32_t Mooglesp_Pin::getValue()
{
    return m_value;
}

/**
 * writes an analog value to a pin
 * @param value the data which should be written
 */
void Mooglesp_Pin::analogWrite(int value)
{
    m_analogIO.setPinNumber(m_pinNumber);
    m_analogIO.analogWrite(value);
}

/**
 * writes a digital value to a pin
 * @param value the data which should be written
 */
void Mooglesp_Pin::digitalWrite(int value)
{
    if (m_mode == OUTPUT)
    {
        m_value = value;
        ::digitalWrite(m_pinNumber, m_value);
    }
}

/**
 * sets the mode to a new value
 * @param mode the new value of mode
 */
void Mooglesp_Pin::setMode(uint8_t mode)
{
    m_mode = mode;

    if (!validateMode())
    {
        m_mode = INPUT;
    }

    pinMode(m_pinNumber, m_mode);
}

/**
 * sets the pin number to a new value
 * @param pinNumber the new value of pin number
 */
void Mooglesp_Pin::setPinNumber(uint8_t pinNumber)
{
    m_pinNumber = pinNumber;
    pinMode(m_pinNumber, m_mode);
}
