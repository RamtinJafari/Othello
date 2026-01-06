#pragma once

#include <string>

struct Board
{
    int BoardSize;
    char** grid;
    char** validMovesGrid;
    char** displayGrid;
    int CursorX = 0;
    int CursorY = 0;

public:
    Board(int boardSize);
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

public:
    void flip(int x, int y);
    int countFlipsInDirection(int x, int y, int dx, int dy, char color);
    void resetValidMovesGrid();
    void prepareValidMovesGrid(char color);
    void updateDisplayGrid();
    void putValidMoves();
};