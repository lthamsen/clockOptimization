#include <math.h>
#include "Header.h"
#define SIZE 5
int pre[SIZE];


void clockInit(int prescaler, int TCNT)
{

}
struct prescaler calcPreTCNT(float Hz)
{
	struct prescaler result;
	result.frequenzy_ = 0;
	result.prescalerNumber_ = 0;

	int prescalerNr = findPrescaler(Hz);

	switch (prescalerNr)
	{
	case 0:
		result.frequenzy_ = (ltRound(16000000 / Hz));
		result.prescalerNumber_ = prescalerNr;
		break;
	case 1:
		result.frequenzy_ = (ltRound(2000000 / Hz));
		result.prescalerNumber_ = prescalerNr;
		break;
	case 2:
		result.frequenzy_ = (ltRound(250000 / Hz));
		result.prescalerNumber_ = prescalerNr;
		break;
	case 3:
		result.frequenzy_ = (ltRound(62500 / Hz));
		result.prescalerNumber_ = prescalerNr;
		break;
	case 4:
		result.frequenzy_ = (ltRound(15625 / Hz));
		result.prescalerNumber_ = prescalerNr;
		break;
	default:
		break;
	}
	return result;
}
//^Giver den endelige TCNT værdi og hvilken prescaler der skal bruges. 
int findPrescaler(float Hz)
{
	float* check = frequenzies(Hz);
	int hold = 0;
	int correctPrescaler = -1;
	for (size_t i = 0; i < SIZE; i++)
	{
		if (closestXTogivenN((int)Hz, (float)hold, check[i]) == 2)
		{
			hold = check[i];
			correctPrescaler = i;
		}
	}
	return correctPrescaler;
}
//^Finder den prescaler der der kommer t�ttest p� frekvens v�rdien ved en integer tcnt v�rdi.
float* frequenzies(float Hz)
{
	float check[SIZE] = { 0 };
	excludePrescaler(Hz);
	/*for (size_t i = 0; i < SIZE; i++)
	{
		printf_s("%p\n", check[i]);
	}*/

	for (size_t i = 0; i < SIZE; i++)
	{

		if (pre[i] != 0)
		{
			/*switch (i)
			{
			case 0:
				check[i] = 16000000 / (float)(ltRound(16000000 / Hz));
				break;
			case 1:
				check[i] = 2000000 / (float)(ltRound(2000000 / Hz));
				break;
			case 2:
				check[i] = 250000 / (float)(ltRound(250000 / Hz));
				break;
			case 3:
				check[i] = 62500 / (float)(ltRound(62500 / Hz));
				break;
			case 4:
				check[i] = 15625 / (float)(ltRound(15625 / Hz));
				break;
			default:
				break;*/
			if(i == 0)
				check[i] = 16000000 / (float)(ltRound(16000000 / Hz));
			if(i == 1)
				check[i] = 2000000 / (float)(ltRound(2000000 / Hz));
			if(i == 2)
				check[i] = 250000 / (float)(ltRound(250000 / Hz));
			if(i == 3)
				check[i] = 62500 / (float)(ltRound(62500 / Hz));
			if(i == 4)
				check[i] = 15625 / (float)(ltRound(15625 / Hz));
		}
	}
	/*for (size_t i = 0; i < SIZE; i++)
	{
		printf_s("\n%f", check[i]);
	}
	printf_s("\n\n");*/
	return check;
}
//^Finder ud af hvilken frekvens timeren k�rer med ved en geven tcnt v�rdi og timer.
int excludePrescaler(float Hz)
{
	/*int pre[SIZE];*/
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
	/*for (size_t i = 0; i < SIZE; i++)
	{
		printf_s("\n%d %d", (int)i, pre[i]);
	}
	printf_s("\n\n");*/
	return pre;
}
//^Excluderer umulige prescaler v�rdier.
int closestXTogivenN(int x, float N1, float N2)
{
	N1 = x - N1;
	N2 = x - N2;
	if (N1 < 0)
		N1 *= (float)-1;
	if (N2 < 0)
		N2 *= (float)-1;
	if (N1 < N2)
		return 1;
	else if (N2 < N1)
		return 2;
	else
		return 1;
	return 0;
}
//^Finder hvilken af N1 eller N2 er t�ttest p� x.
int closerToInt(float N1, float N2)
{
	N1 = N1 - floor(N1);
	N2 = N2 - floor(N2);
	if (N1 > 0.5)
		N1 = 1 - N1;
	if (N2 > 0.5)
		N2 = 1 - N2; 
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
unsigned int ltRound(float number) // Afrunder en float til n�rmeste integer.
{
	if (fmod(number, 1) >= 0.5)
		return (unsigned int)ceil(number);
	if (fmod(number, 1) < 0.5)
		return (unsigned int)floor(number);
	return 1;
}