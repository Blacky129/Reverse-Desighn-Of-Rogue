#pragma once

class CPosition
{
public:
	int X;
	int Y;

	friend bool operator== (CPosition LeftObject, CPosition RightObject);
	friend CPosition operator+ (CPosition LeftObject, CPosition RightObject);
	friend CPosition operator- (CPosition LeftObject, CPosition RightObject);
};

