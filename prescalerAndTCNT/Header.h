#pragma once
#include <stdio.h>


struct prescaler calcPreTCNT(float);
int excludePrescaler(float);
float* frequenzies(float);
int findPrescaler(float);
int closestXTogivenN(int x, float, float);
int closerToInt(float, float);
unsigned int ltRound(float);

struct prescaler 
{
	int prescalerNumber_;
	int frequenzy_;
};