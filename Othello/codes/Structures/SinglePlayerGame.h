#pragma once

#include "Board.h"
#include "Bot.h"
#include "Player.h"
#include <string>

struct SinglePlayerGame
{
    int id;
    Board* GameBoard;
    std::string mode;
    Player* Player1;
    Bot* GameBot;
    char CurrentTurnColor;
    int Winner;

public:
    SinglePlayerGame(Board* GameBoard, Player* Player1, Bot* GameBot, char CurrentTurnColor);
    void start();
    void end();
    std::string retrieveGame();
    void save();
    void changeTurn();

private:
};
