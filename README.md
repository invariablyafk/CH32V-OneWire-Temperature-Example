An example of how to use a CH32V003 microcontroller with OneWire to communicate with DS18S20 DS1820, DS18B20, or DS1822 temperature sensors.

The example searches for every temperature sensor that it can find on Pin C4. It iterates over the sensors, prompts each sensor to read the temperature, waits for the read to occur, then prints the temperatures via printf() on the CHLINKe single wire serial interface. (or wherever printf() goes)
