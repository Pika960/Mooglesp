//includes
#include "Mooglesp_LM75.h"

/**
 * initializes the class instance
 */
Mooglesp_LM75::Mooglesp_LM75(uint8_t address, uint8_t busNumber) :
    m_wire(busNumber)
{
    //store variables in instance
    m_address      = address;
    m_registerData = 0xFFFF;
}

/**
 * cleans up the class instance
 */
Mooglesp_LM75::~Mooglesp_LM75()
{
    //nothing to do here
}

/**
 * initializes the I2C bus connection
 * @return true if init was successful, false if not
 */
bool Mooglesp_LM75::begin(uint8_t sda, uint8_t scl, uint32_t frequency)
{
    return m_wire.begin(sda, scl, frequency);
}

/**
 * gets the current hysteresis
 * @param fahrenheit if set to true temperature will be in fahrenheit
 * @return the current hysteresis
 */
float Mooglesp_LM75::getHysteresis(bool fahrenheit)
{
    //refresh data
    readRegister(MOOGLESP_LM75_REGISTER_THYST);

    //calculate hysteresis
    float hysteresis = m_registerData / 256.0F;

    //convert hysteresis to fahrenheit if flag is set to true
    if (fahrenheit)
    {
        return (hysteresis * 1.8) + 32;
    }

    return hysteresis;
}

/**
 * gets the current over-temperature output
 * @param fahrenheit if set to true temperature will be in fahrenheit
 * @return the current over-temperature output
 */
float Mooglesp_LM75::getOverTemperature(bool fahrenheit)
{
    //refresh data
    readRegister(MOOGLESP_LM75_REGISTER_TOS);

    //calculate over-temperature output
    float os = m_registerData / 256.0F;

    //convert over-temperature output to fahrenheit if flag is set to true
    if (fahrenheit)
    {
        return (os * 1.8) + 32;
    }

    return os;
}

/**
 * gets the current temperature
 * @param fahrenheit if set to true temperature will be in fahrenheit
 * @return the current temperature
 */
float Mooglesp_LM75::getTemperature(bool fahrenheit)
{
    //refresh data
    readRegister(MOOGLESP_LM75_REGISTER_TEMPERATURE);

    //calculate temperature
    float temperature = m_registerData / 256.0F;

    //convert temperature to fahrenheit if flag is set to true
    if (fahrenheit)
    {
        return (temperature * 1.8) + 32;
    }

    return temperature;
}

/**
 * reads the data from a data register
 * @param address the address of the register
 */
void Mooglesp_LM75::readRegister(uint8_t address)
{
    m_wire.beginTransmission(m_address);
    m_wire.write(address);
    m_wire.endTransmission();
    m_wire.requestFrom(m_address, uint8_t(2));

    if (m_wire.available())
    {
        uint8_t result = m_wire.read();
        m_registerData = result;

        if (address != MOOGLESP_LM75_REGISTER_CONFIGURATION)
        {
            m_registerData = (unsigned(result)) << 8;

            if (m_wire.available())
            {
                result          = m_wire.read();
                m_registerData |= (unsigned(result));
            }
        }
    }
}
