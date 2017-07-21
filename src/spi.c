#include "spi.h"

int initSPI(char *devName)
{
	memcpy( SPI_config.device, devName, sizeof(*devName) );
	SPI_config.mode		= SPI_MODE_0;
	SPI_config.bits		= 8;
	SPI_config.speed	= 500000;
	SPI_config.delay	= 0;

	SPI_config.fd		= open(SPI_config.device, O_RDWR);
	assert( SPI_config.fd > 0 );

	assert( ioctl(SPI_config.fd, SPI_IOC_WR_MODE, &(SPI_config.mode)) != -1 );
	assert( ioctl(SPI_config.fd, SPI_IOC_RD_MODE, &(SPI_config.mode)) != -1 );
	assert( ioctl(SPI_config.fd, SPI_IOC_WR_BITS_PER_WORD, &(SPI_config.bits)) != -1 );
	assert( ioctl(SPI_config.fd, SPI_IOC_RD_BITS_PER_WORD, &(SPI_config.bits)) != -1 );
	assert( ioctl(SPI_config.fd, SPI_IOC_WR_MAX_SPEED_HZ, &(SPI_config.speed)) != -1 );
	assert( ioctl(SPI_config.fd, SPI_IOC_RD_MAX_SPEED_HZ, &(SPI_config.speed)) != -1 );

	return 0;
}

int transfer(uint32_t reg)
{
	// MSB first
	uint8_t tx_buffer[4];
	tx_buffer[0] = (uint8_t)((reg >> 24) & 0xFF);
	tx_buffer[1] = (uint8_t)((reg >> 16) & 0xFF);
	tx_buffer[2] = (uint8_t)((reg >> 8)  & 0xFF);
	tx_buffer[3] = (uint8_t)((reg >> 0)  & 0xFF);
	uint8_t rx_buffer[4] = {0, 0, 0, 0};

	struct spi_ioc_transfer tr = {
		.tx_buf = tx_buffer,
		.rx_buf = rx_buffer,
		.len = 4,
		.delay_usecs = SPI_config.delay,
		.speed_hz = SPI_config.speed,
		.bits_per_word = SPI_config.bits
	};

	assert( ioctl(SPI_config.fd, SPI_IOC_MESSAGE(1), &tr) >= 1 );

	return 0;
}
