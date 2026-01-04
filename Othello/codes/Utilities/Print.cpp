#include <iostream>
#include "codes/Utilities/Print.h"

void print(std::string subject, int count)
{
    for (int i = 0; i < count; i++) std::cout << subject;
}