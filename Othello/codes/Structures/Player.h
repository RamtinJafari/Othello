#pragma once

#include <string>

struct Player
{
    std::string name;
    char color;

public:
    Player(std::string name, char color);
    std::string retrievePlayer();
    void loadPlayer(std::string player);
};