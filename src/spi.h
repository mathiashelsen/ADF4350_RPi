#ifndef _SPI_H
#define _SPI_H

#include <assert.h>
#include <fcntl.h>				//Needed for SPI port
#include <linux/spi/spidev.h>	//Needed for SPI port
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>			//Needed for SPI port
#include <unistd.h>

struct
{
	char *device;
	uint8_t mode;
	uint8_t bits;
	uint32_t speed;
	uint16_t delay;
	int fd;

} SPI_config;

int initSPI(char *devName);

int transfer(uint32_t reg);

int closeSPI();

#endif
