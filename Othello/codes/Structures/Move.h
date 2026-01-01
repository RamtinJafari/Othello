#pragma once

#include <string>

struct Move
{
    int x;
    int y;
    char color;

public:
    Move(int x, int y, char color);
    std::string retrieveMove();
    void loadMove(std::string move);
};