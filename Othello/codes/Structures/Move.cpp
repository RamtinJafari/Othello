#include "Move.h"
#include "../Utilities/StrToInt.h"
#include "../Utilities/IntToStr.h"
#include "../Utilities/StrToSymbol.h"
#include "../Utilities/SymbolToStr.h"
#include <string>


Move::Move()
{
    this -> x = 0;
    this -> y = 0;
    this -> color = 'B';
}


Move::Move(int x, int y, char color)
{
    this -> x = x;
    this -> y = y;
    this -> color = color;
}

std::string Move::retrieveMove()
{
    return intToStr(x) + " " + intToStr(y) + " " + symbolToStr(color);
}

void Move::loadMove(std::string move)
{
    int xLastIndex = move.find(" ");
    std::string x = move.substr(0, xLastIndex);
    move = move.substr(xLastIndex + 1, move.size());

    int yLastIndex = move.find(" ");
    std::string y = move.substr(0, yLastIndex);
    move = move.substr(yLastIndex + 1, move.size());

    std::string color = move.substr(0, move.size());

    this -> x = strToInt(x);
    this -> y = strToInt(y);
    this -> color = strToSymbol(color);
};
