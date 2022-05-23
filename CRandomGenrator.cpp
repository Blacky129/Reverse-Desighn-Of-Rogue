#include "CRandomGenrator.h"

int CRandomGenrator::generateIntergerInRange(int Min, int Max)
{

	if (Min == Max)
		return Max;

	if (Min > Max)
		std::swap(Min, Max);

	return Random() % (Max - Min + 1) + Min;
}

int CRandomGenrator::trowDice(unsigned int NumberOfDices, unsigned int TypeOfDice)
{
	if (NumberOfDices == 0 || TypeOfDice == 0)
		return 0;

	int Result = 0;
	for (int IndexOfDice = 1; IndexOfDice <= NumberOfDices; IndexOfDice++)
	{
		Result += generateIntergerInRange(1, NumberOfDices);
	}

	return Result;
}
