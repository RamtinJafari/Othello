#include "Board.h"
#include "Player.h"
#include <iostream>

struct SinglePlayerGame
{
    int id;
    Board GameBoard;
    std::string mode;
    Player Player1;
    Player Player2;
    char CurrentTurnColor;
    int Winner;

    SinglePlayerGame()
    {
        
    }
};