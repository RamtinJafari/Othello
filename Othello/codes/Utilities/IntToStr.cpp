#include <string>
#include "IntToStr.h"



char getChar(int digit);
int getDigitsCount(int number);



std::string intToStr(int number)
{
    int numberLen = getDigitsCount(number);

    char result[numberLen];
    
    for (int i = numberLen - 1; i >= 0; i--)
    {
        result[i] = getChar(number % 10);
        number /= 10;
    }

    std::string resultStr = "";
    
    for (int i = 0; i < numberLen; i++)
    {
        resultStr += result[i];
    }

    return resultStr;
}

char getChar(int digit)
{
    switch (digit)
    {
    case 0:
        return '0';
    case 1:
        return '1';
    case 2:
        return '2';
    case 3:
        return '3';
    case 4:
        return '4';
    case 5:
        return '5';
    case 6:
        return '6';
    case 7:
        return '7';
    case 8:
        return '8';
    case 9:
        return '9';
    }
}

int getDigitsCount(int number)
{
    if (number == 0) return 1;

    int count = 0;

    while(number != 0)
    {
        number /= 10;
        count++;
    }

    return count;
}