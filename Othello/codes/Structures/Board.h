#pragma once

#include <string>

struct Board
{
    int BoardSize;
    char** grid;
    char** validMovesGrid;
    char** displayGrid;

public:
    Board();
    void deleteBoardMemory();
    std::string retrieveBoard();
    void newGameSetup();
    void loadBoard(std::string Board);
    void prepareBoardForMove(char thisTurnColor);
    void putPiece(int x, int y, char color);
    int countBlack();
    int countWhite();
    int isValid(int x, int y, char color);
    int countValidMoves();
    void display();
    char placeCursor(int x, int y);

public:
    void flip(int x, int y);
    int countFlipsInDirection(int x, int y, int dx, int dy, char color);
    void resetValidMovesGrid();
    void prepareValidMovesGrid(char color);
    void updateDisplayGrid();
    void putValidMoves();
};