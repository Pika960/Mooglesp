#ifndef MOOGLESP_ANALOGIO_H
#define MOOGLESP_ANALOGIO_H

//includes
#include <Arduino.h>
#include <driver/adc.h>

//defines
#define MOOGLESP_ANALOGIO_CHANNEL_SIZE 16

//typedefs
typedef struct output_channel
{
    int8_t  pin;
    double  frequency;
    uint8_t resolution;
};

//class Mooglesp_AnalogIO
class Mooglesp_AnalogIO
{
    //public section
    public:
        //static access function
        static Mooglesp_AnalogIO& getInstance();

        //destructors
        ~Mooglesp_AnalogIO();

        //getter and setter
        void setFrequency(uint32_t frequency);
        void setInputTime(uint32_t inputTime);
        void setPinNumber(uint8_t pinNumber);
        void setResolution(uint8_t resolution);
        void setSampleSize(uint32_t sampleSize);

        //read and write functions
        int  analogRead();
        int  analogReadSmooth();
        void analogWrite(int value);

    //private section
    private:
        //constructors
        Mooglesp_AnalogIO();
        Mooglesp_AnalogIO(const Mooglesp_AnalogIO&);

        //overloaded operators
        Mooglesp_AnalogIO& operator=(const Mooglesp_AnalogIO&);

        //internal values
        adc1_channel_t  m_adc1;
        adc2_channel_t  m_adc2;
        output_channel* m_outputChannels;
        uint8_t         m_adcNumber;
        uint8_t         m_channelSize;
        uint32_t        m_frequency;
        uint32_t        m_inputTime;
        uint8_t         m_pinNumber;
        uint8_t         m_resolution;
        uint32_t        m_sampleSize;

        //internal functions
        bool portmap();
        int  checkIfPinIsConnected();
        void initChannels();
        void updateChannels();
};

#endif
