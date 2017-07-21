#include <stdio.h>
#include <stdlib.h>
#include "adf4350.h"
#include "spi.h"

int main(void)
{
	initSPI("/dev/spidev0.0");
	initRegs();

	setFrequency(151.0e6);
	setFrequency(151.336e6);
	
	closeSPI();

	return 0;
}
