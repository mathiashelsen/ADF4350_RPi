#include <stdio.h>
#include <stdlib.h>
#include "adf4350.h"
#include "spi.h"

int main(void)
{
	double fT = 137.0e6*2;
	while(fT < 4400.0e6)
	{
		setFrequency(fT);
		fT += 137.0e6;
	}

	initSPI("/dev/spidev0.0");
	transfer((uint32_t) 1);
	closeSPI();

	return 0;
}
