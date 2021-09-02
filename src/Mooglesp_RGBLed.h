#ifndef MOOGLESP_RGBLED_H
#define MOOGLESP_RGBLED_H

//includes
#include "Mooglesp_Led.h"

//defines
#define MOOGLESP_RGBLED_COLOR_BLACK   0x000000
#define MOOGLESP_RGBLED_COLOR_BLUE    0x0000FF
#define MOOGLESP_RGBLED_COLOR_CYAN    0x00FFFF
#define MOOGLESP_RGBLED_COLOR_GREEN   0x00FF00
#define MOOGLESP_RGBLED_COLOR_MAGENTA 0xFF00FF
#define MOOGLESP_RGBLED_COLOR_RED     0xFF0000
#define MOOGLESP_RGBLED_COLOR_WHITE   0xFFFFFF
#define MOOGLESP_RGBLED_COLOR_YELLOW  0xFFFF00

//class Mooglesp_RGBLed
class Mooglesp_RGBLed
{
    //public section
    public:
        //constructors and destructors
        Mooglesp_RGBLed(uint8_t pinRed, uint8_t pinGreen, uint8_t pinBlue);
        ~Mooglesp_RGBLed();

        //getter and setter
        uint8_t  getColorBlue();
        uint8_t  getColorGreen();
        uint8_t  getColorRed();
        uint32_t getColor();
        void setColor(uint8_t red, uint8_t green,
            uint8_t blue, bool write = true);
        void setColor(uint32_t color, bool write = true);

        //core functions
        bool state();
        void blink(uint32_t cycles, uint32_t delay,
            uint8_t red, uint8_t green, uint8_t blue);
        void blink(uint32_t cycles, uint32_t delay,
            uint32_t color = 0xFFFFFF);
        void clear();
        void fade(uint32_t delay, uint8_t red, uint8_t green, uint8_t blue);
        void fade(uint32_t delay, uint32_t color);
        void off();
        void on();
        void rainbow(uint32_t delay);

    //protected section
    protected:
        //internal objects
        Mooglesp_Led m_ledBlue;
        Mooglesp_Led m_ledGreen;
        Mooglesp_Led m_ledRed;

        //internal values
        uint8_t  m_colorBlue;
        uint8_t  m_colorGreen;
        uint8_t  m_colorRed;
        uint32_t m_color;

        //internal functions
        void writeColor(uint8_t red, uint8_t green, uint8_t blue);
};

#endif
