#include "utile.h"

int max(int a, int b)
{
    if (a > b)
	return a;
    return b;
}

int min(int a, int b)
{
    if (a > b)
        return b;
    return a;
}
/*
float fmin(float a, float b)
{
    if (a > b)
        return b;
    return a;
}

float fmax(float a, float b)
{
    if (a > b)
        return a;
    return b;
}
*/