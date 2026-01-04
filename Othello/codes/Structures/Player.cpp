#include <string>
#include <windows.h>
#include "codes/Structures/Player.h"


Player::Player(std::string name, char32_t color)
{
    this -> name = name;
    this -> color = color;
}

std::string Player::retrievePlayer()
{
    return name + "|" + std::string(1, color);
}

void Player::loadPlayer(std::string player)
{
    int speratorIndex = player.find("|");

    std::string name = player.substr(0, speratorIndex);
    std::string color = player.substr(speratorIndex + 1, player.size());

    this -> name = name;
    this -> color = static_cast<char32_t>(color[0]);
}
