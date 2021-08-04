#ifndef MOOGLESP_LM75_H
#define MOOGLESP_LM75_H

//includes
#include <Arduino.h>
#include <Wire.h>

//defines
#define MOOGLESP_LM75_REGISTER_TEMPERATURE   0x00
#define MOOGLESP_LM75_REGISTER_CONFIGURATION 0x01
#define MOOGLESP_LM75_REGISTER_THYST         0x02
#define MOOGLESP_LM75_REGISTER_TOS           0x03

//class Mooglesp_LM75
class Mooglesp_LM75
{
    //public section
    public:
        //constructors and destructors
        explicit Mooglesp_LM75(uint8_t address, uint8_t busNumber = 0);
        ~Mooglesp_LM75();

        //getter and setter
        float getHysteresis(bool fahrenheit = false);
        float getOverTemperature(bool fahrenheit = false);
        float getTemperature(bool fahrenheit = false);
        void  setHysteresis(uint8_t hysteresis);

        //core functions
        bool begin(uint8_t sda, uint8_t scl, uint32_t frequency);

    //protected section
    protected:
        //internal objects
        TwoWire m_wire;

        //internal values
        uint8_t  m_address;
        uint32_t m_registerData;

        //internal functions
        void readRegister(uint8_t address);
        void writeRegister(uint8_t address, uint32_t data);
};

#endif
