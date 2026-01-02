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
    void prepareBoardForMove();
    void putPiece(int x, int y, char color);
    int countBlack();
    int countWhite();
    bool isValid(int x, int y, char color);
    int countValidMoves();
    void display(int cursorX, int cursorY);
    char placeCursor(int x, int y);

private:
    void flip(int x, int y);
    void verticalflip(int x, int y, char color);
    void horazinalflip(int x, int y, char color);
    void diagonalflip(int x, int y, char color);
    int verticalNeighbour(int x, int y, char color);
    int horazinalNeighbour(int x, int y, char color);
    int diagonalNeighbour(int x, int y, char color);
    void resetValidMovesGrid();
    void prepareValidMovesGrid();
    void updateDisplayGrid();
    void putValidMoves();
};