#ifndef MOOGLESP_DHT_H
#define MOOGLESP_DHT_H

//includes
#include <Mooglesp_Pin.h>

//defines
#define MOOGLESP_DHT_DATA_INVALID 9999
#define MOOGLESP_DHT_DATA_PULSES    40
#define MOOGLESP_DHT_DATA_SIZE       5
#define MOOGLESP_DHT_TYPE_DHT11     11
#define MOOGLESP_DHT_TYPE_DHT12     12
#define MOOGLESP_DHT_TYPE_DHT21     21
#define MOOGLESP_DHT_TYPE_DHT22     22

//class Mooglesp_DHT
class Mooglesp_DHT : public Mooglesp_Pin
{
    //public section
    public:
        //constructors and destructors
        explicit Mooglesp_DHT(uint8_t pinNumber,
            uint8_t type = MOOGLESP_DHT_TYPE_DHT11);
        ~Mooglesp_DHT();

        //getter and setter
        float getHumidity();
        float getTemperature(bool fahrenheit = false);
        void  getData(uint8_t* dataArray);

    //protected section
    protected:
        //internal arrays
        uint8_t m_data[MOOGLESP_DHT_DATA_SIZE] = { 0 };

        //internal values
        float    m_humidity;
        float    m_temperature;
        uint8_t  m_type;
        uint32_t m_lastTime;

        //internal functions
        bool validateType();
        void measurement();

    //private section
    private:
        //change access specifiers of read functions to private
        using Mooglesp_Pin::analogRead;
        using Mooglesp_Pin::analogReadSmooth;
        using Mooglesp_Pin::digitalRead;
};

#endif
