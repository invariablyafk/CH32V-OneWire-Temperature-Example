#ifndef OneWire_Direct_GPIO_h
#define OneWire_Direct_GPIO_h
#include "ch32v003fun.h"

// This header should ONLY be included by OneWire.cpp.  These defines are
// meant to be private, used within OneWire.cpp, other libraries which may 
// include OneWire.h.

#include <stdint.h>

// Platform specific I/O definitions

static inline __attribute__((always_inline))
uint8_t directRead()
{
    return GPIO_digitalRead(GPIOv_from_PORT_PIN(GPIO_port_C, 4));
}

static inline __attribute__((always_inline))
void directModeInput()
{
    GPIO_pinMode(GPIOv_from_PORT_PIN(GPIO_port_C, 4), GPIO_pinMode_I_floating, GPIO_Speed_50MHz);
}

static inline __attribute__((always_inline))
void directModeOutput()
{
    GPIO_pinMode(GPIOv_from_PORT_PIN(GPIO_port_C, 4), GPIO_pinMode_O_pushPull, GPIO_Speed_50MHz);
}

static inline __attribute__((always_inline))
void directWriteLow()
{
    GPIO_digitalWrite_lo(GPIOv_from_PORT_PIN(GPIO_port_C, 4));
}

static inline __attribute__((always_inline))
void directWriteHigh()
{
    GPIO_digitalWrite_hi(GPIOv_from_PORT_PIN(GPIO_port_C, 4));
}

#define DIRECT_READ()          directRead()
#define DIRECT_WRITE_LOW()     directWriteLow()
#define DIRECT_WRITE_HIGH()    directWriteHigh()
#define DIRECT_MODE_INPUT()    directModeInput()
#define DIRECT_MODE_OUTPUT()   directModeOutput()
#endif