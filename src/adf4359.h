#ifndef _ADF4350_H
#define _ADF4350_H

stuct
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
	
} register_2;

#endif
