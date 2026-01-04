#pragma once

#include <string>

struct Board
{
    int BoardSize;
    char32_t** grid;
    char32_t** validMovesGrid;
    char32_t** displayGrid;

public:
    Board();
    void deleteBoardMemory();
    std::string retrieveBoard();
    void newGameSetup();
    void loadBoard(std::string Board);
    void prepareBoardForMove(char32_t thisTurnColor);
    void putPiece(int x, int y, char32_t color);
    int countBlack();
    int countWhite();
    int isValid(int x, int y, char32_t color);
    int countValidMoves();
    void display();
    char32_t placeCursor(int x, int y);

private:
    void flip(int x, int y);
    void verticalflip(int x, int y, char32_t color);
    void horazinalflip(int x, int y, char32_t color);
    void diagonalflip(int x, int y, char32_t color);
    int verticalNeighbour(int x, int y, char32_t color);
    int horazinalNeighbour(int x, int y, char32_t color);
    int diagonalNeighbour(int x, int y, char32_t color);
    void resetValidMovesGrid();
    void prepareValidMovesGrid(char32_t color);
    void updateDisplayGrid();
    void putValidMoves();
};