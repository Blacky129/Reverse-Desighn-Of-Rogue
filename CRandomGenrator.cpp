#include "CRandomGenrator.h"

int CRandomGenrator::generateIntergerInRange(int Min, int Max)
{

	if (Min == Max)
		return Max;

	if (Min > Max)
		std::swap(Min, Max);

	return Random() % (Max - Min + 1) + Min;
}
