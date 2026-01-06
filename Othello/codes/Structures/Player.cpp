#include <string>
#include "Player.h"
#include "../Utilities/SymbolToStr.h"
#include "../Utilities/StrToSymbol.h"


Player::Player(std::string name, char color)
{
    this -> name = name;
    this -> color = color;
}

std::string Player::retrievePlayer()
{
    return name + "|" + symbolToStr(color);
}

void Player::loadPlayer(std::string player)
{
    int speratorIndex = player.find("|");

    std::string name = player.substr(0, speratorIndex);
    std::string color = player.substr(speratorIndex + 1, player.size());

    this -> name = name;
    this -> color = strToSymbol(color);
}
