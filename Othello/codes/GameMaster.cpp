#include <windows.h>
#include <conio.h>
#include <iostream>
#include <limits>
#include "GameMaster.h"
#include "Database/GameLogManager.h"
#include "GameReviewer.h"
#include "Database/GameHistoryManager.h"
#include "Structures/Board.h"
#include "Structures/Player.h"
#include "Structures/Bot.h"
#include "Structures/SinglePlayerGame.h"
#include "Structures/MultiPlayerGame.h"
#include "Structures/Config.h"
#include "Utilities/outputDecoratedSavedGame.h"
#include "Utilities/GetSavedBoardSize.h"

void handleLoadGame();
void handleNewGame();
void loadSinglePlayerGame(int gameId);
void loadMultiPlayerGame(int gameId);
void handleSinglePlayerNewGame();
void handleMultiPlayerNewGame();

void executeGameMaster(bool loadGameMode)
{
    clearGameLog(); // emptying GameLog for the new game

    if (loadGameMode) handleLoadGame();
    else handleNewGame();
}



void handleLoadGame()
{
    system("cls");

    std::cout << "You've chosen to load a previous unfinished game\n"
        << "Previous unfunished games are: \n";

    int startingGameId = getFirstGameId();
    int lastGameId = getLastGameId();

    if (startingGameId == -1)
    {
        std::cout << "\n There are no games inside game history\n Press any key to continue";
        getch();
    }

    for (int i = 0; i <= lastGameId; i++)
    {
        outputDecoratedSavedGame(getGameById(i));
    }

    int gameId;
    std::string wantedGame;
    while (true)
    {
        std::cout << "\n Please type the id of the game you wish to continue playing: ";

        std::cin >> gameId;

        std::string savedGame = getGameById(gameId);

        if (getProperty(6, savedGame) != "0")
        {
            std::cout << "The id entered belong to a finished game, please choose an id from the given list\n";
            continue;
        }

        wantedGame = savedGame;
    }

    if (getProperty(2, wantedGame) == "1Player")
    {
        loadSinglePlayerGame(gameId);
    }
    else
    {
        loadMultiPlayerGame(gameId);
    }
}



void loadSinglePlayerGame(int gameId)
{
    SinglePlayerGame game = getSinglePlayerGame(gameId);

    game.start();

    std::cout << "\n The game has finished, would you like to see the replay? [Y/N]" << std::endl;

    char procceded;
    std::cin >> procceded;
    
    if (procceded == 'Y' || procceded == 'y')
    {
        executeGameReviewer(*game.GameBoard);
    }

    game.GameBoard -> deleteBoardMemory();
} 



void loadMultiPlayerGame(int gameId)
{
    MultiPlayerGame game = getMultiPlayerGame(gameId);

    game.start();

    std::cout << "\n The game has finished, would you like to see the replay? [Y/N]" << std::endl;

    char procceded;
    std::cin >> procceded;
    
    if (procceded == 'Y' || procceded == 'y')
    {
        executeGameReviewer(*game.GameBoard);
    }

    game.GameBoard -> deleteBoardMemory();
}



void handleNewGame()
{
    int chosenOption = 0;
    while (true)
    {
        system("cls");

        std::cout << (chosenOption == 0 ? " >":" ") << " Single Player" << std::endl
            << (chosenOption == 1 ? " >":" ") << " MultiPlayer" << std::endl;

        int userInput = getch();

        if (userInput == static_cast<int>('w') || userInput == 72)
        {
            if (chosenOption == 1)
            {
                chosenOption--;
                continue;
            }
        }

        if (userInput == static_cast<int>('s') || userInput == 80)
        {
            if (chosenOption == 0)
            {
                chosenOption++;
                continue;
            }
        }

        if (userInput == 13)
        {
            if (chosenOption == 0)
            {
                handleSinglePlayerNewGame();
            }
            else if (chosenOption == 1)
            {
                handleMultiPlayerNewGame();
            }
            break;
        }
    }
}



