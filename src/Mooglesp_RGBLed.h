#ifndef MOOGLESP_RGBLED_H
#define MOOGLESP_RGBLED_H

//includes
#include "Mooglesp_Led.h"

//class Mooglesp_RGBLed
class Mooglesp_RGBLed
{
    //public section
    public:
        //constructors and destructors
        Mooglesp_RGBLed(uint8_t pinRed, uint8_t pinGreen, uint8_t pinBlue);
        ~Mooglesp_RGBLed();

        //getter and setter
        byte     getColorBlue();
        byte     getColorGreen();
        byte     getColorRed();
        uint32_t getColor();
        void     setColor(byte red, byte green, byte blue);
        void     setColor(uint32_t color);

        //core functions
        bool state();
        void clear();
        void off();
        void on();

    //protected section
    protected:
        //internal objects
        Mooglesp_Led m_ledBlue;
        Mooglesp_Led m_ledGreen;
        Mooglesp_Led m_ledRed;

        //internal values
        byte     m_colorBlue;
        byte     m_colorGreen;
        byte     m_colorRed;
        uint32_t m_color;

        //internal functions
        void writeColor(byte red, byte green, byte blue);
};

#endif
