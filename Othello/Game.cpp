#include "codes/Database/GameHistoryManager.h"
#include "codes/Structures/Config.h"
#include "codes/ConfigModifier.h"
#include "codes/GameMaster.h"
#include "codes/GameReporter.h"
#include "codes/GameReviewer.h"
#include "codes/Helper.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

int main()
{
    system("cls");
    
    Config::initialize();
    syncWithNewLimit();


    int chosenOption = 0;

    while (true)
    {
        system("cls");

        std::cout << "Welcome to Othello game!" << std::endl
            << (chosenOption == 0 ? "■":"□") << " new game" << std::endl
            << (chosenOption == 1 ? "■":"□") << " load game" << std::endl
            << (chosenOption == 2 ? "■":"□") << " help" << std::endl
            << (chosenOption == 3 ? "■":"□") << " games history" << std::endl
            << (chosenOption == 4 ? "■":"□") << " settings" << std::endl
            << (chosenOption == 5 ? "■":"□") << " exit" << std::endl;

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
            if (chosenOption < 5)
            {
                chosenOption++;
                continue;
            }
        }

         if (userInput == 13)
        {
            if (chosenOption == 0)
            {
                executeGameMaster(false);
            }
            else if (chosenOption == 1)
            {
                executeGameMaster(true);
            }
            else if (chosenOption == 2)
            {
                executeHelper();
            }
            else if (chosenOption == 3)
            {
                executeGameReporter();
            }
            else if (chosenOption == 4)
            {
                executeConfigModifier();
            }
            else if (chosenOption == 5)
            {
                break;
            }
        }
    }

    return 0;
}