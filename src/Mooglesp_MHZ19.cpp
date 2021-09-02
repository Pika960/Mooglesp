//includes
#include "Mooglesp_MHZ19.h"

/**
 * initializes the class instance
 */
Mooglesp_MHZ19::Mooglesp_MHZ19(uint8_t rx, uint8_t tx)
{
    m_currentCO2  = -1;
    m_lastCO2     = -1;
    m_rx          = rx;
    m_temperature = -1;
    m_tx          = tx;
}

/**
 * cleans up the class instance
 */
Mooglesp_MHZ19::~Mooglesp_MHZ19()
{
    //nothing to do here
}

/**
 * gets the current auto calibration status
 * @return the current auto calibration status
 */
bool Mooglesp_MHZ19::getAutoCalibrationStatus()
{
    //create the command array
    uint8_t command[MOOGLESP_MHZ19_ARRAYSIZE_REQUEST];

    //create the response array
    uint8_t response[MOOGLESP_MHZ19_ARRAYSIZE_RESPONSE];

    //construct the command, write it to the sensor and store the response
    buildCommand(MOOGLESP_MHZ19_COMMAND_ABC_STATUS, command);
    writeCommand(command, response);

    //return the current auto calibration status
    return response[7];
}

/**
 * checks if the sensor is ready
 */
bool Mooglesp_MHZ19::isWarmingUp()
{
    //according to the datasheet the sensor can take up to 3min to be ready
    //let's cap this function to this value
    if (millis() < 180000)
    {
        //refresh data
        measurement();

        //store data from last measurement on first run
        if (m_lastCO2 == -1)
        {
            m_lastCO2 = m_currentCO2;
        }

        //on every other run of this function check if data has changed
        else
        {
            //if data has changed declare sensor as ready
            if (m_lastCO2 != m_currentCO2)
            {
                m_lastCO2 = 0;
                return false;
            }
        }

        //return true while sensor is not ready
        return true;
    }

    //return that sensor is ready after 3min
    return false;
}

/**
 * gets the current temperature
 * @param fahrenheit if set to true temperature will be in fahrenheit
 * @return the current temperature
 */
int8_t Mooglesp_MHZ19::getTemperature(bool fahrenheit)
{
    //refresh data
    measurement();

    //convert temperature to fahrenheit if flag is set to true
    if (fahrenheit)
    {
        return (m_temperature * 1.8) + 32;
    }

    //if flag is not set return current temperature in celsius
    return m_temperature;
}

/**
 * gets the current carbon dioxide concentration
 * @return the current carbon dioxide concentration
 */
int16_t Mooglesp_MHZ19::getCO2()
{
    //refresh data
    measurement();

    //return the current carbon dioxide concentration
    return m_currentCO2;
}

/**
 * calculates a checksum depending on the specified command
 * @param command an array containing the command sequence
 * @return the corresponding checksum
 */
uint8_t Mooglesp_MHZ19::calculateChecksum(uint8_t command[])
{
    //create a variable to store the checksum
    uint8_t sum = 0x00;

    //build the sum of the array
    for (int i = 1; i < MOOGLESP_MHZ19_ARRAYSIZE_REQUEST; i++)
    {
        sum += command[i];
    }

    //calculate the checksum and return it
    return 0xff - sum + 0x01;
}

/**
 * gets the current rx pin number
 * @return the current rx pin number
 */
uint8_t Mooglesp_MHZ19::getRX()
{
    //return the current rx pin number
    return m_rx;
}

/**
 * gets the current tx pin number
 * @return the current tx pin number
 */
uint8_t Mooglesp_MHZ19::getTX()
{
    //return the current tx pin number
    return m_tx;
}

/**
 * creates a command sequence
 * @param type the command you want to build
 * @param command an array in which the command sequence will be stored
 * @param abc if set to true the third value of the command will be set
 */
void Mooglesp_MHZ19::buildCommand(uint8_t type, uint8_t command[], bool abc)
{
    //set the address of the sensor to any
    command[0] = MOOGLESP_MHZ19_COMMAND_ADDRESS_ANY;

    //set the register
    command[1] = MOOGLESP_MHZ19_COMMAND_REGISTER_SET;

    //set the command
    command[2] = type;

    //decide if auto calibration (abc) should be on or off
    if (abc)
    {
        command[3] = MOOGLESP_MHZ19_COMMAND_GET_FIRMWARE;
    }

    else
    {
        command[3] = MOOGLESP_MHZ19_COMMAND_EMPTY;
    }

    //set everything else to zero
    command[4] = MOOGLESP_MHZ19_COMMAND_EMPTY;
    command[5] = MOOGLESP_MHZ19_COMMAND_EMPTY;
    command[6] = MOOGLESP_MHZ19_COMMAND_EMPTY;
    command[7] = MOOGLESP_MHZ19_COMMAND_EMPTY;
}

/**
 * configures the auto calibration of the sensor
 * @param enableAutoCalibration if set to true auto-mode will be enabled
 */
