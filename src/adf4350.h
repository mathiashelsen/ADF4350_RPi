#ifndef _ADF4350_H
#define _ADF4350_H

#define REF_CLK 10.0e6
#define PFD_FREQ 5.0e6

#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "spi.h"

struct
{
	unsigned int control_bits	: 3;
	unsigned int frac_value		: 12;
	unsigned int int_value		: 16;
	unsigned int reserved		: 1;
} register_0;

struct
{
	unsigned int control_bits	: 3;
	unsigned int modulus		: 12;
	unsigned int phase			: 12;
	unsigned int prescaler		: 1;
	unsigned int reserved		: 4;
} register_1;

struct
{
	unsigned int control_bits	: 3;
	unsigned int reset_ctr		: 1;
	unsigned int tristate_cp	: 1;
	unsigned int pd				: 1;
	unsigned int pd_polarity	: 1;
	unsigned int ldp			: 1;
	unsigned int ldf			: 1;
	unsigned int chargepump		: 4;
	unsigned int doublebuff		: 1;
	unsigned int r_counter		: 10;
	unsigned int r_div_2		: 1;
	unsigned int ref_doubler	: 1;
	unsigned int muxout			: 3;
	unsigned int lownoise		: 2;
	unsigned int reserved		: 1;
} register_2;

struct
{
	unsigned int control_bits	: 3;
	unsigned int clock_div		: 12;
	unsigned int clock_div_mode	: 2;
	unsigned int reserved		: 1;
	unsigned int csr			: 1;
	unsigned int reserved_2		: 2;
	unsigned int reserver_3		: 11;
} register_3;

struct
{
	unsigned int control_bits	: 3;
	unsigned int power			: 2;
	unsigned int power_en		: 1;
	unsigned int aux_power		: 2;
	unsigned int aux_en			: 1;
	unsigned int aux_sel		: 1;
	unsigned int mtld			: 1;
	unsigned int vco_pwr_dwn	: 1;
	unsigned int band_sel		: 8;
	unsigned int div_sel		: 3;
	unsigned int fb_sel			: 1;
	unsigned int reserved		: 8;	
} register_4;

struct
{
	unsigned int control_bits	: 3;
	unsigned int reserved		: 16;
	unsigned int reserved_2		: 2;
	unsigned int reserved_3		: 1;
	unsigned int ld_pin_mode	: 2;
	unsigned int reserved_4		: 8;
} register_5;

int initRegs();
int setFrequency(double frequency);

#endif
