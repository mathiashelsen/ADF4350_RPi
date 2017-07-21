#include "adf4350.h"

int initRegs()
{
	memset( &register_1, 0, 4);
	memset( &register_2, 0, 4);
	memset( &register_3, 0, 4);
	memset( &register_4, 0, 4);
	memset( &register_5, 0, 4);

	register_0.control_bits	= (unsigned int) 0;

	register_1.control_bits	= (unsigned int) 1;

	register_2.control_bits	= (unsigned int) 2;
	register_2.pd_polarity	= (unsigned int) 1;
	register_2.chargepump	= (unsigned int) 15;	// 5mA CP out
	register_2.muxout		= (unsigned int) 4;		// Digital lock-detect

	register_3.control_bits	= (unsigned int) 3;
	register_3.clock_div	= (unsigned int) 4095;
	register_3.clock_div_mode = (unsigned int) 0;

	register_4.control_bits	= (unsigned int) 4;
	register_4.power_en		= (unsigned int) 1;
	register_4.fb_sel		= (unsigned int) 1;

	register_5.control_bits	= (unsigned int) 5;
	register_5.ld_pin_mode	= (unsigned int) 1;

	return 0;
}

int setFrequency(double frequency)
{
	double VCO_frequency, divider, remainder, eps;
	int RF_DIV, INT , MOD, FRAC, PHASE, BS_CLK_DIV, PRESCALER, LDF;

	BS_CLK_DIV		= (int)(ceil( PFD_FREQ / 125.0e3 )+1.0);	
	PHASE			= 1;
	RF_DIV			= (int) ceil(log(2200.0e6 / frequency)/log(2));
	assert( RF_DIV >= 0 && RF_DIV < 5 );
	VCO_frequency	= frequency * pow(2.0, (double) RF_DIV);

	assert( VCO_frequency >= 2200.0e6 && VCO_frequency <= 4400.0e6);

	divider			= VCO_frequency/PFD_FREQ;
	INT				= (int)floor(divider);
	if( VCO_frequency < 3000.0e6)
	{
		PRESCALER = 0;
		assert( INT >= 23 );
	} else {
		PRESCALER = 1;
		assert( INT >= 75 );
	}
	printf("Target VCO frequency: %f MHz\n", VCO_frequency/1.0e6);
	

	remainder	= divider - (double)INT;

	MOD		= 2;
	FRAC		= MOD-1;
	eps			= (fabs(remainder*(double)MOD - (double)FRAC));

	while( MOD < 4095 && eps > 1.0e-10 )
	{
		MOD		+= 1;
		FRAC	= (int)round(MOD * remainder);
		eps		= (fabs(remainder*(double)MOD - (double)FRAC));
	}
	

	assert( FRAC >= 0 && FRAC < MOD );
	assert( MOD >= 2 && MOD <= 4095 );

	LDF			= (FRAC > 0) ? 0 : 1;
	

	printf("%f x %d = %d + %f = %d + %d/%d\n", divider, (int)pow(2.0, (double)RF_DIV),
		 INT, remainder, INT, FRAC, MOD);

	printf("LDF = %d, BS_CLK_DIV = %d, RF_DIV = %d\n", LDF, BS_CLK_DIV, RF_DIV);
	

	register_0.frac_value	= (unsigned int) FRAC;
	register_0.int_value	= (unsigned int) INT;

	register_1.modulus	= (unsigned int) MOD;
	register_1.phase	= (unsigned int) PHASE;
	register_1.prescaler	= (unsigned int) PRESCALER;

	register_2.r_counter	= (unsigned int) 2;
	register_2.ldf		= (unsigned int) LDF;

	register_4.band_sel	= (unsigned int) BS_CLK_DIV;
	register_4.div_sel	= (unsigned int) RF_DIV;


	uint32_t tmp;
	printf("-- Register 5 --\n");
	memcpy( &tmp, &register_5, 4);
	transfer( tmp );
	usleep(500);


	printf("-- Register 4 --\n");
	memcpy( &tmp, &register_4, 4);
	transfer( tmp );
	usleep(500);


	printf("-- Register 3 --\n");
	memcpy( &tmp, &register_3, 4);
	transfer( tmp );
	usleep(500);


	printf("-- Register 2 --\n");
	memcpy( &tmp, &register_2, 4);
	transfer( tmp );
	usleep(500);


	printf("-- Register 1 --\n");
	memcpy( &tmp, &register_1, 4);
	transfer( tmp );
	usleep(500);


	printf("-- Register 0 --\n");
	memcpy( &tmp, &register_0, 4);
	transfer( tmp );
	usleep(500);


	return 0;

}
