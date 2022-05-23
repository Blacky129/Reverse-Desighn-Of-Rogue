#pragma once

#include <random>

class CRandomGenrator
{
public:

	int generateIntergerInRange(int Min, int Max);

private:
	std::random_device Random;

};

