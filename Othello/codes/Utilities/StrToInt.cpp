#include <string>
#include "StrTiInt.h"
using namespace std;

// turns a string containing digits into a integer
int strToInt(string number)
{
    int result {0};

    while (number != "")
    {
        result = result*10 + getNumber((char) number[0])
        number = number.substr(1, line.size())
    }

    return number;
}

int getNumber(char digit)
{
    switch (digit)
    {
        case '0':
            return 0;
            break;
        case '1':
            return 1;
            break;
        case '2':
            return 2;
            break;
        case '3':
            return 3;
            break;
        case '4':
            return 4;
            break;
        case '5':
            return 5;
            break;
        case '6':
            return 6;
            break;
        case '7':
            return 7;
            break;
        case '8':
            return 8;
            break;
        case '9':
            return 9;
            break;
    }
}