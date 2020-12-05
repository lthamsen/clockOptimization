#include <math.h>
#include "Header.h"

int calcPreTCNT(float Hz)
{
	int* x = excludePrescaler(Hz);
	/*for (size_t i = 0; i < 5; i++)
	{
		printf_s("%d\n", *x);
		x++;
	}
	
	x -= 5;*/
	float pre[5] = { 0 };

	if (*x != 0)
		pre[0] = 16000000 / Hz;
	x++;
	if (*x != 0)
		pre[1] = 2000000 / Hz;
	x++;
	if (*x != 0)
		pre[2] = 250000 / Hz;
	x++;
	if (*x != 0)
		pre[3] = 62500 / Hz;
	x++;
	if (*x != 0)
		pre[4] = 15625 / Hz;


	for (int i = 0; i < 5; i++)
	{
		printf_s("%f\n", pre[i]);
	}

	for (int i = 0; i < 5; i++)
	{
		float hold = 0;

		if (pre[i] == 0)
		{
			hold = pre[i + 1];
			pre[i + 1] = 0;
			pre[i] = hold;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		printf_s("%f\n", pre[i]);
	}
	return 0;
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


int closerToInt(float N1, float N2)
{
	N1 = N1 - floor(N1);
	N2 = N2 - floor(N2);

	printf_s("\nN1: %f N2: %f", N1, N2);

	if (N1 > 0.5)
		N1 = 1 - N1;
	if (N2 > 0.5)
		N2 = 1 - N2;

	printf_s("\nN1: %f N2: %f", N1, N2);

	if (N1 == N2)
		return 3;
	else
	{
		if (N1 < N2)
			return 1;
		if (N2 < N1)
			return 2;
	}
}