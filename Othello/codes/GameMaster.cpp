// Player name should not have a | or [ or ] character within

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

void executeGameMaster(bool loadGameMode)
{
    clearGameLog(); // emptying GameLog for the new game

    if (loadGameMode) handleLoadGame();
    else handleNewGame();
}



void handleLoadGame()
{
    system("clr");

    std::cout << "You've chosen to load a previous unfinished game\n"
        << "Previous unfunished games are: \n";

    int numberOfUnfinishedGames = countUnfinishedGames();
    for (int i = 0; i < numberOfUnfinishedGames; i++)
    {
        outputDecoratedSavedGame(
            getUnfinishedGame(i)
        );
    }

    int gameId;
    std::string game;
    while (true)
    {
        std::cout << "\n Please type the id of the game you wish to continue playing: ";

        if (!std::cin >> gameId)
        {
            // Failed: non-numeric input
            std::cout << "Invalid number inputted, please enter a valid number.\n";
            std::cout << "Press any key to continue...";
            
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            getch();
            
            continue;
        }

        std::string savedGame = getGameById(gameId);

        if (getWinner(savedGame) != 0)
        {
            std::cout << "The id entered belong to a finished game, please choose an id from the given list\n";
            continue;
        }

        game = savedGame;
    }

    int legalBoardSize = Config::getInstance() -> BOARD_SIZE;
    int thisGameBoardSize = getSavedBoardSize(getGameBoard(game));

    if (thisGameBoardSize != legalBoardSize)
    {
        Config::customizeBoardSize(thisGameBoardSize); // changing board size temporarily
    }

    if (getMode(game) == "1Player")
    {
        loadSinglePlayerGame(gameId);
    }
    else
    {
        loadMultiPlayerGame(gameId);
    }

    Config::customizeBoardSize(legalBoardSize); // changing board size to the original value
}



void loadSinglePlayerGame(int gameId)
{
    Player player{"0", 0};
    Bot bot{"0", 0};
    Board board{};

    SinglePlayerGame game{board, &player, &bot, '0'};

    game.loadGame(gameId);

    game.start();

    std::cout << "\n The game has finished, would you like to see the replay? [Y/N]" << std::endl;

    char procceded;
    std::cin >> procceded;
    
    if (procceded == 'Y' || procceded == 'y')
    {
        executeGameReviewer(game.GameBoard);
    }
} 



void loadMultiPlayerGame(int gameId)
{
    Player player1{"0", 0};
    Player player2{"0", 0};
    Board board{};

    MultiPlayerGame game{board, &player1, &player2, '0'};

    game.loadGame(gameId);

    game.start();

    std::cout << "\n The game has finished, would you like to see the replay? [Y/N]" << std::endl;

    char procceded;
    std::cin >> procceded;
    
    if (procceded == 'Y' || procceded == 'y')
    {
        executeGameReviewer(game.GameBoard);
    }
}



void handleNewGame()
{
    int chosenOption = 0;
    while (true)
    {
        system("cls");

        std::cout << (chosenOption == 0 ? "■":"□") << " Single Player" << std::endl
            << (chosenOption == 1 ? "■":"□") << " MultiPlayer" << std::endl;

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
            << (chosenOption == 0 ? "■":"□") << " Easy" << std::endl
            << (chosenOption == 1 ? "■":"□") << " Medium" << std::endl
            << (chosenOption == 2 ? "■":"□") << " Hard" << std::endl;

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
                bot.difficulty = 2; // to change
                bot.name == "Hard Bot";
            }
            break;
        }
    }

    Player player{"0", '○'};
    while (true)
    {
        system("clr");

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

        system("clr");
        break;
    }

    chosenOption = 0;
    while (true)
    {
        system("cls");

        std::cout << "Please choose your color\n"
            << (chosenOption == 0 ? "■":"□") << " Black" << std::endl
            << (chosenOption == 1 ? "■":"□") << " White" << std::endl;

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
                player.color = '○';
            }
            else if (chosenOption == 1)
            {
                player.color = '⬤';
            }
            break;
        }
    }

    system("clr");

    Board board{};

    SinglePlayerGame game{board, &player, &bot, '○'};

    game.GameBoard.newGameSetup();
    game.start();

    std::cout << "\n The game has finished, would you like to see the replay? [Y/N]" << std::endl;

    char procceded;
    std::cin >> procceded;
    
    if (procceded == 'Y' || procceded == 'y')
    {
        executeGameReviewer(game.GameBoard);
    }
}



void handleMultiPlayerNewGame()
{
    Player player1{"0", '○'};
    while (true)
    {
        system("clr");

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

        system("clr");
        break;
    }

    int chosenOption = 0;
    while (true)
    {
        system("cls");

        std::cout << "Player1, please choose your color\n"
            << (chosenOption == 0 ? "■":"□") << " Black" << std::endl
            << (chosenOption == 1 ? "■":"□") << " White" << std::endl;

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
                player1.color = '○';
            }
            else if (chosenOption == 1)
            {
                player1.color = '⬤';
            }
            break;
        }
    }

    Player player2{"0", '○'};
    while (true)
    {
        system("clr");

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

        system("clr");
        break;
    }

    system("clr");

    Board board{};

    MultiPlayerGame game{board, &player1, &player2, '○'};

    game.GameBoard.newGameSetup();
    game.start();

    std::cout << "\n The game has finished, would you like to see the replay? [Y/N]" << std::endl;

    char procceded;
    std::cin >> procceded;
    
    if (procceded == 'Y' || procceded == 'y')
    {
        executeGameReviewer(game.GameBoard);
    }
}