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



void outputDecoratedSavedSinglePlayerGame(std::string game);
void outputDecoratedSavedMultiPlayerGame(std::string game);



void outputDecoratedSavedGame(std::string game)
{
    std::string gameMode = getMode(game);

    if (gameMode == "1Player") 
    {
        return outputDecoratedSavedSinglePlayerGame(game);
    }
    else
    {
        return outputDecoratedSavedMultiPlayerGame(game);
    }
}



void outputDecoratedSavedSinglePlayerGame(std::string game)
{
    int id = getGameId(game);
    std::cout << "{\n  id = " + intToStr(id) + "\n";

    std::string savedGameBoard = getGameBoard(game);
    int boardSize = getSavedBoardSize(savedGameBoard);

    std::cout << "  game board = { \n";

    
    std::cout << "      ";
    print("―", boardSize * 2 + 2);
    std::cout << std::endl;

    int i = 0;
    for (int y = 0; y < boardSize; y++)
    {
        std::cout << "      |";
        for (int x = 0; x < boardSize; x++)
        {
            std::cout << savedGameBoard[i] << "|";
            i += 2;
        }

        std::cout << "\n        ";
        print("―", boardSize * 2 + 2);
        std::cout << "\n";
    }

    std::cout << "      ";
    print("―", boardSize * 2 + 2);
    std::cout << "  }\n";


    std::cout << "  mode = single player\n";

    Player player{"0", 0};
    player.loadPlayer(getPlayer1(game));
    std::cout << "  Player = {\n"
        << "      name = " << player.name << std::endl
        << "      color = " << player.color << std::endl
        << "  }\n";


    Bot bot{"0", 0};
    bot.loadBot(getBot(game));
    std::string difficultyToOutput = (
        bot.difficulty == 1 ?
            "easy" : bot.difficulty == 2 ?
                "medium" : "hard"
    );
    std::cout << "  Bot = {\n"
        << "      difficulty = " << difficultyToOutput << std::endl
        << "  }\n";

    int winner = getWinner(game);
    std::string winnerToOutput = (
        winner == 0 ?
            "The game is unfinished" : winner == 1 ?
                "Player has won this game" : winner == 2 ?
                    "Bot has won this game" : "The game resulted in a draw"
    );
    std::cout << "  " << winnerToOutput << "\n}\n";
}



void outputDecoratedSavedMultiPlayerGame(std::string game)
{
    int id = getGameId(game);
    std::cout << "{\n  id = " + intToStr(id) + "\n";

    std::string savedGameBoard = getGameBoard(game);
    int boardSize = getSavedBoardSize(savedGameBoard);

    std::cout << "  game board = { \n";

    
    std::cout << "      ";
    print("―", boardSize * 2 + 2);
    std::cout << std::endl;

    int i = 0;
    for (int y = 0; y < boardSize; y++)
    {
        std::cout << "      |";
        for (int x = 0; x < boardSize; x++)
        {
            std::cout << savedGameBoard[i] << "|";
            i += 2;
        }

        std::cout << "\n        ";
        print("―", boardSize * 2 + 2);
        std::cout << "\n";
    }

    std::cout << "      ";
    print("―", boardSize * 2 + 2);
    std::cout << "  }\n";


    std::cout << "  mode = multiplayer\n";

    Player player1{"0", 0};
    player1.loadPlayer(getPlayer1(game));
    std::cout << "  Player1 = {\n"
        << "      name = " << player1.name << std::endl
        << "      color = " << player1.color << std::endl
        << "  }\n";


    Player player2{"0", 0};
    player2.loadPlayer(getPlayer1(game));
    std::cout << "  Player2 = {\n"
        << "      name = " << player2.name << std::endl
        << "      color = " << player2.color << std::endl
        << "  }\n";

    int winner = getWinner(game);
    std::string winnerToOutput = (
        winner == 0 ?
            "The game is unfinished" : winner == 1 ?
                "Player has won this game" : winner == 2 ?
                    "Bot has won this game" : "The game resulted in a draw"
    );
    std::cout << "  " << winnerToOutput << "\n}\n";
}