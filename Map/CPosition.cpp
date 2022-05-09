#include "CPosition.h"
#include <math.h>

bool operator==(CPosition LeftObject, CPosition RightObject)
{
    if (LeftObject.X == RightObject.X && LeftObject.Y == RightObject.Y)
        return true;
    return false;
}

CPosition operator+(CPosition LeftObject, CPosition RightObject)
{
    return CPosition{ LeftObject.X + RightObject.X, LeftObject.Y + RightObject.Y};
}

CPosition operator-(CPosition LeftObject, CPosition RightObject)
{
    return CPosition{LeftObject.X - RightObject.X, LeftObject.Y - RightObject.Y};
}

float CPosition::getVectorLength()
{
    return sqrt(X * X + Y * Y);
}