void handleSinglePlayerNewGame()
{
    Bot bot{"0", 0};
    
    int chosenOption = 0;
    while (true)
    {
        system("cls");

        std::cout << "Please choose the difficulty: \n"
            << (chosenOption == 0 ? " >":" ") << " Easy" << std::endl
            << (chosenOption == 1 ? " >":" ") << " Medium" << std::endl
            << (chosenOption == 2 ? " >":" ") << " Hard" << std::endl;

        int userInput = getch();

        if (userInput == static_cast<int>('w') || userInput == 72)
        {
            if (chosenOption != 0)
            {
                chosenOption--;
                continue;
            }
        }

        if (userInput == static_cast<int>('s') || userInput == 80)
        {
            if (chosenOption != 2)
            {
                chosenOption++;
                continue;
            }
        }

        if (userInput == 13)
        {
            if (chosenOption == 0)
            {
                bot.difficulty = 1;
                bot.name == "Easy Bot";
            }
            else if (chosenOption == 1)
            {
                bot.difficulty = 2;
                bot.name == "Medium Bot";
            }
            else if (chosenOption == 2)
            {
                bot.difficulty = 3;
                bot.name == "Hard Bot";
            }
            break;
        }
    }

    Player player{"0", 'W'};
    while (true)
    {
        system("cls");

        std::string name;
        std::cout << "Please set your name: ";
        std::cin >> name;
        std::cout << std::endl;

        if (name.find("|") != -1 || name.find("[") != -1 || name.find("]") != -1)
        {
            std::cout << "One day you will die" 
                << "\nSome poeple will attend your funeral only for the food"
                << "\nYour friends will hang out again after 1 month"
                << "\nYour kids will go to work casually after 2 months"
                << "\nYour wife/husband will laugh with a comedy movie after 6 month"
                << "\nEventually, your name will be forgotten and memories of you fade away"
                << "\nYet some poeple like you think they can escape this fact by putting | or [ or ] inside their names"
                << "\nYou guys think noone is going to forget your name because they be like:"
                << "\n      Damn bro this guy has a | or [ or ] inside their name! I'm going to remember this name till my last breath"
                << "\nLet's be real, nobody will say that unless they're high and high poeple can't remember anything more than 5 seconds"
                << "\nSo stop annoying me and choose a name without | or [ or ]"
                << "\nNow click any freaking key to continue...";

            getch();
            continue;
        }

        player.name = name;

        system("cls");
        break;
    }

    chosenOption = 0;
    while (true)
    {
        system("cls");

        std::cout << "Please choose your color\n"
            << (chosenOption == 0 ? " >":" ") << " Black" << std::endl
            << (chosenOption == 1 ? " >":" ") << " White" << std::endl;

        int userInput = getch();

        if (userInput == static_cast<int>('w') || userInput == 72)
        {
            if (chosenOption == 1)
            {
                chosenOption--;
                continue;
            }
        }

        if (userInput == static_cast<int>('s') || userInput == 80)
        {
            if (chosenOption == 0)
            {
                chosenOption++;
                continue;
            }
        }

        if (userInput == 13)
        {
            if (chosenOption == 0)
            {
                player.color = 'B';
            }
            else if (chosenOption == 1)
            {
                player.color = 'W';
            }
            break;
        }
    }

    system("cls");

    Board board{Config::instance -> BOARD_SIZE};

    board.newGameSetup();

    SinglePlayerGame game{&board, &player, &bot, 'B'};

    game.start();

    std::cout << "\n The game has finished, would you like to see the replay? [Y/N]" << std::endl;

    char procceded;
    std::cin >> procceded;
    
    if (procceded == 'Y' || procceded == 'y')
    {
        executeGameReviewer(*game.GameBoard);
    }

    game.GameBoard -> deleteBoardMemory();
}



