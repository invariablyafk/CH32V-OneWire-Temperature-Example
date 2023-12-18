# CH32V003 Microcontroller OneWire Example with DS18x20 Sensors

## Overview
This example demonstrates how to use a CH32V003 microcontroller to communicate with DS18S20, DS1820, DS18B20, or DS1822 temperature sensors using the OneWire protocol. The CH32V003 is a cost-effective 48 MHz RISC-V microcontroller with 16kB of flash and 2kB of RAM, suitable for various applications.

## Features
- Searches for temperature sensors on Pin C4.
- Iterates over each sensor to prompt a temperature read.
- Waits for the read to occur and then prints the temperatures.
- Utilizes `printf()` over the CHLINK single-wire serial interface for output.

## Installation and Setup
- For detailed installation instructions of the development environment, refer to the [ch32v003fun project wiki](https://github.com/cnlohr/ch32v003fun/wiki).
- The project supports `printf` debugging and gdbserver-style debugging via minichlink.
- Building and flashing instructions can be found in the `examples/blink` directory.

## Hardware Requirements
- `SWIO` on `PD1` is required for programming/debugging.
- `PC4` connected to DS18x20 sensor data. (Don't forget the external pull-up resistor to VCC)

## Additional Resources
- For more examples and third-party tools, check out [ch32v003fun_wildwest](https://github.com/someuser/ch32v003fun_wildwest) and [ch32v003fun_libs](https://github.com/anotheruser/ch32v003fun_libs).
- Join the [Discord community](https://discord.gg/CCeyWyZ) for support and discussion.

##  Resources from Pallav Aggarwal's Blog
- [Setting up the Development Environment for CH32V003: Compile and Run first example code](https://pallavaggarwal.in/setting-up-the-development-environment-for-ch32v003-compile-and-run-first-example-code/)
- [CH32V003: GPIO as Output](https://pallavaggarwal.in/ch32v003-gpio-as-output/)
- [CH32V003: GPIO as Input (Polling, Interrupt)](https://pallavaggarwal.in/ch32v003-gpio-input-polling-interrupt/)
- [CH32V003: UART Transmit / Receive data](https://pallavaggarwal.in/ch32v003-uart-transmit-receive-data/)
- [CH32V003: PWM output with Frequency and Duty Cycle Control](https://pallavaggarwal.in/ch32v003-pwm-output-with-frequency-and-duty-cycle-control/)
- [CH32V003: ADC for analog signal measurement](https://pallavaggarwal.in/ch32v003-adc-for-analog-signal-measurement/)
- [CH32V003: I2C Interface](https://pallavaggarwal.in/ch32v003-i2c-interface/)
- [CH32V003: SPI Interface](https://pallavaggarwal.in/ch32v003-spi-interface/)
- [CH32V003: Timer Interrupt](https://pallavaggarwal.in/ch32v003-timer-interrupt/)
- [CH32V003: How to read 64-bit Unique ID](https://pallavaggarwal.in/ch32v003-how-to-read-64-bit-unique-id/)

## Sensors and Maximum OneWire Library
- The example is compatible with DS18S20, DS1820, DS18B20, and DS1822 temperature sensors.
- The Maximum OneWire library is designed to efficiently handle communication with multiple sensors over a single wire.

## Notes on CH32V003
- The CH32V003 operates at different performance levels depending on whether it runs from RAM or FLASH due to varying wait states.
- For further technical details, refer to the [Debugging Manual](https://raw.githubusercontent.com/openwch/ch32v003/main/RISC-V%20QingKeV2%20Microprocessor%20Debug%20Manual.pdf) and [Processor Manual](http://www.wch-ic.com/downloads/QingKeV2_Processor_Manual_PDF.html).
- An external oscillator was used during testing.

## Microcontroller Information (CH32V003)
- [CH32V003 Microcontroller Details](https://www.wch-ic.com/products/CH32V003.html)
  - Features a 48MHz system main frequency, 2KB SRAM, 16KB Flash.
  - Includes a variety of peripherals such as USART, I2C, SPI, ADC, and timers.
  - Offers multiple low-power modes and a 1-wire serial debug interface.


----



In a tiny world of silicon and wire,

Lives a microcontroller, CH32V003, with a desire.

To speak in tongues of RISC-V, so clear,

Whispering to sensors, both far and near.


Through OneWire it travels, a single thread,

Carrying tales of temperatures, both blue and red.

"Too hot or cold?" the sensors keenly measure,

In a dance of bytes, they find their treasure.


In this realm of circuits, small and spry,

Micro wonders unfold, under the digital sky.
