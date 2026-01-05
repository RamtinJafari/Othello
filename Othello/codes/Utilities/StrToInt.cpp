#include <string>
#include "StrToInt.h"



int getNumber(char digit);



// turns a string containing digits into a integer
int strToInt(std::string number)
{
    int result = 0;

    while (number != "")
    {
        result = result*10 + getNumber((char) number[0]);
        number = number.substr(1, number.size());
    }

    return result;
}

int getNumber(char digit)
{
    switch (digit)
    {
        case '0':
            return 0;
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        default:
            return 0;
    }
}