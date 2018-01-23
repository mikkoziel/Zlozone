
#include "dht1.h"

int dht1::read(int pin)
{
	//Bufor
	uint8_t bits[5];		//tablica wyników
	uint8_t bitsCnt = 7;		//Licznik bitów
	uint8_t bytesCnt = 0;		//Licznik bajtów

	//Pusty bufor
	for (int i=0; i< 5; i++) bits[i] = 0;

	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
	delay(18);
	digitalWrite(pin, HIGH);
	delayMicroseconds(40);
	pinMode(pin, INPUT);


	// Czeka aż dostanie sygnał startu, jeśli nie dostanie to błąd czasowy
	unsigned int loopCnt = 10000;
	while(digitalRead(pin) == LOW)
		if (loopCnt-- == 0) return DHTLIB_ERROR_TIMEOUT;

	loopCnt = 10000;
	while(digitalRead(pin) == HIGH)
		if (loopCnt-- == 0) return DHTLIB_ERROR_TIMEOUT;

	// Czytamy odpowiedź sensora (40 bitów dzielimy na 5 bajtów)
	for (int i=0; i<40; i++)
	{
		loopCnt = 10000;
		while(digitalRead(pin) == LOW)
			if (loopCnt-- == 0) return DHTLIB_ERROR_TIMEOUT;
		//zmienna do sprawdzenia czy przesyłanie trwało wystarczająco długo
		unsigned long t = micros();

		loopCnt = 10000;
		while(digitalRead(pin) == HIGH)
			if (loopCnt-- == 0) return DHTLIB_ERROR_TIMEOUT;

	//Uzupełnianie konkretnych pól tablicy bits przy użyciu przesunięcia bitowego
		//(jeśli czas przesyłania trwał przynajmniej 40ms to dajemy 1,
		//w przeciwnym przypadku nic nie przesuwamy, czyli na danym miejscy zostaje 0)
		if ((micros() - t) > 40) bits[bytesCnt] |= (1 << bitsCnt);
		// Jeśli skończyliśmy uzupełniać wszystkie bity odpowiedniego bajtu
		if (bitsCnt == 0)
		{
			bitsCnt = 7;    // restartujemy licznik bitowy
			bytesCnt++;      // przechodzimy do następnego bajtu
		}
		else bitsCnt--;	//Jeśli nie to kolejny bit
	}

	// Przypisywanie do odpowiednich zmiennych
	humidity    = bits[0];		//odczyt wilgotności
	temperature = bits[2];		//odczyt temperatury

	//zmienna do sprawdzenia sumy kontrolnej
	uint8_t sum = bits[0] + bits[1] + bits[2] + bits[3];

	//Jeśli suma kontrolna nie równa zmiennej to bład
	if (bits[4] != sum) return DHTLIB_ERROR_CHECKSUM;
	return DHTLIB_OK;		//Inaczej OK
}
