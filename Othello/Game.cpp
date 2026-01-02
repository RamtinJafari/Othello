#include "codes/Structures/Config.h"
#include "codes/ConfigModifier.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

int main()
{
    system("cls");
    
    Config::initialize();

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
                // new game
            }
            else if (chosenOption == 1)
            {
                // load game
            }
            else if (chosenOption == 2)
            {
                // help
            }
            else if (chosenOption == 3)
            {
                // games history
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