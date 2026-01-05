#include <string>

char strToSymbol(std::string character)
{
    if (character == "W")
    {
        return 'W';
    }
    else if (character == "B")
    {
        return 'B';
    }
    else if (character == ".")
    {
        return '.';
    }
    else if (character == "X")
    {
        return 'X';
    }
    else if (character == "O")
    {
        return 'O';
    }
}