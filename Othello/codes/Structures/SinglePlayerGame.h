#pragma once

#include "Board.h"
#include "Bot.h"
#include "Player.h"
#include <string>

struct SinglePlayerGame
{
    int id;
    Board GameBoard;
    std::string mode;
    Player* Player1;
    Bot* GameBot;
    char32_t CurrentTurnColor;
    int Winner;

public:
    SinglePlayerGame(Board GameBoard, Player* Player1, Bot* GameBot, char32_t CurrentTurnColor);
    void start();
    void end();
    void loadGame(int gameId);

private:
    void changeTurn();
    std::string retrieveGame();
    void save();
};
