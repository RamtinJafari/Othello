#pragma once

#include "Board.h"
#include "Player.h"
#include <string>

struct MultiPlayerGame
{
    int id;
    Board* GameBoard;
    std::string mode;
    Player* Player1;
    Player* Player2;
    char CurrentTurnColor;
    int Winner;

public:
    MultiPlayerGame(Board* GameBoard, Player* Player1, Player* Player2, char CurrentTurnColor);
    void start();
    void end();
    std::string retrieveGame();
    void save();
    void changeTurn();

private:
};
