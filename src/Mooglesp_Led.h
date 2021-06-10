#ifndef MOOGLESP_LED_H
#define MOOGLESP_LED_H

//includes
#include "Mooglesp_Pin.h"

//class Mooglesp_Led
class Mooglesp_Led : public Mooglesp_Pin
{
    //public section
    public:
        //constructors and destructors
        explicit Mooglesp_Led(uint8_t pinNumber);
        ~Mooglesp_Led();

        //core functions
        bool state();
        void blink(uint32_t cycles, uint32_t delay);
        void fade(uint8_t start, uint8_t end, uint32_t delay);
        void off();
        void on();

    //private section:
    private:
        //change access specifiers of read functions to private
        using Mooglesp_Pin::analogRead;
        using Mooglesp_Pin::analogReadSmooth;
        using Mooglesp_Pin::digitalRead;
};

#endif