void Mooglesp_MHZ19::configureAutoCalibration(bool enableAutoCalibration)
{
    //create the command array
    uint8_t command[MOOGLESP_MHZ19_ARRAYSIZE_REQUEST] = { 0 };

    //check if flag is set to true
    if (enableAutoCalibration)
    {
        //if true then enable auto calibration
        buildCommand(MOOGLESP_MHZ19_COMMAND_ABC_ON_OFF, command, true);
    }

    else
    {
        //if false then disable auto calibration
        buildCommand(MOOGLESP_MHZ19_COMMAND_ABC_ON_OFF, command, false);
    }

    //write the command to the sensor
    writeCommand(command, NULL);
}

/**
 * configures the span calibration of the sensor
 * @param span the value of the carbon dioxide span (between 0 - 10000)
 */
void Mooglesp_MHZ19::configureSpanCalibration(uint16_t span)
{
    //create the command array
    uint8_t command[MOOGLESP_MHZ19_ARRAYSIZE_REQUEST] = { 0 };

    //check if span is in valid range
    if (span > 10000)
    {
        //if not set span to max value
        span = 10000;
    }

    //construct the command
    buildCommand(MOOGLESP_MHZ19_COMMAND_CALIBRATION_SPAN, command);
    command[3] = (uint8_t)(span / 256);
    command[4] = (uint8_t)(span % 256);

    //write the command to the sensor
    writeCommand(command, NULL);
}

/**
 * enables zero calibration
 */
void Mooglesp_MHZ19::enableZeroCalibration()
{
    //create the command array
    uint8_t command[MOOGLESP_MHZ19_ARRAYSIZE_REQUEST] = { 0 };

    //construct the command and write it to the sensor
    buildCommand(MOOGLESP_MHZ19_COMMAND_CALIBRATION_ZERO, command);
    writeCommand(command, NULL);
}

/**
 * gets the current firmware version of the sensor
 * @param version an array containing the current firmware version
 */
void Mooglesp_MHZ19::getFirmwareVersion(char firmwareVersion[])
{
    //create the command array
    uint8_t command[MOOGLESP_MHZ19_ARRAYSIZE_REQUEST];

    //create the response array
    uint8_t response[MOOGLESP_MHZ19_ARRAYSIZE_RESPONSE];

    //construct the command, write it to the sensor and store the response
    buildCommand(MOOGLESP_MHZ19_COMMAND_GET_FIRMWARE, command);
    writeCommand(command, response);

    //store firmware version in array
    for (uint8_t i = 0; i < 4; i++)
    {
        firmwareVersion[i] = char(response[i + 2]);
    }
}

/**
 * reads the data from the sensor
 */
void Mooglesp_MHZ19::measurement()
{
    //create the command array
    uint8_t command[MOOGLESP_MHZ19_ARRAYSIZE_REQUEST] = { 0 };

    //create the response array
    uint8_t response[MOOGLESP_MHZ19_ARRAYSIZE_RESPONSE] = { 0 };

    //construct the command, write it to the sensor and store the response
    //send a command to the sensor and store the response
    buildCommand(MOOGLESP_MHZ19_COMMAND_CO2_LIMITED_TEMP_INTEGER, command);
    writeCommand(command, response);

    //calculate checksum
    uint8_t checksum = calculateChecksum(response);

    //validate reponse
    if (response[0] == MOOGLESP_MHZ19_COMMAND_ADDRESS_ANY &&
        response[1] == MOOGLESP_MHZ19_COMMAND_CO2_LIMITED_TEMP_INTEGER &&
        checksum    == response[MOOGLESP_MHZ19_ARRAYSIZE_RESPONSE - 1])
    {
        //store data into variables
        m_currentCO2  = response[2] * 256 + response[3];
        m_temperature = response[4] - 40;
    }

    //if data is not valid store error values in variables
    else
    {
        m_currentCO2  = -1;
        m_temperature = -1;
    }
}

/**
 * sets the rx pin number to a new value
 * @param rx the new value of the rx pin number
 */
void Mooglesp_MHZ19::setRX(uint8_t rx)
{
    //update the rx pin number
    m_rx = rx;
}

/**
 * sets the tx pin number to a new value
 * @param tx the new value of the tx pin number
 */
void Mooglesp_MHZ19::setTX(uint8_t tx)
{
    //update the tx pin number
    m_tx = tx;
}

/**
 * writes a command to the sensor
 * @param command an array containing the command sequence
 * @param response an array containing the response from the sensor
 */
void Mooglesp_MHZ19::writeCommand(uint8_t command[], uint8_t response[])
{
    //create an instance of SoftwareSerial
    SoftwareSerial serial(m_rx, m_tx);

    //configure the serial connection and send the command
    serial.begin(9600);
    serial.write(command, MOOGLESP_MHZ19_ARRAYSIZE_REQUEST);
    serial.write(calculateChecksum(command));
    serial.flush();

    //check if response array is valid
    if (response != NULL)
    {
        //create a counter variable
        int counterWait = 0;

        // wait for the serial port to send data
        while (!serial.available())
        {
            //increase the counter by 1 each time
            counterWait++;

            //give up after 50 cycles
            if (counterWait > 50)
            {
                return;
            }

            //otherwise wait a moment and then repeat the loop
            yield();
            delay(10);
        }

        //store response in array
        serial.readBytes(response, MOOGLESP_MHZ19_ARRAYSIZE_RESPONSE);
    }
}
