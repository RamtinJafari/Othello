#pragma once

#include <string>
#include "Board.h"
#include "Move.h"

struct Bot
{
    std::string name;
    int difficulty;

    public:
    Bot(std::string name, int difficulty);
    Move suggestMove(Board& board, char color);
    std::string retrieveBot();
    void loadBot(std::string bot);

    private:
    Move suggestEasyMove(Board& borad, char color);
    Move suggestMediumMove(Board& board, char color);
    Move suggestHardMove(Board& board, char color);
    int ratePlacement(int x, int y, int boardSize);
    int rateBoard(Board& board, char botColor);
    int minimax(char color, Board dummyBoard, bool isMaxAgent, char botColor, int depth = 0, int upFloor = INT_MIN, int downFloor = INT_MAX);
    void deepCopy(Board& board, Board& newBoard);
};