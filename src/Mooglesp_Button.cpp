//includes
#include "Mooglesp_Button.h"

/**
 * initializes the class instance
 */
Mooglesp_Button::Mooglesp_Button(uint8_t pinNumber, uint32_t debounce,
    bool pullupActive) : Mooglesp_Pin(pinNumber,
    (pullupActive ? INPUT_PULLUP : INPUT_PULLDOWN))
{
    m_changed      = false;
    m_debounce     = debounce;
    m_lastChange   = millis();
    m_lastState    = LOW;
    m_pullupActive = pullupActive;
    m_state        = LOW;
}

/**
 * cleans up the class instance
 */
Mooglesp_Button::~Mooglesp_Button()
{
    //nothing to do here
}

/**
 * checks whether the button is currently pressed or not
 * @returns true if button is currently pressed, false if not
 */
bool Mooglesp_Button::isPressed()
{
    return m_state;
}

/**
 * checks whether the button is currently released or not
 * @returns true if button is currently released, false if not
 */
bool Mooglesp_Button::isReleased()
{
    return !m_state;
}

/**
 * gets the current state of the button
 * @returns true if button is pressed, false if not
 */
bool Mooglesp_Button::read()
{
    bool     currentState = digitalRead();
    uint32_t currentTime  = millis();

    if (m_pullupActive)
    {
        currentState = !currentState;
    }

    if (currentTime - m_lastChange < m_debounce)
    {
        m_changed = false;
    }

    else
    {
        m_lastState = m_state;
        m_state     = currentState;
        m_changed   = (m_state != m_lastState);

        if (m_changed)
        {
            m_lastChange = currentTime;
        }
    }

    return m_state;
}

/**
 * checks whether the button was pressed during the last cycles
 * @returns true if button is was pressed, false if not
 */
bool Mooglesp_Button::wasPressed()
{
    return m_state && m_changed;
}

/**
 * checks whether the button was released during the last cycles
 * @returns true if button is was pressed, false if not
 */
bool Mooglesp_Button::wasReleased()
{
    return !m_state && m_changed;
}
