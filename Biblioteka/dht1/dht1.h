#ifndef dht1_h
#define dht1_h

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// Definicja błędów
#define DHTLIB_OK				0
#define DHTLIB_ERROR_CHECKSUM	-1
#define DHTLIB_ERROR_TIMEOUT	-2

class dht1
{
public:
    int read(int pin);
	int humidity;
	int temperature;
};
#endif
