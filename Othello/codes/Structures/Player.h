#pragma once

#include <string>

struct Player
{
    std::string name;
    char32_t color;

public:
    Player(std::string name, char32_t color);
    std::string retrievePlayer();
    void loadPlayer(std::string player);
};