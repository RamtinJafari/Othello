#include "Move.h"
#include "../Utilities/StrToInt.h"
#include <string>


Move::Move(int x, int y, char32_t color)
{
    this -> x = x;
    this -> y = y;
    this -> color = color;
}

std::string Move::retrieveMove()
{
    return std::to_string(x) + " " + std::to_string(y) + " " + std::string(1, color);
}

void Move::loadMove(std::string move)
{
    int xLastIndex = move.find(" ") - 1;
    std::string x = move.substr(0, xLastIndex);
    move = move.substr(0, xLastIndex + 1);

    int yLastIndex = move.find(" ") - 1;
    std::string y = move.substr(0, yLastIndex);
    move = move.substr(0, yLastIndex + 1);

    std::string color = move.substr(0, move.size());

    this -> x = strToInt(x);
    this -> y = strToInt(y);
    this -> color = static_cast<char32_t>(color[0]);
};
