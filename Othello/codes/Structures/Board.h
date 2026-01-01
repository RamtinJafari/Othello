#pragma once

#include <string>
#include <Config.h>

struct Board
{
    int BoardSize;
    char** grid;

public:
    Board();
    void display();
    void flip(int x, int y);
    void putPiece(int x, int y, char color);
    bool isValid(int x, int y, char color);
    int countBlack();
    int countWhite();
    std::string retrieveBoard();
    void newGameSetup();
    void loadBoard(std::string Board);
    void deleteBoardMemory();
};