#include "IntSqrt.h"

int intSqrt(int number)
{
    for (int i = 1; i < 100000000; i++)
    {
        if (i * i == number) return i;
    }
    return -1;
}