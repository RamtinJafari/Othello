#pragma once

#include "codes/Structures/Board.h"
#include "codes/Structures/Bot.h"
#include "codes/Structures/Player.h"
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
