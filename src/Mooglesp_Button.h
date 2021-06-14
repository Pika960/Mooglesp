#ifndef MOOGLESP_BUTTON_H
#define MOOGLESP_BUTTON_H

//includes
#include "Mooglesp_Pin.h"

//class Mooglesp_Button
class Mooglesp_Button : public Mooglesp_Pin
{
    //public section
    public:
        //constructors and destructors
        explicit Mooglesp_Button(uint8_t pinNumber, uint32_t debounce = 25,
            bool pullupActive = true);
        ~Mooglesp_Button();

        //core functions
        bool isPressed();
        bool isReleased();
        bool read();
        bool wasPressed();
        bool wasReleased();

    //protected section:
    protected:
        bool     m_changed;
        bool     m_lastState;
        bool     m_pullupActive;
        bool     m_state;
        uint32_t m_debounce;
        uint32_t m_lastChange;

    //private section:
    private:
        //change access specifiers of write functions to private
        using Mooglesp_Pin::analogWrite;
        using Mooglesp_Pin::digitalWrite;
};

#endif
