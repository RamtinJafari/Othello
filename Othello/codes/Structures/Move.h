#pragma once

struct Move
{
    int x;
    int y;
    char color;

public:
    Move(int x, int y, char color);
    std::string retrieveMove();
    Move loadMove(std::string move);
}