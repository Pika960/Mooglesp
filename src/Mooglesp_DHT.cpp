//includes
#include "Mooglesp_DHT.h"

/**
 * initializes the class instance
 */
Mooglesp_DHT::Mooglesp_DHT(uint8_t pinNumber, uint8_t type) :
    Mooglesp_Pin(pinNumber, INPUT)
{
    //store variables in instance
    m_humidity    = MOOGLESP_DHT_DATA_INVALID;
    m_lastTime    = 0;
    m_temperature = MOOGLESP_DHT_DATA_INVALID;
    m_type        = type;

    //check if device type is valid
    if (!validateType())
    {
        //if not, set type to DHT11
        m_type = MOOGLESP_DHT_TYPE_DHT11;
    }
}

/**
 * cleans up the class instance
 */
Mooglesp_DHT::~Mooglesp_DHT()
{
    //nothing to do here
}

/**
 * checks if the requested type is valid
 * @return true if type is valid, else false
 */
bool Mooglesp_DHT::validateType()
{
    if (m_type == MOOGLESP_DHT_TYPE_DHT11 ||
        m_type == MOOGLESP_DHT_TYPE_DHT12 ||
        m_type == MOOGLESP_DHT_TYPE_DHT21 ||
        m_type == MOOGLESP_DHT_TYPE_DHT22)
    {
        return true;
    }

    return false;
}

/**
 * gets the current humidity
 * @return the current humidity
 */
float Mooglesp_DHT::getHumidity()
{
    //refresh data
    measurement();

    //process raw data according to device type
    switch (m_type)
    {
        case MOOGLESP_DHT_TYPE_DHT11:
        case MOOGLESP_DHT_TYPE_DHT12:
        {
            m_humidity = m_data[0] + m_data[1] * 0.1;
        } break;

        case MOOGLESP_DHT_TYPE_DHT21:
        case MOOGLESP_DHT_TYPE_DHT22:
        {
            m_humidity = ((word)m_data[0]) << 8 | m_data[1];
            m_humidity *= 0.1;
        } break;
    }

    return m_humidity;
}

/**
 * gets the current temperature
 * @param fahrenheit if set to true temperature will be in fahrenheit
 * @return the current temperature
 */
float Mooglesp_DHT::getTemperature(bool fahrenheit)
{
    //refresh data
    measurement();

    //process raw data according to device type
    switch (m_type)
    {
        case MOOGLESP_DHT_TYPE_DHT11:
        {
            m_temperature = m_data[2];

            if (m_data[3] & 0x80)
            {
                m_temperature = -1 - m_temperature;
            }

            m_temperature += (m_data[3] & 0x0f) * 0.1;
        } break;

        case MOOGLESP_DHT_TYPE_DHT12:
        {
            m_temperature = m_data[2];
            m_temperature += (m_data[3] & 0x0f) * 0.1;

            if (m_data[2] & 0x80)
            {
                m_temperature *= -1;
            }
        } break;

        case MOOGLESP_DHT_TYPE_DHT21:
        case MOOGLESP_DHT_TYPE_DHT22:
        {
            m_temperature = ((word)(m_data[2] & 0x7F)) << 8 | m_data[3];
            m_temperature *= 0.1;

            if (m_data[2] & 0x80)
            {
                m_temperature *= -1;
            }
        } break;
    }

    //convert temperature to fahrenheit if flag is set to true
    if (fahrenheit)
    {
        return (m_temperature * 1.8) + 32;
    }

    return m_temperature;
}

/**
 * gets the raw data from the last measurement
 * @param dataArray the array to which to copy the data
 */
void Mooglesp_DHT::getData(uint8_t* dataArray)
{
    //refresh data
    measurement();

    //copy data of m_data into dataArray
    if (dataArray != NULL)
    {
        for (int i = 0; i < MOOGLESP_DHT_DATA_SIZE; i++)
        {
            dataArray[i] = m_data[i];
        }
    }
}

/**
 * reads the data from the sensor
 */
void Mooglesp_DHT::measurement()
{
    uint32_t currentTime = millis();

    //wait two seconds before grapping new data
    if ((currentTime - m_lastTime) > 2000)
    {
        int index       = 0;
        int bitposition = 7;

        //clear data array
        memset(m_data, 0, sizeof(m_data));

        //trigger measurement
        setMode(OUTPUT);
        delay(1);
        digitalWrite(LOW);
        delay(18);
        digitalWrite(HIGH);

        //get confirmation
        setMode(INPUT);
        delayMicroseconds(30);
        pulseIn(m_pinNumber, HIGH);

        //read data from device
        for (int i = 0; i < MOOGLESP_DHT_DATA_PULSES; i++)
        {
            if (pulseIn(m_pinNumber, HIGH) > 40)
            {
                m_data[index] |= (1 << bitposition);
            }

            if(--bitposition < 0)
            {
                bitposition = 7;
                index++;
            }
        }

        //validate measurement
        if(m_data[0] && (m_data[0] + m_data[2]) != m_data[4])
        {
            m_humidity    = MOOGLESP_DHT_DATA_INVALID;
            m_temperature = MOOGLESP_DHT_DATA_INVALID;
        }

        //store last measurement time
        m_lastTime = currentTime;
    }
}
