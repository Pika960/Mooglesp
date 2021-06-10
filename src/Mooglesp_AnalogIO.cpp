//includes
#include "Mooglesp_AnalogIO.h"

/**
 * initializes the class instance
 */
Mooglesp_AnalogIO::Mooglesp_AnalogIO()
{
    m_adcNumber      = 0;
    m_channelSize    = MOOGLESP_ANALOGIO_CHANNEL_SIZE;
    m_frequency      = 5000;
    m_inputTime      = 100;
    m_outputChannels = new output_channel[m_channelSize];
    m_pinNumber      = 0;
    m_resolution     = 8;
    m_sampleSize     = 20;

    initChannels();
}

/**
 * cleans up the class instance
 */
Mooglesp_AnalogIO::~Mooglesp_AnalogIO()
{
    delete[] m_outputChannels;
}

/**
 * get a reference to the singleton object
 * @return a reference to the singleton object
 */
Mooglesp_AnalogIO& Mooglesp_AnalogIO::getInstance()
{
    static Mooglesp_AnalogIO m_instance;
    return m_instance;
}

/**
 * maps the port to the corresponding adc channel
 * @return true if mapping succeeded, false if not
 */
bool Mooglesp_AnalogIO::portmap()
{
    switch (m_pinNumber)
    {
        case 2:
        {
            m_adc2      = ADC2_CHANNEL_2;
            m_adcNumber = 2;

            adc2_config_channel_atten(ADC2_CHANNEL_2, ADC_ATTEN_DB_11);
        } break;

        case 4:
        {
            m_adc2      = ADC2_CHANNEL_0;
            m_adcNumber = 2;

            adc2_config_channel_atten(ADC2_CHANNEL_0, ADC_ATTEN_DB_11);
        } break;

        case 12:
        {
            m_adc2      = ADC2_CHANNEL_5;
            m_adcNumber = 2;

            adc2_config_channel_atten(ADC2_CHANNEL_5, ADC_ATTEN_DB_11);
        } break;

        case 13:
        {
            m_adc2      = ADC2_CHANNEL_4;
            m_adcNumber = 2;

            adc2_config_channel_atten(ADC2_CHANNEL_4, ADC_ATTEN_DB_11);
        } break;

        case 14:
        {
            m_adc2      = ADC2_CHANNEL_6;
            m_adcNumber = 2;

            adc2_config_channel_atten(ADC2_CHANNEL_6, ADC_ATTEN_DB_11);
        } break;

        case 15:
        {
            m_adc2      = ADC2_CHANNEL_3;
            m_adcNumber = 2;

            adc2_config_channel_atten(ADC2_CHANNEL_3, ADC_ATTEN_DB_11);
        } break;

        case 25:
        {
            m_adc2      = ADC2_CHANNEL_8;
            m_adcNumber = 2;

            adc2_config_channel_atten(ADC2_CHANNEL_8, ADC_ATTEN_DB_11);
        } break;

        case 26:
        {
            m_adc2      = ADC2_CHANNEL_9;
            m_adcNumber = 2;

            adc2_config_channel_atten(ADC2_CHANNEL_9, ADC_ATTEN_DB_11);
        } break;

        case 27:
        {
            m_adc2      = ADC2_CHANNEL_7;
            m_adcNumber = 2;

            adc2_config_channel_atten(ADC2_CHANNEL_7, ADC_ATTEN_DB_11);
        } break;

        case 32:
        {
            m_adc1      = ADC1_CHANNEL_4;
            m_adcNumber = 1;

            adc1_config_width(ADC_WIDTH_BIT_12);
            adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);
        } break;

        case 33:
        {
            m_adc1      = ADC1_CHANNEL_5;
            m_adcNumber = 1;

            adc1_config_width(ADC_WIDTH_BIT_12);
            adc1_config_channel_atten(ADC1_CHANNEL_5, ADC_ATTEN_DB_11);
        } break;

        case 34:
        {
            m_adc1      = ADC1_CHANNEL_6;
            m_adcNumber = 1;

            adc1_config_width(ADC_WIDTH_BIT_12);
            adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11);
        } break;

        case 35:
        {
            m_adc1      = ADC1_CHANNEL_7;
            m_adcNumber = 1;

            adc1_config_width(ADC_WIDTH_BIT_12);
            adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_11);
        } break;

        case 36:
        {
            m_adc1      = ADC1_CHANNEL_0;
            m_adcNumber = 1;

            adc1_config_width(ADC_WIDTH_BIT_12);
            adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
        } break;

        case 39:
        {
            m_adc1      = ADC1_CHANNEL_3;
            m_adcNumber = 1;

            adc1_config_width(ADC_WIDTH_BIT_12);
            adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_11);
        } break;

        default:
        {
            m_adcNumber = 0;
            return false;
        }
    }

    return true;
}

