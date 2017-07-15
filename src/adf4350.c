#include "adf4350.h"

int setFrequency(int frequency)
{
    int multiplier;
	// Divider from VCO to output
	int divider;

    if (frequency <= 270e6 && frequency >= 140e6){
        divider = 4;
        multiplier = 16;
    } else if (frequency >= 280e6 && frequency <= 540e6){
        divider = 3;
        multiplier = 8;
    } else if (frequency >= 550e6 && frequency <= 1090e6){
        divider = 2;
        multiplier = 4;
    } else if (frequency >= 1100e6 && frequency <= 2190e6){
        divider = 1;
        multiplier = 2;
    } else{
        divider = 0;
        multiplier = 1;
    }


}
