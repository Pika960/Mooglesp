#ifndef MOOGLESP_PIN_H
#define MOOGLESP_PIN_H

//includes
#include <Arduino.h>
#include "Mooglesp_AnalogIO.h"

//class Mooglesp_Pin
class Mooglesp_Pin
{
    //public section
    public:
        //constructors and destructors
        Mooglesp_Pin(uint8_t pinNumber, uint8_t mode);
        ~Mooglesp_Pin();

        //getter and setter
        uint8_t  getMode();
        uint8_t  getPinNumber();
        uint32_t getValue();
        void     setMode(uint8_t mode);
        void     setPinNumber(uint8_t pinNumber);

        //read and write functions
        int  analogRead();
        int  analogReadSmooth();
        int  digitalRead();
        void analogWrite(int value);
        void digitalWrite(int value);

    //protected section
    protected:
        //internal references
        Mooglesp_AnalogIO& m_analogIO = Mooglesp_AnalogIO::getInstance();

        //internal values
        uint8_t  m_mode;
        uint8_t  m_pinNumber;
        uint32_t m_value;

        //internal functions
        bool validateMode();
};

#endif
