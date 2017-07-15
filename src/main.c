#include <stdio.h>
#include <stdlib.h>
#include "adf4350.h"

int main(void)
{

	printf("Size of register-0: %lu\n", sizeof(register_0));
	printf("Size of register-1: %lu\n", sizeof(register_1));
	printf("Size of register-2: %lu\n", sizeof(register_2));
	printf("Size of register-3: %lu\n", sizeof(register_3));
	printf("Size of register-4: %lu\n", sizeof(register_4));
	printf("Size of register-5: %lu\n", sizeof(register_5));
	return 0;
}
