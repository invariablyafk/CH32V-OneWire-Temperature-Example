/**
 * @file temp-sensors.c
 * @brief DS18B20 Temp Sensor Communication Example with Maxim OneWire interface
 * @author Tal G.
 * @license MIT License
 * @details This code demonstrates temperature measurement using DS18B20 one-wire sensors.
 */

#include "ch32v003fun.h"
#include "ch32v003_GPIO_branchless.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "OneWire.c"

// Function prototypes
/**
 * @brief Initializes the hardware
 */
void initializeHardware();
/**
 * @brief Find the next DS18x20 sensor on the one-wire bus.
 * @param address The 8-byte address of the found sensor.
 * @return True if a sensor is found, false otherwise.
 */
bool findNextSensor(uint8_t address[8]);
/**
 * @brief Validate the CRC of the sensor's address.
 * @param address The 8-byte address of the sensor.
 * @return True if the CRC is valid, false otherwise.
 */
bool validateAddressCRC(uint8_t address[8]);
/**
 * @brief Print the type of DS18x20 sensor based on its address.
 * @param address The 8-byte address of the sensor.
 */
void printSensorType(uint8_t address[8]);
/**
 * @brief Start a temperature conversion on the DS18x20 sensor.
 * @param address The 8-byte address of the sensor.
 */
void startTemperatureConversion(uint8_t address[8]);
/**
 * @brief Read temperature data from the DS18x20 sensor.
 * @param address The 8-byte address of the sensor.
 * @param data The array to store the temperature data.
 * @return True if the data is successfully read, false otherwise.
 */
bool readTemperatureData(uint8_t address[8], uint8_t data[9]);
/**
 * @brief Validate the CRC of the temperature data.
 * @param data The temperature data.
 * @return True if the CRC is valid, false otherwise.
 */
bool validateDataCRC(uint8_t data[9]);
/**
 * @brief Convert raw temperature data to Celsius
 * @param data The temperature data.
 * @param address The sensor address, used to calculate the type ( address[0] == 0x10 for DS18S20, otherwise DS18B20/DS1822).
 * @return The temperature in raw format.
 */
float convertRawDataToCelsius(uint8_t address[8], uint8_t data[9]);
/**
 * @brief Print the temperature data.
 * @param address The 8-byte address of the sensor.
 * @param raw The raw temperature data.
 */
void printTemperatureData(uint8_t address[8], float celsius);

/**
 * @brief Initializes the hardware
 * This function initializes the hardware for temperature sensor communication on pin C4
 */
void setup() {
    GPIO_port_enable(GPIO_port_C);
    GPIO_pinMode(GPIOv_from_PORT_PIN(GPIO_port_C, 4), GPIO_pinMode_O_pushPull, GPIO_Speed_50MHz);
    printf("Starting up..");
}

/**
 * @brief Main loop for processing received data and serial communication.
 * This function is the main loop that performs temperature measurements using DS18B20 sensors.
 */
void loop() {
    uint8_t address[8];
    uint8_t data[9];
    float temperatureInC;
    
    if (!findNextSensor(address)) {
        printf("----\n");
        OneWireResetSearch();
        Delay_Ms(250);
        return;
    }
    
    if (!validateAddressCRC(address)) {
        printf("Invalid address detected!\n");
        return;
    }
    
    printSensorType(address);
    startTemperatureConversion(address);

    Delay_Ms(1000); // wait for temperature conversion to complete.
    
    if (!readTemperatureData(address, data)) {
        printf("No valid temperature sent!\n");
        return;
    }
    
    temperatureInC = convertRawDataToCelsius(address, data);
    printTemperatureData(address, temperatureInC);
}

/**
 * @brief Entry point of the program.
 * This function initializes the system and sets up the main loop for temperature measurements.
 */
int main() {
    SystemInit();
    setup();
    while (1) {
        loop();
    }
}

// Function definitions

/**
 * @brief Find the next DS18x20 sensor on the one-wire bus.
 * @param address The 8-byte address of the found sensor.
 * @return True if a sensor is found, false otherwise.
 * This function searches for the next DS18x20 sensor on the one-wire bus.
 */