/**
 * reads the value from the analog pin
 * @return the analog reading on the pin
 */
int Mooglesp_AnalogIO::analogRead()
{
    int inputValue = -1;

    if (portmap())
    {
        if (m_adcNumber == 1)
        {
            inputValue = adc1_get_raw(m_adc1);
        }

        else if (m_adcNumber == 2)
        {
            adc2_get_raw(m_adc2, ADC_WIDTH_BIT_12, &inputValue);
        }
    }

    return inputValue;
}

/**
 * reads the value from the analog pin and smooths the data
 * @return the analog reading on the pin
 */
int Mooglesp_AnalogIO::analogReadSmooth()
{
    int totalValue = 0;

    for (int i = 0; i < m_sampleSize; i++)
    {
        int inputValue = analogRead();

        if (inputValue == -1)
        {
            return -1;
        }

        totalValue += inputValue;
        delay(m_inputTime / m_sampleSize);
    }

    return totalValue / m_sampleSize;
}

/**
 * searches for a free channel
 * @return the channel number if a free channel is available, else -1
 */
int Mooglesp_AnalogIO::checkIfPinIsConnected()
{
    int channel = -1;

    //check if pin is already connected to a channel
    for (uint8_t i = 0; i < m_channelSize; i++)
    {
        if (m_outputChannels[i].pin == m_pinNumber)
        {
            channel = i;
            break;
        }
    }

    //if pin is not connected, connect it to a free channel
    if (channel == -1)
    {
        for (uint8_t i = 0; i < m_channelSize; i++)
        {
            if (m_outputChannels[i].pin == -1)
            {
                m_outputChannels[i].pin = m_pinNumber;
                channel                 = i;

                ledcSetup(channel, m_outputChannels[i].frequency,
                    m_outputChannels[i].resolution);
                ledcAttachPin(m_pinNumber, channel);

                break;
            }
        }
    }

    return channel;
}

/**
 * writes an analog value to a pin
 * @param value the data which should be written
 */
void Mooglesp_AnalogIO::analogWrite(int value)
{
    int channel = checkIfPinIsConnected();

    if (channel != -1 && channel < m_channelSize)
    {
        int resLevel = pow(2, m_outputChannels[channel].resolution);
        int payload  = ((resLevel -1) / 255) * min(value, 255);

        ledcWrite(channel, payload);
    }
}

/**
 * initializes the channel array
 */
void Mooglesp_AnalogIO::initChannels()
{
    for (int i = 0; i < m_channelSize; i++)
    {
        m_outputChannels[i].pin        = -1;
        m_outputChannels[i].frequency  = m_frequency;
        m_outputChannels[i].resolution = m_resolution;
    }
}

/**
 * sets the frequency to a new value
 * @param frequency the new value of frequency
 */
void Mooglesp_AnalogIO::setFrequency(uint32_t frequency)
{
    m_frequency = frequency;

    updateChannels();
}

/**
 * sets the input time to a new value
 * @param inputTime the new value of input time
 */
void Mooglesp_AnalogIO::setInputTime(uint32_t inputTime)
{
    m_inputTime = inputTime;
}

/**
 * sets the pin number to a new value
 * @param pinNumber the new value of pin number
 */
void Mooglesp_AnalogIO::setPinNumber(uint8_t pinNumber)
{
    m_pinNumber = pinNumber;
}

/**
 * sets the resolution to a new value
 * @param resolution the new value of resoultion
 */
void Mooglesp_AnalogIO::setResolution(uint8_t resolution)
{
    m_resolution = resolution;

    updateChannels();
}

/**
 * sets the sample size to a new value
 * @param sampleSize the new value of sample size
 */
void Mooglesp_AnalogIO::setSampleSize(uint32_t sampleSize)
{
    m_sampleSize = sampleSize;
}

/**
 * updates the channel array
 */
void Mooglesp_AnalogIO::updateChannels()
{
    for (int i = 0; i < m_channelSize; i++)
    {
        m_outputChannels[i].frequency  = m_frequency;
        m_outputChannels[i].resolution = m_resolution;
    }
}
