#pragma once

#include <string>

struct Move
{
    int x;
    int y;
    char32_t color;

public:
    Move(int x, int y, char32_t color);
    std::string retrieveMove();
    void loadMove(std::string move);
};