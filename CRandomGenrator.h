#pragma once

#include <random>

class CRandomGenrator
{
public:
	int generateIntergerInRange(int Min, int Max);

	int trowDice(unsigned int NumberOfDices, unsigned int TypeOfDice);

private:
	std::random_device Random;

};

