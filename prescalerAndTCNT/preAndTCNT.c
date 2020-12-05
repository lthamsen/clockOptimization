#include <math.h>
#include "Header.h"

int calcPreTCNT(double Hz)
{
	float pre0 = 0;
	float pre8 = 0;
	float pre64 = 0;
	float pre256 = 0;
	float pre1024 = 0;

	int * x = excludePrescaler(Hz);
	for (size_t i = 0; i < 5; i++)
	{
		printf_s("%d", *x);
		x++;
	}
	return 0;

	if (x != 0)
		pre0 = 16000000 / Hz;
	x++;
	if (x != 0)
		pre8 = 2000000 / Hz;
	x++;
	if (x != 0)
		pre64 = 250000 / Hz;

}

int * excludePrescaler(float Hz)
{
	#define SIZE 5

	int pre[SIZE];

	for (int index = 0; index < SIZE; index++)
		pre[index] = 1;

	if (!(Hz >= 62745 && Hz <= 16000000))
		pre[0] = 0;
	if (!(Hz >= 7843 && Hz <= 2000000))
		pre[1] = 0;
	if (!(Hz >= 980 && Hz <= 250000))
		pre[2] = 0;
	if (!(Hz >= 245 && Hz <= 62500))
		pre[3] = 0;
	if (!(Hz >= 61 && Hz <= 15625))
		pre[4] = 0;
	
	return pre;
}

int closestXTogivenN(int x, int N1, int N2)//Finder hvilken af N1 eller N2 er tættest på x
{
	N1 = x - N1;
	N2 = x - N2;

	if (N1 < 0)
		N1 *= -1;
	if (N2 < 0)
		N2 *= -1;

	if (N1 < N2)
		return 1;
	else if (N2 < N1)
		return 2;
	else
		return 1;
	return 0;
}