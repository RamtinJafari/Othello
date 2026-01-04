#include "ConfigModifier.h"
#include "Database/ConfigManager.h"
#include <conio.h>
#include <windows.h>
#include <limits>
#include <iostream>



bool madeChanges = false;



void handleGameHistoryLimit();
void handleBoardSize();
void handlShowAvailablePlacesToPieces();



void executeConfigModifier()
{
    int chosenOption = 0;

    while (true)
    {
        system("cls");

        std::cout << "curent setting are:" << std::endl
        << "The number of games inside game history: " << getGameHistoryLimit() << std::endl
        << "The size of the board: " << getBoardSize() << std::endl
        << "Show available places for pieces: " << getShowAvailablePlacesForPieces() << std::endl << std::endl;

        std::cout << "Which of these properties do you wish to change?" << std::endl;

        std::cout << (chosenOption == 0 ? "■":"□") << " The number of games inside game history" << std::endl
            << (chosenOption == 1 ? "■":"□") << " The size of the board" << std::endl
            << (chosenOption == 2 ? "■":"□") << " Showing avaibale places for pieces" << std::endl
            << (chosenOption == 3 ? "■":"□") << " apply the changes and exit" << std::endl;

        int userInput = getch();

        if (userInput == static_cast<int>('w') || userInput == 72)
        {
            if (chosenOption > 0)
            {
                chosenOption--;
                continue;
            }
        }

        if (userInput == static_cast<int>('s') || userInput == 80)
        {
            if (chosenOption < 3)
            {
                chosenOption++;
                continue;
            }
        }

        if (userInput == 13)
        {
            if (chosenOption == 0)
            {
                handleGameHistoryLimit();
            }
            else if (chosenOption == 1)
            {
                handleBoardSize();
            }
            else if (chosenOption == 2)
            {
                handlShowAvailablePlacesToPieces();
            }
            else if (chosenOption == 3)
            {
                break;
            }
        }
    }

    if (madeChanges == false) std::cout << "No changes has been made\nPress any key to continue";
    else if (madeChanges == true) std::cout << "Please restart the game for changes to be applied to the game\nPress any key to continue";

    getchar();
    system("cls");
    return;
}



void handleGameHistoryLimit()
{
    system("cls");

    std::cout << "the current value of the number of games inside game history is "
        << getGameHistoryLimit() << std::endl
        << "Please set the new value: " << std::endl;

    int newValue;

    if (!std::cin >> newValue)
    {
        // Failed: non-numeric input
        std::cout << "Invalid number inputted, please enter a valid number.\n";
        std::cout << "Press any key to continue...";
        
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        getch();
        
        return handleGameHistoryLimit();
    }

    if (getGameHistoryLimit() == newValue)
    {
        return handleGameHistoryLimit();
    }

    if (newValue > 100)
    {
        std::cout << "Inputed number is too big, you might face slow loading when recieving reports or loading games"
            << std::endl << "Do you procced? [Y/N]" << std::endl;

        char procceded;
        std::cin >> procceded;
        
        if (!(procceded == 'Y' || procceded == 'y'))
        {
            return handleGameHistoryLimit();
        }
    }

    modifyGameHistoryLimit(newValue);
    std::cout << "Change has been made\nPress any key to continue";
    getch();

    return;
}



void handleBoardSize()
{
    system("cls");

    std::cout << "the current value of the size of the board is "
        << getBoardSize() << std::endl
        << "Please set the new value: " << std::endl;

    int newValue;
    if (!std::cin >> newValue)
    {
        // Failed: non-numeric input
        std::cout << "Invalid number inputted, please enter a valid number.\n";
        std::cout << "Press any key to continue...";
        
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        getch();
        
        return handleGameHistoryLimit();
    }

    if (getBoardSize() == newValue)
    {
        return handleBoardSize();
    }

    if (newValue > 50)
    {
        std::cout << "Inputed number is too big, please set a number lower than or equal to 50\nPress any key to continue" << std::endl;

        getch();

        return handleBoardSize();
    }

    if (newValue % 2 == 1)
    {
        std::cout << "Board size cannot be an odd number, please set an even number\nPress any key to continue";

        getch();

        return handleBoardSize();
    }

    modifyBoardSize(newValue);
    std::cout << "Change has been made\nPress any key to continue";
    getch();

    return;
}



void handlShowAvailablePlacesToPieces()
{
    system("cls");
    
    bool curValue = getShowAvailablePlacesForPieces();

    std::cout << (curValue ?
        "Currently, you will see available places for putting your piece durning the game":
        "Currently, you won't see available places for putting your piece durning the game"
    ) << std::endl;

    std::cout << "Do you proceed to change the behavour? [Y/N]" << std::endl;

    char procceded;
    std::cin >> procceded;
    
    if (!(procceded == 'Y' || procceded == 'y'))
    {
        return;
    }

    madeChanges = true;
    if (curValue)
    {
        modifyShowAvailablePlacesForPieces(false);
    }
    else
    {
        modifyShowAvailablePlacesForPieces(true);
    }

    std::cout << "Change has been made\nPress any key to continue";
    getch();

    return;
}
