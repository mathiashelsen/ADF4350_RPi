#include "adf4350.h"

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
	

	remainder	= divider - (double)INT;

	MOD			= 2;
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

	LDF			= (MOD > 0) ? 1 : 0;

	printf("%f x %d = %d + %f = %d + %d/%d\n", divider, (int)pow(2.0, (double)RF_DIV),
		 INT, remainder, INT, FRAC, MOD);
	

	return 0;

}
