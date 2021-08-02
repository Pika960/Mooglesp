//includes
#include <Arduino.h>
#include <Mooglesp_DHT.h>

//global constants
const uint8_t pin_dht = 18;

//global objects
Mooglesp_DHT dht(pin_dht);

/**
 * initializes the current sketch
 */
void setup()
{
    //set the baud rate to 115200
    Serial.begin(115200);
}

/**
 * runs the main logic in an infinite loop
 */
void loop()
{
    //wait two seconds before reading from sensor
    delay(2000);

    //get data from sensor
    float temperature = dht.getTemperature();
    float humidity    = dht.getHumidity();

    //get raw data from sensor
    uint8_t data[MOOGLESP_DHT_DATA_SIZE];
    dht.getData(data);

    //print the data to the serial monitor
    Serial.printf("Temperature: %.1f°c\n", temperature);
    Serial.printf("Humidity:    %.1f%%\n", humidity);

    //print the raw data to the serial monitor
    Serial.printf("Raw data: ");

    for(int i = 0; i < MOOGLESP_DHT_DATA_SIZE; i++)
    {
        Serial.printf("0x%02x(%d) ", data[i], data[i]);
    }

    Serial.printf("\n\n");
}
