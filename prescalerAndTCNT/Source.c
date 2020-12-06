#include "Header.h"
#include <stdio.h>

int main(void)
{
	/*int x = 0;

	for (size_t i = 1; i < 16000000; i+=100)
	{
		x = excludePrescaler(i);
		printf_s("%d", x);
		if (fmod(i, 5) == 0);
			printf_s(" ");
	}

	*/
	while (1)
	{
		int x = 0;
		printf_s("Indtast frekvens der skal tjekkes mod prescaler: ");
		scanf_s("%d", &x);
		printf_s("\n");

		
		struct prescaler pre = calcPreTCNT(x);
		printf_s("%d %d\n", pre.prescalerNumber_, pre.frequenzy_);

	}
}