bool findNextSensor(uint8_t address[8]) {
    if (!OneWireSearch(address, true)) {
        return false;
    }
    return true;
}

/**
 * @brief Validate the CRC of the sensor's address.
 * @param address The 8-byte address of the sensor.
 * @return True if the CRC is valid, false otherwise.
 * This function validates the CRC of the sensor's address to ensure it's correct.
 */
bool validateAddressCRC(uint8_t address[8]) {
    if (OneWireCrc8(address, 7) != address[7]) {
        return false;
    }
    return true;
}

/**
 * @brief Print the type of DS18x20 sensor based on its address.
 * @param address The 8-byte address of the sensor.
 * This function prints the type of DS18x20 sensor based on its address.
 */
void printSensorType(uint8_t address[8]) {
    switch (address[0]) {
        case 0x10:
            printf("DS18S20 ");  // or old DS1820
            break;
        case 0x28:
            printf("DS18B20 ");
            break;
        case 0x22:
            printf("DS1822 ");
            break;
        default:
            printf("Device is not a DS18x20 family device.\n");
            break;
    }
}

/**
 * @brief Start a temperature conversion on the DS18x20 sensor.
 * @param address The 8-byte address of the sensor.
 * This function initiates a temperature conversion on the DS18x20 sensor.
 */
void startTemperatureConversion(uint8_t address[8]) {
    OneWireReset();
    OneWireSelect(address);
    OneWireWrite(0x44, 0);  // start conversion, with no parasite power on at the end
}

/**
 * @brief Read temperature data from the DS18x20 sensor.
 * @param address The 8-byte address of the sensor.
 * @param data The array to store the temperature data.
 * @return True if the data is successfully read, false otherwise.
 * This function reads temperature data from the DS18x20 sensor and validates it.
 */
bool readTemperatureData(uint8_t address[8], uint8_t data[9]) {
    OneWireReset();
    OneWireSelect(address);
    OneWireWrite(0xBE, 0);  // Read Scratchpad
    for (uint8_t i = 0; i < 9; i++) {
        data[i] = OneWireRead();
    }
    if (OneWireCrc8(data, 8) != data[8]) {
        return false;
    }
    return true;
}

/**
 * @brief Convert raw temperature data to Celsius
 * @param data The temperature data.
 * @param address The sensor address, used to calculate the type ( address[0] == 0x10 for DS18S20, otherwise DS18B20/DS1822).
 * @return The temperature in celsius.
 * This function converts the sensors temperature data to Celsius based on the sensor type.
 */
float convertRawDataToCelsius(uint8_t address[8], uint8_t data[9]) {
    int16_t raw = (data[1] << 8) | data[0];
    if (address[0] == 0x10 ) {
        raw = raw << 3;  // 9 bit resolution default
        if (data[7] == 0x10) {
            raw = (raw & 0xFFF0) + 12 - data[6];
        }
    } else {
        uint8_t cfg = (data[4] & 0x60);
        if (cfg == 0x00) raw = raw & ~7;      // 9 bit resolution, 93.75 ms
        else if (cfg == 0x20) raw = raw & ~3;  // 10 bit res, 187.5 ms
        else if (cfg == 0x40) raw = raw & ~1;  // 11 bit res, 375 ms
        // default is 12 bit resolution, 750 ms conversion time
    }
    return (float)(raw / 16.0);
}

/**
 * @brief Print the temperature data.
 * @param address The 8-byte address of the sensor.
 * @param raw The raw temperature data.
 * This function prints the temperature data in Celsius and Fahrenheit.
 */
void printTemperatureData(uint8_t address[8], float celsius) {

    float fahrenheit = (celsius * 1.8 + 32.0);
    
    printf("0x");
    for (uint8_t i = 0; i < 8; i++) {
        printf("%02X", address[i]);
    }
    printf(": %d", (int)celsius);
    printf("C, ");
    printf("%d", (int)fahrenheit);
    printf("F\n");
}
