#include "../Database/GameHistoryManager.h"
#include "../Utilities/IntToStr.h"
#include "../Structures/Board.h"
#include "../Structures/Player.h"
#include "../Structures/Bot.h"
#include "../Structures/SinglePlayerGame.h"
#include "../Structures/MultiPlayerGame.h"
#include "GetSavedBoardSize.h"
#include "Print.h"
#include "outputDecoratedSavedGame.h"
#include <iostream>



void outputDecoratedSavedSinglePlayerGame(std::string savedGame);
void outputDecoratedSavedMultiPlayerGame(std::string savedGame);



void outputDecoratedSavedGame(std::string savedGame)
{
    std::string gameMode = getProperty(2, savedGame);

    if (gameMode == "1Player") 
    {
        return outputDecoratedSavedSinglePlayerGame(savedGame);
    }
    else
    {
        return outputDecoratedSavedMultiPlayerGame(savedGame);
    }
}



void outputDecoratedSavedSinglePlayerGame(std::string savedGame)
{
    int id = getGameId(savedGame);
    Board board = *(getSinglePlayerGame(id).GameBoard);
    Player player = *(getSinglePlayerGame(id).Player1);
    Bot bot = *(getSinglePlayerGame(id).GameBot);
    char CurrentTurnColor = getSinglePlayerGame(id).CurrentTurnColor;
    int Winner = getSinglePlayerGame(id).Winner;

    SinglePlayerGame game {&board, &player, &bot, CurrentTurnColor};
    game.id = id;
    game.Winner = Winner;
    game.mode = "1Player";
    game.GameBoard -> CursorX = -1;
    game.GameBoard -> CursorY = -1;


    std::cout << "{\n    id = " << intToStr(game.id) << "\n";

    std::cout << "    game board = { \n";
    game.GameBoard -> display();

    std::cout << "    mode = single player\n";

    std::cout << "    Player = {\n"
        << "        name = " << game.Player1 -> name << std::endl
        << "        color = " << (game.Player1 -> color == 'W' ? "White":"Black") << std::endl
        << "    }\n";


    int botDifficulty = game.GameBot -> difficulty;
    std::string difficultyToOutput = (
        botDifficulty == 1 ?
            "easy" : botDifficulty == 2 ?
                "medium" : "hard"
    );
    std::cout << "    Bot = {\n"
        << "        difficulty = " << difficultyToOutput << std::endl
        << "    }\n";

    int winner = game.Winner;
    std::string winnerToOutput = (
        winner == 0 ?
            "The game is unfinished" : winner == 1 ?
                "Player has won this game" : winner == 2 ?
                    "Bot has won this game" : "The game resulted in a draw"
    );
    std::cout << "    " << winnerToOutput << "\n}\n";
}



void outputDecoratedSavedMultiPlayerGame(std::string savedGame)
{
    int id = getGameId(savedGame);
    Board board = *(getMultiPlayerGame(id).GameBoard);
    Player player1 = *(getMultiPlayerGame(id).Player1);
    Player player2 = *(getMultiPlayerGame(id).Player2);
    char CurrentTurnColor = getMultiPlayerGame(id).CurrentTurnColor;
    int Winner = getMultiPlayerGame(id).Winner;

    MultiPlayerGame game {&board, &player1, &player2, CurrentTurnColor};
    game.id = id;
    game.Winner = Winner;
    game.mode = "2Player";
    game.GameBoard -> CursorX = -1;
    game.GameBoard -> CursorY = -1;

    std::cout << "{\n    id = " << intToStr(game.id) << "\n";

    std::cout << "    game board = { \n";
    game.GameBoard -> display();

    std::cout << "    mode = Multiplayer\n";

    std::cout << "    Player1 = {\n"
        << "        name = " << game.Player1 -> name << std::endl
        << "        color = " << (game.Player1 -> color == 'W' ? "White":"Black") << std::endl
        << "    }\n";

    std::cout << "    Player2 = {\n"
        << "        name = " << game.Player2 -> name << std::endl
        << "        color = " << (game.Player2 -> color == 'W' ? "White":"Black") << std::endl
        << "    }\n";

    int winner = game.Winner;
    std::string winnerToOutput = (
        winner == 0 ?
            "The game is unfinished" : winner == 1 ?
                "Player1 has won this game" : winner == 2 ?
                    "Player2 has won this game" : "The game resulted in a draw"
    );
    std::cout << "    " << winnerToOutput << "\n}\n";
}