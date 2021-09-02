#ifndef MOOGLESP_MHZ19_H
#define MOOGLESP_MHZ19_H

//includes
#include <Arduino.h>
#include <SoftwareSerial.h>

#define MOOGLESP_MHZ19_ARRAYSIZE_REQUEST                 0x08
#define MOOGLESP_MHZ19_ARRAYSIZE_RESPONSE                0x09
#define MOOGLESP_MHZ19_COMMAND_ABC_ON_OFF                0x79
#define MOOGLESP_MHZ19_COMMAND_ABC_STATUS                0x7D
#define MOOGLESP_MHZ19_COMMAND_ADDRESS_ANY               0xFF
#define MOOGLESP_MHZ19_COMMAND_CALIBRATION_SPAN          0x88
#define MOOGLESP_MHZ19_COMMAND_CALIBRATION_ZERO          0x87
#define MOOGLESP_MHZ19_COMMAND_CO2_LIMITED_TEMP_INTEGER  0x86
#define MOOGLESP_MHZ19_COMMAND_CO2_RAW                   0x84
#define MOOGLESP_MHZ19_COMMAND_CO2_UNLIMITED_TEMP_FLOAT  0x85
#define MOOGLESP_MHZ19_COMMAND_CONFIGURE_RANGE           0x99
#define MOOGLESP_MHZ19_COMMAND_EMPTY                     0x00
#define MOOGLESP_MHZ19_COMMAND_GET_CO2_BACKGROUND        0x9C
#define MOOGLESP_MHZ19_COMMAND_GET_FIRMWARE              0xA0
#define MOOGLESP_MHZ19_COMMAND_GET_LAST_RESPONSE         0xA2
#define MOOGLESP_MHZ19_COMMAND_GET_RANGE                 0x9B
#define MOOGLESP_MHZ19_COMMAND_GET_TEMPERATE_CALIBRATION 0xA3
#define MOOGLESP_MHZ19_COMMAND_RECOVERY_RESET            0x78
#define MOOGLESP_MHZ19_COMMAND_REGISTER_SET              0x01

//class Mooglesp_MHZ19
class Mooglesp_MHZ19
{
    //public section
    public:
        //constructors and destructors
        Mooglesp_MHZ19(uint8_t rx, uint8_t tx);
        ~Mooglesp_MHZ19();

        //getter and setter
        bool    getAutoCalibrationStatus();
        int8_t  getTemperature(bool fahrenheit = false);
        int16_t getCO2();
        uint8_t getRX();
        void    getFirmwareVersion(char firmwareVersion[]);
        void    setRX(uint8_t rx);

        //core functions
        bool isWarmingUp();
        void configureAutoCalibration(bool enableAutoCalibration);
        void configureSpanCalibration(uint16_t span);
        void enableZeroCalibration();

    //protected section
    protected:
        //internal values
        int8_t  m_temperature;
        int16_t m_currentCO2;
        int16_t m_lastCO2;
        uint8_t m_rx;
        uint8_t m_tx;

        //internal functions
        uint8_t calculateChecksum(uint8_t command[]);
        void buildCommand(uint8_t type, uint8_t command[], bool abc = false);
        void measurement();
        void writeCommand(uint8_t command[], uint8_t response[]);
};

#endif