void handleMultiPlayerNewGame()
{
    Player player1{"0", 'W'};
    while (true)
    {
        system("cls");

        std::string name;
        std::cout << "Player1, Please set your name: ";
        std::cin >> name;
        std::cout << std::endl;

        if (name.find("|") != -1 || name.find("[") != -1 || name.find("]") != -1)
        {
            std::cout << "One day you will die" 
                << "\nSome poeple will attend your funeral only for the food"
                << "\nYour friends will hang out again after 1 month"
                << "\nYour kids will go to work casually after 2 months"
                << "\nYour wife/husband will laugh with a comedy movie after 6 month"
                << "\nEventually, your name will be forgotten and memories of you fade away"
                << "\nYet some poeple like you think they can escape this fact by putting | or [ or ] inside their names"
                << "\nYou guys think noone is going to forget your name because they be like:"
                << "\n      Damn bro this guy has a | or [ or ] inside their name! I'm going to remember this name till my last breath"
                << "\nLet's be real, nobody will say that unless they're high and high poeple can't remember anything more than 5 seconds"
                << "\nSo stop annoying me and choose a name without | or [ or ]"
                << "\nNow click any freaking key to continue...";

            getch();
            continue;
        }

        player1.name = name;

        system("cls");
        break;
    }

    int chosenOption = 0;
    while (true)
    {
        system("cls");

        std::cout << "Player1, please choose your color\n"
            << (chosenOption == 0 ? " >":" ") << " Black" << std::endl
            << (chosenOption == 1 ? " >":" ") << " White" << std::endl;

        int userInput = getch();

        if (userInput == static_cast<int>('w') || userInput == 72)
        {
            if (chosenOption == 1)
            {
                chosenOption--;
                continue;
            }
        }

        if (userInput == static_cast<int>('s') || userInput == 80)
        {
            if (chosenOption == 0)
            {
                chosenOption++;
                continue;
            }
        }

        if (userInput == 13)
        {
            if (chosenOption == 0)
            {
                player1.color = 'W';
            }
            else if (chosenOption == 1)
            {
                player1.color = 'B';
            }
            break;
        }
    }

    Player player2{"0", 'W'};
    while (true)
    {
        system("cls");

        std::string name;
        std::cout << "Player2, Please set your name: ";
        std::cin >> name;
        std::cout << std::endl;

        if (name.find("|") != -1 || name.find("[") != -1 || name.find("]") != -1)
        {
            std::cout << "One day you will die" 
                << "\nSome poeple will attend your funeral only for the food"
                << "\nYour friends will hang out again after 1 month"
                << "\nYour kids will go to work casually after 2 months"
                << "\nYour wife/husband will laugh with a comedy movie after 6 month"
                << "\nEventually, your name will be forgotten and memories of you fade away"
                << "\nYet some poeple like you think they can escape this fact by putting | or [ or ] inside their names"
                << "\nYou guys think noone is going to forget your name because they be like:"
                << "\n      Damn bro this guy has a | or [ or ] inside their name! I'm going to remember this name till my last breath"
                << "\nLet's be real, nobody will say that unless they're high and high poeple can't remember anything more than 5 seconds"
                << "\nSo stop annoying me and choose a name without | or [ or ]"
                << "\nNow click any freaking key to continue...";

            getch();
            continue;
        }

        player2.name = name;

        system("cls");
        break;
    }

    system("cls");

    Board board{Config::getInstance() -> BOARD_SIZE};

    board.newGameSetup();

    MultiPlayerGame game{&board, &player1, &player2, 'B'};

    game.start();

    std::cout << "\n The game has finished, would you like to see the replay? [Y/N]" << std::endl;

    char procceded;
    std::cin >> procceded;
    
    if (procceded == 'Y' || procceded == 'y')
    {
        executeGameReviewer(*game.GameBoard);
    }

    game.GameBoard -> deleteBoardMemory();
}