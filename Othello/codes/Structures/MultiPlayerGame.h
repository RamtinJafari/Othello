#pragma once

#include "Board.h"
#include "Player.h"
#include <string>

struct MultiPlayerGame
{
    int id;
    Board GameBoard;
    std::string mode;
    Player* Player1;
    Player* Player2;
    char32_t CurrentTurnColor;
    int Winner;

public:
    MultiPlayerGame(Board GameBoard, Player* Player1, Player* Player2, char32_t CurrentTurnColor);
    void start();
    void end();
    void loadGame(int gameId);

private:
    void changeTurn();
    std::string retrieveGame();
    void save();
};
